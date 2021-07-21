# business card

This is a persistence-of-vision (POV) business card, which is also NFC enabled
to aid in sharing contact information. POV is enabled by an accelerometer which
detects the end points of a swing of the card made by the user, and arranges
the letters to flash at the correct time in between two estimated end points
(the future end-point is guessed at by the length of the previous swing). Settings are changed by a capacitive sense button.

# Directory Structure

The firmare of the card is located in the `src` directory. The electrical
design files are in `design/business_card`. Images and other media are inside
`media`.

- [src](src/)
  - Contains the firmware of the card
- [design](design/)
  - Contains the KiCAD design files of the board
- [card_manufacturing](card_manufacturing/)
  - Contains python scripts used to generate GCODE to laser etch the aluminum top of the card.
- [media](media/)
  - Contains media (gifs, images, etc.)

# Building and Flashing Firmware

In order to flash the firmware, you must have the AVR toolchain installed.

`sudo apt-get install binutils gcc-avr avr-libc uisp avrdude flex byacc bison`

Then, navigate to the `src` directory and run `make` to build the object
file. In order to flash a business card, make sure to have your AVR programmer
plugged into your computer and connected to the board (and make sure the board
is appropriately powered!), then run

`make flash`

avrdude should say the the flash was successfull.

# Running manufacturing scripts

Some helper scripts exist to automate a lot of the manufacturing process for
customization. The scripts are specific to GRBL capable CNC machines (which
can laser etch). Scripts are written in python, and can be installed by
downloading the repository and running:

`pip install -e .`

Once the dependencies are installed, the scripts can be run from the root
directory, for example:

`python -m card_manufacturing.gcode_streamer`

## image_to_laser

This is a command line argument script which converts an image to an efficiently
rastered laser etcher GCODE path. It makes sure to utilize [laser mode](https://github.com/gnea/grbl/wiki/Grbl-v1.1-Laser-Mode) which
has been implemented in GRBL v1.1. The image is thresholded and the laser path
is binary (since the etching is all or nothing on coated aluminum). To get the
help for the script run:

`python -m card_manufacturing.image_to_laser -h`

## laser_calibration

This script generates a GCODE path to calibrate a CNC (with Z travel) with a
laser attachment. It progressively creates lines at different Z levels and
marks what the Z difference was on the line, so the user can identify the line
with the best marking and apply the appropriate offset for future etches. To
get the help for the script run:

`python -m card_manufacturing.laser_calibration -h`

## gcode_streamer

Finally, once GCODE is generated, the following script will stream the GCODE
to the CNC to run the part. To get the help for the script run:

`python -m card_manufacturing.gcode_streamer -h`
