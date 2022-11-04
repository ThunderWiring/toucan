# Toucan

This is the desk robot project based on ARM Cortex M4 Blackpill microcontroller, with desktop studio app for interacting with the robot (later will add a mobile app support).

I'm calling this project Toucan, because Toucans are awesome birds, and this is an awesome robot project.

## Project structure

This repo contains the source code for both the microcontroller as well as the desktop app.
* `blackpill` folder contains the firmware code.
* `host` folder contains the desktop app code for interacting with the Cortex M4 chip (i.e. Blackpill board) via USB protocole.
To make the device detectable on Windows, must use the libusb driver, and need to use Zadig app to override the default driver.