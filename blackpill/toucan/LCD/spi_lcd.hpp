#ifndef __SPI_LCD_H__
#define __SPI_LCD_H__

#include "shapes.hpp"
#include "lcd_driver.hpp"

static constexpr uint16_t LCD_1IN28_HEIGHT = 240;
static constexpr uint16_t LCD_1IN28_WIDTH = 240;
static constexpr uint8_t LCD_BACKLIGHT = 1000;
/**
 * @brief 1.28 inch round screen
 * 
 */
class RoundLCD {
  private:
    GPIOPin bl;
    uint16_t height, width;
    LCDDriver lcd_driver;
    LCDPaint painter;

  public:
    RoundLCD(uint16_t h, uint16_t w);
    
    /**
     * @brief Initializes the LCD driver for preparation to display content.
     */
    void initLCD();   

    void setBackLight(uint16_t brightness);

    /** Clears all pixels. */
    void clearDisplay();

    void drawShape(Shape& shape);
};
#endif /* __SPI_LCD_H__ */