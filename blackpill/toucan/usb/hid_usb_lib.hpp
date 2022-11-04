#ifndef __TOUCAN_USB_H__
#define __TOUCAN_USB_H__

#include "at32f403a_407_clock.h"
#include "usbd_core.h"
#include "usbd_int.h"
#include "custom_hid_class.h"
#include "custom_hid_desc.h"

/** pointer to function for processing USB packets upon RX event. */
typedef  void (*USBPacketBufferCallback)(void *udev, uint8_t *report, uint16_t len);

class CustomUSBHID {
  private:
    usbd_core_type usb_core_dev;
    usbd_class_handler class_handler;
    usbd_desc_handler desc_handler;

    void set_usb_clock();

  public:
    CustomUSBHID();
    usbd_core_type* getDevice();
    void initUSB();
    void connect();
    void setUSBPacketHandler(USBPacketBufferCallback callback);
};

#endif /* __TOUCAN_USB_H__ */