import array
from typing import List
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

  def write_to_endpoint(self, ep: Endpoint, data, timeout = 100) -> None:
    return ep.write(data, timeout)


class FrameDataPacket:
  '''
  Given an array of data bytes, this class slices it into smaller data packets to be 
  written effectvely to the device, while appending a header if neccessarly.
  '''
  def __init__(self, frame_idx, data_pcket_quota: int) -> None:
    self.frame_idx = frame_idx
    self.data_pcket_quota = data_pcket_quota

  def get_packets(self, data_bytes: List, header: List = []) -> List[List]:
    data_pivot = 0
    frames = len(data_bytes) // self.data_pcket_quota
    packets = []
    for k in range(frames):
      packets.append([k % 256] + header + data_bytes[data_pivot:data_pivot + self.data_pcket_quota])
      data_pivot += self.data_pcket_quota
    
    if len(data_bytes) % self.data_pcket_quota > 0:
      res_data = [0] * self.data_pcket_quota
      res_data[0::] = data_bytes[frames * self.data_pcket_quota - 1::]
      packets.append([0] + header + res_data)

    return packets

class USBImageWriter(HID_USB):
  '''
  Sends image frame via USB to the connected device.
  Each data packet written to the device is of the follwing structure:
  
  +-------+-----------+------+------+--------------------+
  | Frame | pct_index | rows | cols | 60 bytes of pixels |
  +-------+-----------+------+------+--------------------+
  Frame: ID of the frame being transmitted. 
         This is a preparation to support multiple frames transmiting
  pct index: the serial order index of this current report, in order to 
             correctly construct the frame
  rows, cols: dimention of the image (frame)
  '''
  MAX_IMAGE_PACKET_SIZE = 57
  def __init__(self, vendor=VENDOR_ID, prod_id=PRODUCT_ID):
    HID_USB.__init__(self, vendor, prod_id)

  def write_to_endpoint(self, ep: Endpoint, data, timeout = 100) -> None:
    packets = FrameDataPacket(frame_idx=0, data_pcket_quota = self.MAX_IMAGE_PACKET_SIZE)
    packets = packets.get_packets(
      data, # pixel values of the image
      header = [240,240], # header of the packet which is the rows/cols of the image
    )
    total_written = 0
    print(f'packets = {len(packets)}, 1st pct: {len(packets[0])}')
    for pct in packets:
      try:
        array.array('B', pct)
        total_written += ep.write(pct, timeout)
      except:
        print(f'pct = {pct}')
    print(f'total_written = {total_written}')
    return total_written
