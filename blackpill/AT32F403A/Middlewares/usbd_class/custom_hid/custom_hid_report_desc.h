#ifndef __CUSTOM_HID_REPORT_DESC_H__
#define __CUSTOM_HID_REPORT_DESC_H__

#include "usbd_core.h"
#include "custom_hid_class.h"

#define USBD_CUSHID_SIZ_REPORT_DESC      22


/**
  * @brief usb hid report descriptor
  */
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
static ALIGNED_HEAD uint8_t g_usbd_custom_hid_report[USBD_CUSHID_SIZ_REPORT_DESC] ALIGNED_TAIL =
{
  0x06, 0x00, 0xFF,    // UsagePage(Vendor-Defined[65,280])
  0x09, 0x01,          // UsageId(Demo USB[1])
  0xA1, 0x01,          // Collection(Application)
  0x85, 0x01,          //     ReportId(1)
  0x09, 0x02,          //     UsageId(LED Delay[2])
  0x15, 0x80,          //     LogicalMinimum(-128)
  0x25, 0x7F,          //     LogicalMaximum(127)
  0x95, 0x01,          //     ReportCount(1)
  0x75, 0x08,          //     ReportSize(8)
  0x81, 0x02,          //     Input(Data, Variable, Absolute, NoWrap, Linear, PreferredState, NoNullPosition, BitField)
  0xC0,                // EndCollection()
};

uint8_t* USB_HID__getReportDesc();
const uint8_t USB_HID__getReportSize();

#endif /* __CUSTOM_HID_REPORT_DESC_H__ */