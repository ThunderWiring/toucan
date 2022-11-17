#ifndef __TOUCAN_SHAPES_H__
#define __TOUCAN_SHAPES_H__

#include "lcd_graphics.hpp"

class Shape {
  private:
  protected:
    Color color;
    PixelWidth px_width;
  public:
    Shape(PixelWidth px_width, Color clr);
    virtual void render(LCDPaint* painter) = 0;

};

class Line : public Shape {
  private:
  Point2d pt1, pt2;
  public:
    Line(PixelWidth px_width, Color clr, Point2d& pt1, Point2d& pt2);
    virtual void render(LCDPaint* painter);
};

#endif /* __TOUCAN_SHAPES_H__ */