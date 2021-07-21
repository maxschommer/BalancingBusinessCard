import os
import plac
from PIL import Image
import cv2
import numpy as np
from mecode import G

DPMM_PER_DPI = 0.03937008


@plac.annotations(
    image=(
        'the image to convert into g-code for a laser cutter.'
    ),
    dpi=(
        'if provided, override the default DPI of the image for gcode'
        ' generation. If dpi is not availiable in the image header and this'
        ' argument isn\'t provided, then an error will be thrown.',
        'option', 'dpi', float
    ),
    invert_image=(
        'if provided, then invert the image before computing passes', 'flag',
        'ii'
    ),
    lines_per_mm=(
        'the number of laser lines to etch per millimeter.',
        'option', 'lpm', float
    ),
    laser_power=(
        'the power of the laser to use in black areas of the image. Should be a'
        ' value greater than 0 and less than 10000.', 'option', 'lp', int
    ),
    speed=(
        'the speed to move the head of the laser in mm/min.',
        'option', 's', float
    ),
    preview=(
        'preview the laser etch operation.', 'flag', 'p'
    ),
    out=(
        'the output file name of the generated gcode. By default is the same'
        ' name as the image but with a `.nc` extension.', 'option'
    )
)
def image_to_laser(
    image: str,
    dpi: float = None,
    invert_image: bool = False,
    lines_per_mm: float = 8,
    laser_power: int = 7000,
    speed: float = 500,
    preview: bool = False,
    out: str = None
):
    """Convert an image to GCODE for a GRBL machine. This uses "Laser mode" and
    thus the firmware of your machine should be up to date.
    """
    if out is None:
        out = os.path.splitext(os.path.basename(image))[0] + '.nc'
    pil_img = Image.open(image)
    pil_img.load()  # required for png.split()

    pil_img.convert('RGB')
    if dpi is None:
        try:
            dpi = pil_img.info['dpi'][0]
        except KeyError:
            raise ValueError(
                "DPI is not provided by the image and must be given as a parameter.")

    dpmm = DPMM_PER_DPI * dpi  # Convert to dots per mm

    background = Image.new("RGB", pil_img.size, (255, 255, 255))
    background.paste(pil_img, mask=pil_img.split()
                     [3])  # 3 is the alpha channel
    pil_img = background

    img = np.array(pil_img)

    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    _, img = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)

    if invert_image:
        img = ~img

    new_height = int(img.shape[0] / dpmm * lines_per_mm)
    img = cv2.resize(img, (img.shape[1], new_height))

    rows_to_engrave = np.squeeze(np.argwhere(np.any(img == 0, axis=1)))
    img_eng = img[rows_to_engrave].astype(np.int64)

    with G(outfile=out) as l_g:
        l_g.write('$32=1')  # Laser mode on
        l_g.abs_move(0, 0, 0, rapid=True)
        l_g.absolute()  # Enter absolute mode
        l_g.feed(speed)

        l_g.move(0, 0)
        l_g.write('M3 S0')  # Turn the laser on at 0 power
        row_dir = 1  # The direction of the current row
        for i, (y_idx, row) in enumerate(zip(rows_to_engrave, img_eng)):
            y_val = (img.shape[0] - y_idx) / lines_per_mm

            min_x = np.argmin(row)
            max_x = -np.argmin(row[::-1]) + img.shape[1] - 1
            x_start = min_x
            x_end = max_x
            if i % 2 == 1:
                x_start = max_x
                x_end = min_x

            l_g.write(f'G1 X{x_start / dpmm:.4f} Y{y_val:.4f} S0')
            l_g._update_current_position(
                mode='absolute', x=x_start / dpmm, y=y_val)
            row_diff = np.diff(row, prepend=row[0])

            laser_events = np.squeeze(np.argwhere(row_diff != 0))
            if i % 2 == 1:
                laser_events = laser_events[::-1]
            for laser_event in laser_events:
                if row_dir * row_diff[laser_event] > 0:
                    l_g.write(
                        f'G1 X{laser_event / dpmm:.4f} Y{y_val:.4f} S{laser_power}')
                else:
                    l_g.write(f'G1 X{laser_event / dpmm:.4f} Y{y_val:.4f} S0')
                l_g._update_current_position(
                    mode='absolute', x=laser_event / dpmm, y=y_val)
            l_g.write(f'G1 X{x_end / dpmm:.4f} Y{y_val:.4f} S0')
            l_g._update_current_position(
                mode='absolute', x=x_end / dpmm, y=y_val)
            row_dir *= -1

        if preview:
            l_g.view()

        l_g.abs_move(0, 0, 0, rapid=True)
        l_g.write('$32=0')  # Laser mode off


if __name__ == "__main__":
    plac.call(image_to_laser)
