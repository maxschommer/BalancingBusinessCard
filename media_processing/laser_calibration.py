import plac
import os
import drawSvg as draw
import numpy as np
from mecode import G


def draw_digit(num: str, width: float = 1, height: float = 2) -> np.ndarray:
    """Generates a numpy array of x, y points required to draw a given
    digit. Assumes that the laser is on the entire time during drawing for each
    digit.

    Args:
        num (str): A character (0-9 and .) to draw
        width (float, optional): The width of the digit. Defaults to 1.
        height (float, optional): The height of the digit. Defaults to 2.

    Returns:
        np.ndarray: A #Nx2 array of x, y points representing the locations to
            move the laser to draw the digit.
    """

    res = None
    if num == '0':
        res = [[0, 0], [1, 0], [1, 1], [0, 1], [0, 0]]
    elif num == '1':
        res = [[0.5, 0], [0.5, 1]]
    elif num == '2':
        res = [[1, 0], [0, 0], [0, 0.5], [1, 0.5], [1, 1], [0, 1]]
    elif num == '3':
        res = [[0, 0], [1, 0], [1, 0.5], [0, 0.5], [1, 0.5], [1, 1], [0, 1]]
    elif num == '4':
        res = [[1, 0], [1, 1], [1, 0.5], [0, 0.5], [0, 1]]
    elif num == '5':
        res = [[0, 0], [1, 0], [1, 0.5], [0, 0.5], [0, 1], [1, 1]]
    elif num == '6':
        res = [[0, 0.5], [0, 0], [1, 0], [1, 0.5], [0, 0.5], [0, 1], [1, 1]]
    elif num == '7':
        res = [[1, 0], [1, 1], [0, 1]]
    elif num == '8':
        res = [[0, 0], [1, 0], [1, 0.5], [0, 0.5],
               [0, 0], [0, 1], [1, 1], [1, 0.5]]
    elif num == '9':
        res = [[1, 0], [1, 1], [0, 1], [0, 0.5], [1, 0.5]]
    elif num == '.':
        res = [[0.4, 0], [0.6, 0], [0.6, 0.1], [0.4, 0.1], [0.4, 0]]
    else:
        raise ValueError(f"Character {num} is not supported.")
    res = np.asarray(res, dtype=np.float64)
    res[:, 0] *= width
    res[:, 1] *= height
    return res


@plac.annotations(
    z_min=('the minimum z height to make a calibration line with.',
           'option', 'zmin', float),
    z_max=('the maximum z height to make a calibration line with.',
           'option', 'zmax', float),
    z_step=('the amount to step in z per calibration line.',
            'option', 'zstp', float),
    x_step=('the amount to step in the x axis for each line (line spacing)',
            'option', 'xstp', float),
    number_height=('the height of the numbers to print for each line.',
                   'option', 'nh', float),
    number_width=('the width of the numbers to print for each line.',
                  'option', 'nw', float),
    number_kern=('the space to put between the numbers.',
                 'option', 'nk', float),
    y_len=('the length of each calibration line.',
           'option', 'ylen', float),
    laser_power=('the power of the laser to use in black areas of the'
                 ' image. Should be a value greater than 0 and less than 10000.',
                 'option', 'lp', int),
    speed=('the speed to move the head of the laser in mm/min.',
           'option', 's', float),
    preview=('preview the laser etch operation.', 'flag', 'p'),
    out=('the output file name of the generated gcode. By default is the same'
         ' name as the image but with a `.nc` extension.', 'option')
)
def laser_calibration(
    z_min: float = 0,
    z_max: float = 10,
    z_step: float = 1,
    x_step: float = 5,
    number_height: float = 2,
    number_width: float = 1,
    number_kern: float = 0.2,
    y_len: float = 25,
    laser_power: int = 7000,
    speed: float = 500,
    preview: bool = False,
    out: str = None
):
    if out is None:
        out = 'laser_cal.nc'

    with G(outfile=out) as l_g:
        l_g.write('$32=1')  # Laser mode on

        l_g.abs_move(0, 0, 0, rapid=True)
        l_g.absolute()  # Enter absolute mode
        l_g.feed(speed)

        l_g.move(0, 0)
        l_g.write('M3 S0')  # Turn the laser on at 0 power

        for i, h in enumerate(np.linspace(z_min, z_max, int((z_max - z_min) / z_step))):
            x = i * x_step
            l_g.write(f'G1 X{x} Y0 Z{h} S0')
            l_g._update_current_position(
                mode='absolute', x=x, y=0, z=h)

            l_g.write(f'G1 X{x} Y{y_len} Z{h} S{laser_power}')
            l_g._update_current_position(
                mode='absolute', x=x, y=y_len, z=h)
            h_str = f'{h:.2f}'

            for i, char in enumerate(h_str):

                path_arr = draw_digit(char, height=number_height,
                                      width=number_width)
                rot_90 = np.asarray([[0, -1], [1, 0]])
                path_arr = np.matmul(rot_90.T, path_arr.T).T
                path_arr[:, 1] += y_len - i * (number_width + number_kern)
                # Space out the letter a bit from the line
                path_arr[:, 0] += x - number_height - 0.5
                p = 0
                for j, pt in enumerate(path_arr):
                    if j != 0:
                        p = laser_power
                    l_g.write(f'G1 X{path_arr[j,0]} Y{path_arr[j,1]} S{p}')
                    l_g._update_current_position(
                        mode='absolute', x=path_arr[j, 0], y=path_arr[j, 1])

        if preview:
            l_g.view()
        l_g.write('$32=0')  # Laser mode off
        l_g.abs_move(0, 0, 0, rapid=True)


if __name__ == "__main__":
    plac.call(laser_calibration)
