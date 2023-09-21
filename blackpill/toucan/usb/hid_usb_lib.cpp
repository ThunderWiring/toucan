#include "hid_usb_lib.hpp"

extern "C" usbd_class_handler custom_hid_class_handler;
extern "C" usbd_desc_handler custom_hid_desc_handler;

CustomUSBHID::CustomUSBHID() {
  class_handler = custom_hid_class_handler;
  desc_handler = custom_hid_desc_handler;
}

CustomUSBHID::CustomUSBHID(USBPacketBufferCallback callback) {
  class_handler = custom_hid_class_handler;
  class_handler.process_buf = callback;
  desc_handler = custom_hid_desc_handler;
}

void CustomUSBHID::initUSB() {
  set_usb_clock();
  usbd_core_init(
    &usb_core_dev, USB, &class_handler, 
    &desc_handler, 0);
    usbd_irq_handler(&usb_core_dev);
}

void CustomUSBHID::connect() {
  usbd_connect(&usb_core_dev);
}

usbd_core_type* CustomUSBHID::getDevice() {
  return &usb_core_dev;
}

void CustomUSBHID::set_usb_clock() {
  /* select usb 48m clcok source */
  usb_clock48m_select(USB_CLK_HICK);

  /* enable usb clock */
  crm_periph_clock_enable(CRM_USB_PERIPH_CLOCK, TRUE);

  /* enable usb interrupt */
  nvic_irq_enable(USBFS_L_CAN1_RX0_IRQn, 0, 0);
}

