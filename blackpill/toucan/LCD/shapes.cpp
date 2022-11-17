#include "shapes.hpp"

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)

Shape::Shape(PixelWidth _px_width, Color clr) :
  color(clr), px_width(_px_width) {}

Line::Line(PixelWidth px_width, Color clr, Point2d& p1, Point2d& p2): 
  Shape(px_width, clr), pt1(p1), pt2(p2) {
  }

void Line::render(LCDPaint* painter) {
  if (painter == nullptr) {
    return;
  } else if(pt1.x == pt2.x) {
    uint16_t start_x = MIN(pt1.x, pt2.x), start_y = MIN(pt1.y, pt2.y);
    uint16_t end_x = MAX(pt1.x, pt2.x), end_y = MAX(pt1.y, pt2.y);
    for (uint16_t y = start_y; y <= end_y; ++y) {
      painter->paintPoint(start_x, y, px_width, color);
    }
    return;
  }
  // Bresenham line algorithm
  Point2d p0 = pt1.isLessX(pt2) ? pt1 : pt2;
  Point2d p1 = pt1.isLessX(pt2) ? pt2 : pt1;
  
  int16_t dx = p1.x - p0.x;
  int16_t dy = p1.y - p0.y;
  int16_t D = 2 * dy- dx;
  int16_t y = p0.y;

  for (uint16_t x = p0.x; p0.x < p1.x ; x++) {
    painter->paintPoint(x, y, px_width, color);
    if (D > 0) {
      y++;
      D -= 2 * dx;
    }
    D += 2* dy;
  }
}
