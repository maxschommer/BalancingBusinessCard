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

- src
  - Contains the firmware of the card
- design
  - Contains the KiCAD design files of the board
- media_processing
  - Contains python scripts used to generate GCODE to laser etch the aluminum top of the card.
- media
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
