#ifndef __TOUCAN_ROBOT_DRIVER_H__
#define __TOUCAN_ROBOT_DRIVER_H__

#include "robot.hpp"

// /** singleton instance for the robot. */

Robot* Robot_getInstance();

// TODO: should pass a struct of configs like the USB packets handler?
void Robot_init(Robot* robot);

/** Reads the image frame data from host via USB. */
void readImageFrameFromHostUSB(void *udev, uint8_t *report, uint16_t len);

#endif /* __TOUCAN_ROBOT_DRIVER_H__ */