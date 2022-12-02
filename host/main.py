
from usb_host import USBImageWriter
import array

def get_example_image_data(height: int, width: int):
  r'''
    generate sample image with the given dims
    the image is 3 colors (RGB) each color is one third.
  '''
  red = 125
  green = 250
  blue = 80
  img_size = height * width
  img = [red for _ in range(img_size // 3)]
  img += [green for _ in range(img_size // 3)]
  img += [blue for _ in range(img_size - 2 * img_size // 3)]
  return img

usb_dev = USBImageWriter()
usb_dev.connect_device()
cfg = usb_dev.get_active_config()
intf = cfg[(0,0)]
ep = usb_dev.get_output_endpoint(intf)

sent = usb_dev.write_to_endpoint(ep, get_example_image_data(240,240))
print(f'send bytes = {sent}')