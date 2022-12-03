#ifndef __ROBOT_TOUCAN_H__
#define __ROBOT_TOUCAN_H__

#include "LCD/spi_lcd.hpp"
#include "usb/hid_usb_lib.hpp"

/** singleton instance for the robot. */
static Robot robot_singleton = Robot();

Robot* const Robot_getInstance();

/** Reads the image frame data from host via USB. */
void readImageFrameFromHostUSB(void *udev, uint8_t *report, uint16_t len);

class Robot {
private:
  RoundLCD lcd;
  CustomUSBHID usb;
public:
  Robot();
  /**
   * @brief Initializes the devices on the robot like USB interface, LCD,..etc.
   */
  void initRobot();

  void diplayOnLCD(uint8_t* data, int data_len);
};

#endif /* __ROBOT_TOUCAN_H__ */