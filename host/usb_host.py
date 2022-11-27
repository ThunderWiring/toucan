import usb.core
import usb.util
import usb.backend.libusb1

from usb.core import Device, Endpoint, Interface, Configuration

# For this to work need to install libusb (pip3 install libusb)
# Then copy the libusb-1.0.dll from 
# C:\Users\Bassam\AppData\Local\Programs\Python\Python39\Lib\site-packages\libusb\_platform\_windows\ x64
# to C:/Windows/System32

# Had to override the default HID driver on windows (HidUsb (v10.0.19041.868)) to 
# libusb-win32 (v1.2.6.0) driver using Zadig app.

'''
Detects the USB connection of the robot to the PC and initializes a
communication session for sending and receiving data packets.
'''

VENDOR_ID = 0x2E3C
PRODUCT_ID = 0x5745

class HID_USB:
  def __init__(self, vendor=VENDOR_ID, prod_id=PRODUCT_ID):
    self.vendor = vendor
    self.product_id = prod_id
  
  def connect_device(self):
    self.dev:Device  = usb.core.find(idVendor=self.vendor, idProduct=self.product_id)
    if self.dev is None:
        raise ValueError('Device not found')
    self.dev.set_configuration()
    self.cfg = self.dev.get_active_configuration()
  
  def get_active_config(self)-> Configuration:
    return self.dev.get_active_configuration()

  def get_output_endpoint(self, intf: Interface) -> Endpoint:
    return  usb.util.find_descriptor(
      intf,
      # match the first OUT endpoint
      custom_match = \
      lambda e: \
          usb.util.endpoint_direction(e.bEndpointAddress) == \
          usb.util.ENDPOINT_OUT)

  def write_to_endpoint(self, ep: Endpoint, data) -> None:
    return self.dev.write(0x01, data, 100)

