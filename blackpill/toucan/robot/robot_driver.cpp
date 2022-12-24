#include "robot_driver.hpp"


Robot* const Robot_getInstance() {
  return &robot_singleton;
}

void Robot_init(Robot* robot) {
  if (robot == nullptr) {
    return;
  }
  robot->initRobot(readImageFrameFromHostUSB);
}

void readImageFrameFromHostUSB(void *udev, uint8_t *report, uint16_t len) {
  uint32_t i_index;
  usbd_core_type *pudev = (usbd_core_type *)udev;
  custom_hid_type *pcshid = (custom_hid_type *)pudev->class_handler->pdata;

  Robot* robot = Robot_getInstance();
  robot->diplayOnLCD(pcshid->g_rxhid_buff, 0);
}

