#include "robot_driver.hpp"


Robot* Robot_getInstance() {
  static Robot robot_singleton = Robot(readImageFrameFromHostUSB);
return &robot_singleton;
}

void Robot_init(Robot* robot) {
  if (robot == nullptr) {
    return;
  }
  robot->initRobot(readImageFrameFromHostUSB);
}

void readImageFrameFromHostUSB(void *udev, uint8_t *report, uint16_t len) {
  usbd_core_type *pudev = (usbd_core_type *)udev;
  custom_hid_type *pcshid = (custom_hid_type *)pudev->class_handler->pdata;

  Robot* robot = Robot_getInstance();
  robot->diplayOnLCD(pcshid->g_rxhid_buff, len);
}

