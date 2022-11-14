#ifndef __TOUCAN_LCD_GRAPHICS_H__
#define __TOUCAN_LCD_GRAPHICS_H__

#include "lcd_driver.hpp"

/**
 * @brief Define basic color codes supported by the LCD.
 */
#define WHITE					0xFFFF
#define BLACK					0x0000	  
#define BLUE 					0x001F  
#define BRED 					0XF81F
#define GRED 					0XFFE0
#define GBLUE					0X07FF
#define RED  					0xF800
#define MAGENTA				0xF81F
#define GREEN					0x07E0
#define CYAN 					0x7FFF
#define YELLOW				0xFFE0
#define BROWN					0XBC40 
#define BRRED					0XFC07 
#define GRAY 					0X8430 
#define DARKBLUE			0X01CF	
#define LIGHTBLUE			0X7D7C	 
#define GRAYBLUE      0X5458 
#define LIGHTGREEN    0X841F 
#define LGRAY 			  0XC618 
#define LGRAYBLUE     0XA651
#define LBBLUE        0X2B12 

#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK
#define FONT_BACKGROUND     WHITE

typedef uint16_t Color;
typedef enum {
  PX_1X1 = 1, 
  PX_2X2, 
  PX_3X3
} PixelWidth;

struct Point2d {
  uint16_t x, y;
};

/** 
 * Paints a shape to the LCD
*/
class LCDPaint {
  private:
    LCDDriver lcd_driver;
    uint16_t hight, width;

    bool is_point_within_boundaries(Point2d& pt) const;
    void set_pixel(Point2d& pt, Color color);
  public:
    LCDPaint(LCDDriver& driver, uint16_t h, uint16_t w);
    void paintPoint(Point2d& pt, PixelWidth px_width, Color color);
};

#endif /* __TOUCAN_LCD_GRAPHICS_H__ */
