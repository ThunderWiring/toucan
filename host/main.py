
from typing import List
from usb_host import USBImageWriter
import itertools

def get_example_image_data(height: int, width: int) -> List:
  r'''
    generate sample image with the given dims
    the image is 3 colors (RGB) each color is one third.
    Each color is 16 bit.
  '''
  # red = 0xF800
  # green = 0x07E0
  # blue = 0x001F  
  img_size = height * width
  img = [[0xF8, 0x0]for _ in range(img_size // 6)] #red
  img += [[0x07,0xE0] for _ in range(img_size // 6)] #green
  img += [[0x0, 0x1F] for _ in range(img_size - img_size // 3)] #blue
  img =  list(itertools.chain.from_iterable(img))
  return img

usb_dev = USBImageWriter()
usb_dev.connect_device()
cfg = usb_dev.get_active_config()
intf = cfg[(0,0)]
ep = usb_dev.get_output_endpoint(intf)

sent = usb_dev.write_to_endpoint(ep, get_example_image_data(240,240))
print(f'send bytes = {sent}')
