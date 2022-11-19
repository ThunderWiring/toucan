#ifndef __TOUCAN_USB_H__
#define __TOUCAN_USB_H__

#include "at32f403a_407_clock.h"
#include "usbd_core.h"
#include "usbd_int.h"
#include "custom_hid_class.h"
#include "custom_hid_desc.h"

/** pointer to function for processing USB packets upon RX event. */
typedef  void (*USBPacketBufferCallback)(void *udev, uint8_t *report, uint16_t len);

// #if defined ( __ICCARM__ ) /* iar compiler */
//   #pragma data_alignment=4
// #endif
// ALIGNED_HEAD uint8_t imageStreamHIDReportDescriptor [] =
// {
//     0x06, 0x00, 0xFF,    // UsagePage(Image-Stream[65,280])
//     0x09, 0x01,          // UsageId(Image[1])
//     0xA1, 0x01,          // Collection(Application)
//     0x85, 0x01,          //     ReportId(1)
//     0x09, 0x02,          //     UsageId(ImagePixels[2])
//     0x15, 0x80,          //     LogicalMinimum(-128)
//     0x25, 0x7F,          //     LogicalMaximum(127)
//     0x95, 0x01,          //     ReportCount(1)
//     0x75, 0x08,          //     ReportSize(8)
//     0x81, 0x02,          //     Input(Data, Variable, Absolute, NoWrap, Linear, PreferredState, NoNullPosition, BitField)
//     0xC0,                // EndCollection()
// };

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