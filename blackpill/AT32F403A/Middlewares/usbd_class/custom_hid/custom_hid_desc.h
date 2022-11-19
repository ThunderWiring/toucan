/**
  **************************************************************************
  * @file     custom_hid_desc.h
  * @version  v2.0.9
  * @date     2022-04-25
  * @brief    usb custom hid descriptor header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __CUSTOM_HID_DESC_H
#define __CUSTOM_HID_DESC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_hid_class.h"
#include "usbd_core.h"
#include "custom_hid_report_desc.h"

/** @addtogroup AT32F403A_407_middlewares_usbd_class
  * @{
  */

/** @addtogroup USB_custom_hid_desc
  * @{
  */

/** @defgroup USB_custom_hid_desc_definition
  * @{
  */


/**
  * @brief usb bcd number define
  */
#define CUSHID_BCD_NUM                   0x0110

/**
  * @brief usb vendor id and product id define
  */
#define USBD_CUSHID_VENDOR_ID            0x2E3C
#define USBD_CUSHID_PRODUCT_ID           0x5745

/**
  * @brief usb descriptor size define
  */
#define USBD_CUSHID_CONFIG_DESC_SIZE     41
#define USBD_CUSHID_SIZ_STRING_LANGID    4
#define USBD_CUSHID_SIZ_STRING_SERIAL    0x1A

/**
  * @brief usb string define(vendor, product configuration, interface)
  */
#define USBD_CUSHID_DESC_MANUFACTURER_STRING    "Artery"
#define USBD_CUSHID_DESC_PRODUCT_STRING         "Custom HID"
#define USBD_CUSHID_DESC_CONFIGURATION_STRING   "Custom HID Config"
#define USBD_CUSHID_DESC_INTERFACE_STRING       "Custom HID Interface"

#define CUSHID_BINTERVAL_TIME            0x0A

/**
  * @brief usb hid report id define
  */
/**
  * @brief usb hid report id define
  */
#define HID_REPORT_ID_1                   0x01
#define HID_REPORT_ID_2                   0x02
#define HID_REPORT_ID_3                   0x03
#define HID_REPORT_ID_4                   0x04
#define HID_REPORT_ID_5                   0x05
#define HID_REPORT_ID_6                   0xF0

/**
  * @brief usb mcu id address deine
  */
#define MCU_ID1                          (0x1FFFF7E8)
#define MCU_ID2                          (0x1FFFF7EC)
#define MCU_ID3                          (0x1FFFF7F0)



/**
  * @brief usb hid descriptor
  */
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
static ALIGNED_HEAD uint8_t g_custom_hid_usb_desc[9] ALIGNED_TAIL =
{
  0x09,                                  /* bLength: size of HID descriptor in bytes */
  HID_CLASS_DESC_HID,                    /* bDescriptorType: HID descriptor type */
  LBYTE(CUSHID_BCD_NUM),
  HBYTE(CUSHID_BCD_NUM),                    /* bcdHID: HID class specification release number */
  0x00,                                  /* bCountryCode: hardware target conutry */
  0x01,                                  /* bNumDescriptors: number of HID class descriptor to follow */
  HID_CLASS_DESC_REPORT,                 /* bDescriptorType: report descriptor type */
  LBYTE(sizeof(g_usbd_custom_hid_report)),
  HBYTE(sizeof(g_usbd_custom_hid_report)),      /* wDescriptorLength: total length of reprot descriptor */
};


/**
  * @brief usb configuration standard descriptor
  */
#if defined ( __ICCARM__ ) /* iar compiler */
  #pragma data_alignment=4
#endif
static ALIGNED_HEAD uint8_t g_usbd_configuration[USBD_CUSHID_CONFIG_DESC_SIZE] ALIGNED_TAIL =
{
  USB_DEVICE_CFG_DESC_LEN,               /* bLength: configuration descriptor size */
  USB_DESCIPTOR_TYPE_CONFIGURATION,      /* bDescriptorType: configuration */
  LBYTE(USBD_CUSHID_CONFIG_DESC_SIZE),          /* wTotalLength: bytes returned */
  HBYTE(USBD_CUSHID_CONFIG_DESC_SIZE),          /* wTotalLength: bytes returned */
  0x01,                                  /* bNumInterfaces: 1 interface */
  0x01,                                  /* bConfigurationValue: configuration value */
  0x00,                                  /* iConfiguration: index of string descriptor describing
                                            the configuration */
  0xC0,                                  /* bmAttributes: self powered */
  0x32,                                  /* MaxPower 100 mA: this current is used for detecting vbus */

  USB_DEVICE_IF_DESC_LEN,                /* bLength: interface descriptor size */
  USB_DESCIPTOR_TYPE_INTERFACE,          /* bDescriptorType: interface descriptor type */
  0x00,                                  /* bInterfaceNumber: number of interface */
  0x00,                                  /* bAlternateSetting: alternate set */
  0x02,                                  /* bNumEndpoints: number of endpoints */
  USB_CLASS_CODE_HID,                    /* bInterfaceClass: class code hid */
  0x00,                                  /* bInterfaceSubClass: subclass code */
  0x00,                                  /* bInterfaceProtocol: protocol code */
  0x00,                                  /* iInterface: index of string descriptor */

  0x09,                                  /* bLength: size of HID descriptor in bytes */
  HID_CLASS_DESC_HID,                    /* bDescriptorType: HID descriptor type */
  LBYTE(CUSHID_BCD_NUM),
  HBYTE(CUSHID_BCD_NUM),                 /* bcdHID: HID class specification release number */
  0x00,                                  /* bCountryCode: hardware target conutry */
  0x01,                                  /* bNumDescriptors: number of HID class descriptor to follow */
  HID_CLASS_DESC_REPORT,                 /* bDescriptorType: report descriptor type */
  LBYTE(sizeof(g_usbd_custom_hid_report)),
  HBYTE(sizeof(g_usbd_custom_hid_report)), /* wDescriptorLength: total length of reprot descriptor */

  USB_DEVICE_EPT_LEN,                    /* bLength: size of endpoint descriptor in bytes */
  USB_DESCIPTOR_TYPE_ENDPOINT,           /* bDescriptorType: endpoint descriptor type */
  USBD_CUSTOM_HID_IN_EPT,                /* bEndpointAddress: the address of endpoint on usb device described by this descriptor */
  USB_EPT_DESC_INTERRUPT,                /* bmAttributes: endpoint attributes */
  LBYTE(USBD_CUSTOM_IN_MAXPACKET_SIZE),
  HBYTE(USBD_CUSTOM_IN_MAXPACKET_SIZE),  /* wMaxPacketSize: maximum packe size this endpoint */
  CUSHID_BINTERVAL_TIME,                                  /* bInterval: interval for polling endpoint for data transfers */

  USB_DEVICE_EPT_LEN,                    /* bLength: size of endpoint descriptor in bytes */
  USB_DESCIPTOR_TYPE_ENDPOINT,           /* bDescriptorType: endpoint descriptor type */
  USBD_CUSTOM_HID_OUT_EPT,               /* bEndpointAddress: the address of endpoint on usb device described by this descriptor */
  USB_EPT_DESC_INTERRUPT,                /* bmAttributes: endpoint attributes */
  LBYTE(USBD_CUSTOM_OUT_MAXPACKET_SIZE),
  HBYTE(USBD_CUSTOM_OUT_MAXPACKET_SIZE),  /* wMaxPacketSize: maximum packe size this endpoint */
  CUSHID_BINTERVAL_TIME,                    /* bInterval: interval for polling endpoint for data transfers */
};

/**
  * @}
  */
extern uint8_t g_custom_hid_usb_desc[9];
extern usbd_desc_handler custom_hid_desc_handler;

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif


