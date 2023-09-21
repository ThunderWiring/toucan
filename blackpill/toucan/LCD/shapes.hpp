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

// TODO: add line style (dotted, dashed,...etc.)
class Line : public Shape {
  private:
  Point2d pt1, pt2;
  public:
    Line(PixelWidth px_width, Color clr, Point2d& pt1, Point2d& pt2);
    virtual void render(LCDPaint* painter);
};

class Image : public Shape {
  private:
  uint16_t rows, cols;
  uint8_t* image;
  public:
  /**
   * @brief Construct a new Image object. Each color is represented by 16 bits
   * 
   * @param pxls buffer of 8 bit bytes for representing the image pixel colors. 
   *             This equalibrium must be satisfied: 
   *             pxls_length = 2 * height * width
   *             because each color is 16 bits, but the buffer is 8 bits.
   * @param height number of rows in the image
   * @param width number of columns in the image.
   */
    Image(uint8_t* pxls, uint16_t height, uint16_t width);
    virtual void render(LCDPaint* painter);
};

#endif /* __TOUCAN_SHAPES_H__ */
