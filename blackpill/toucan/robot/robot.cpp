#include "robot.hpp"

Robot* const Robot_getInstance() {
  return &robot_singleton;
}

void readImageFrameFromHostUSB(void *udev, uint8_t *report, uint16_t len) {
  uint32_t i_index;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  custom_hid_type *pcshid = (custom_hid_type *)pudev->class_handler->pdata;

  Robot* robot = Robot_getInstance();
  robot->diplayOnLCD(pcshid->g_rxhid_buff, 0);
}

Robot::Robot() :
  lcd(RoundLCD(LCD_1IN28_HEIGHT, LCD_1IN28_WIDTH)),
  usb(CustomUSBHID(nullptr)) { }

void Robot::initRobot() {
  usb.initUSB();
  usb.connect();

  lcd.initLCD();
  lcd.setBackLight(LCD_BACKLIGHT);
  lcd.clearDisplay();
}

void Robot::diplayOnLCD(uint8_t* data, int data_len) {
  if (data ==nullptr || data_len <= 0) {
    return;
  }
}