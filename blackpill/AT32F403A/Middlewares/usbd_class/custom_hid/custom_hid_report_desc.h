#ifndef __CUSTOM_HID_REPORT_DESC_H__
#define __CUSTOM_HID_REPORT_DESC_H__

#include "usbd_core.h"
#include "custom_hid_class.h"

#define USBD_CUSHID_SIZ_REPORT_DESC      28


/**
  * @brief usb hid report descriptor
  */
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
static ALIGNED_HEAD uint8_t g_usbd_custom_hid_report[USBD_CUSHID_SIZ_REPORT_DESC] ALIGNED_TAIL =
{
  0x06, 0x00, 0xFF,                // UsagePage(Image-Stream[65,280])
  0x09, 0x01,                      // UsageId(FrameDataPacket[1])
  0xA1, 0x01,                      // Collection(Application)
  0x85, 0x69,                      //     ReportId(105)
  0x09, 0x06,                      //     UsageId(ImagePixels[6])
  0x17, 0x00, 0x00, 0x00, 0x80,    //     LogicalMinimum(-2,147,483,648)
  0x27, 0xFF, 0xFF, 0xFF, 0x7F,    //     LogicalMaximum(2,147,483,647)
  0x95, 0x01,                      //     ReportCount(1)
  0x75, 0x20,                      //     ReportSize(32)
  0x81, 0x02,                      //     Input(Data, Variable, Absolute, NoWrap, Linear, PreferredState, NoNullPosition, BitField)
  0xC0,                            // EndCollection()
};


#endif /* __CUSTOM_HID_REPORT_DESC_H__ */