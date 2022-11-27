
from host.usb_host import HID_USB

usb_dev = HID_USB()
usb_dev.connect_device()
cfg = usb_dev.get_active_config()
intf = cfg[(0,0)]
ep = usb_dev.get_output_endpoint(intf)

pct = [0 for _ in range(64)]
pct[0] = 11
sent = usb_dev.write_to_endpoint(ep, pct)
print(f'send bytes = {sent}')