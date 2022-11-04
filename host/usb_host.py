import usb.core
import usb.util
import usb.backend.libusb1

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

dev = usb.core.find(idVendor=VENDOR_ID, idProduct=PRODUCT_ID)
if dev is None:
    raise ValueError('Device not found')

dev.set_configuration()
cfg = dev.get_active_configuration()
intf = cfg[(0,0)]

pct = [0 for _ in range(64)]
pct[0] = 11
print(f'send bytes = {dev.write(0x01, pct, 100)}')
