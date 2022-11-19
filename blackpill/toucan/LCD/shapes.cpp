#include "shapes.hpp"

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)
#define ASSERT_PAINTER_PTR(painter_ptr) if ((painter_ptr) == nullptr) return
Shape::Shape(PixelWidth _px_width, Color clr) :
  color(clr), px_width(_px_width) {}

Line::Line(PixelWidth px_width, Color clr, Point2d& p1, Point2d& p2): 
  Shape(px_width, clr), pt1(p1), pt2(p2) {
  }

void Line::render(LCDPaint* painter) {
  ASSERT_PAINTER_PTR(painter);
  
  if(pt1.x == pt2.x) {
    uint16_t start_x = MIN(pt1.x, pt2.x), start_y = MIN(pt1.y, pt2.y);
    uint16_t end_x = MAX(pt1.x, pt2.x), end_y = MAX(pt1.y, pt2.y);
    for (uint16_t y = start_y; y <= end_y; ++y) {
      painter->paintPoint(start_x, y, px_width, color);
    }
    return;
  }

  // Bresenham line algorithm
  // impl taken from https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
  int dx = (int)pt2.x - (int)pt1.x;
  int dy = (int)pt2.y - (int)pt1.y;
  
  int sx = dx > 0 ? 1 : -1;
  int sy = dy > 0 ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;
  
  volatile uint16_t y = pt1.y;
  volatile uint16_t x = pt1.x;
  
  for(;;){
    painter->paintPoint(x, y, px_width, color);
    if (x==pt2.x && y==pt2.y) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x += sx; }
    if (e2 < dy) { err += dx; y += sy; }
  }
}


Image::Image(Color* pxls,  uint16_t height, uint16_t width) : 
  Shape(PX_1X1, BLACK), /* Those values are not needed for Image class, so can be anything. */
  rows(height), cols(width) {

  }

void Image::render(LCDPaint* painter) {
  ASSERT_PAINTER_PTR(painter);
  for (uint16_t row; row < row; row++) {
    for (uint16_t col; col < cols; col++) {
      // paint pixel
    }
  }
}