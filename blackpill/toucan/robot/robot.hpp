#ifndef __ROBOT_TOUCAN_H__
#define __ROBOT_TOUCAN_H__

#include "spi_lcd.hpp"
#include "hid_usb_lib.hpp"


class Robot {
private:
  RoundLCD lcd;
  CustomUSBHID usb;
public:
  Robot();
  Robot(USBPacketBufferCallback callback);

  /**
   * @brief Initializes the devices on the robot like USB interface, LCD,..etc.
   */
  void initRobot(USBPacketBufferCallback callback);

  /**
   * @brief Draws the given pixel data on the lcd
   * 
   * @param data pointer to the pixel values of the image
   * @param data_len number of pixels in the given buffer.
   */
  void diplayOnLCD(uint8_t* data, int data_len);

  usbd_core_type* getUsbDevice();
};

#endif /* __ROBOT_TOUCAN_H__ */