#include "custom_hid_report_desc.h"

const uint8_t USB_HID__getReportSize() {
  return sizeof(g_usbd_custom_hid_report);
}

uint8_t* USB_HID__getReportDesc() {
  return g_usbd_custom_hid_report;
}