
from usb_host import HID_USB


def get_example_image_data(height: int, width: int):
  r'''
    generate sample image with the given dims
    the image is 3 colors (RGB) each color is one third.
  '''
  red = 0xFF0000
  green = 0xFF00
  blue = 0xFF
  img_size = height * width
  img = [red for _ in range(img_size / 3)]
  img += [green for _ in range(img_size / 3)]
  img += [blue for _ in range(img_size - 2 * img_size / 3)]
  return img

usb_dev = HID_USB()
usb_dev.connect_device()
cfg = usb_dev.get_active_config()
intf = cfg[(0,0)]
ep = usb_dev.get_output_endpoint(intf)

pct = [0 for _ in range(64)]
pct[0] = 11
sent = usb_dev.write_to_endpoint(ep, pct)
print(f'send bytes = {sent}')