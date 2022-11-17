#include "lcd_graphics.hpp"

Point2d::Point2d(uint16_t _x, uint16_t _y): x(_x), y(_y) {}
Point2d::Point2d(Point2d& p): x(p.x), y(p.y) {}

LCDPaint::LCDPaint(LCDDriver* driver, uint16_t h, uint16_t w) : 
  lcd_driver(driver),
  height(h), width(w) {}

void LCDPaint::paintPoint(Point2d& pt, PixelWidth px_width, Color color) {
  paintPoint(pt.x, pt.y, px_width, color);
}

void LCDPaint::paintPoint(
    uint16_t x, uint16_t y, PixelWidth px_width, Color color) {
  if (!is_point_within_boundaries(x, y)) {
    return;
  }
  for (uint16_t row = x; row < x + px_width; ++row) {
    for (uint16_t col = y; col < y + px_width; ++col) {
      set_pixel(row, col, color);
    }
  }
}

bool LCDPaint::is_point_within_boundaries(Point2d& pt) const {
  return is_point_within_boundaries(pt.x, pt.y);
}

bool LCDPaint::is_point_within_boundaries(uint16_t x, uint16_t y) const {
  return x < width && y < height;
}

void LCDPaint::set_pixel(uint16_t x, uint16_t y, Color color) {
  if (!is_point_within_boundaries(x, y)) {
    return;
  }
  lcd_driver->setCursor(x, y, x, y);
  lcd_driver->send16BitData(color);  
}

void LCDPaint::set_pixel(Point2d& pt, Color color) {
  set_pixel(pt.x, pt.y, color);
}