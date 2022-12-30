#include "robot.hpp"

Robot::Robot() :
  lcd(RoundLCD(LCD_1IN28_HEIGHT, LCD_1IN28_WIDTH)) { }

void Robot::initRobot(USBPacketBufferCallback callback) {
  usb = CustomUSBHID();
  usb.initUSB();
  usb.connect();

  lcd.initLCD();
  lcd.setBackLight(LCD_BACKLIGHT);
  lcd.clearDisplay();
}

void Robot::diplayOnLCD(uint8_t* data, int data_len) {
  if (data == nullptr || data_len <= 0) {
    return;
  }
  uint8_t pct_idx = data[1], rows = data[2], cols = data[3], *pixels = data + 4;
  // TODO: create an image shape from the pixels
  // TODO: draw the image shape using the lcd api. Need to cast to uint16_t
}