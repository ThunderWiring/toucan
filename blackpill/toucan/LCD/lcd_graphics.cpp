#include "lcd_graphics.hpp"

LCDPaint::LCDPaint(LCDDriver& driver, uint16_t h, uint16_t w) : 
  lcd_driver(driver),
  height(h), width(w) {}

void LCDPaint::paintPoint(Point2d& pt, PixelWidth px_width, Color color) {
  if (!is_point_within_boundaries(pt)) {
    return;
  }
  for (int16_t row = pt.x; row < pt.x + px_width; ++row) {
    for (int16_t col = pt.y; col < pt.y + px_width; ++col) {
      Point2d pxl = {row, col};
      set_pixel(pxl, color);
    }
  }
}

bool LCDPaint::is_point_within_boundaries(Point2d& pt) const {
  return pt.x < width && pt.y < height;
}

void LCDPaint::set_pixel(Point2d& pt, Color color) {
  if (!is_point_within_boundaries(pt)) {
    return;
  }
  lcd_driver.setCursor(pt.x, pt.y, pt.x, pt.y);
  lcd_driver.send16BitData(color);
}