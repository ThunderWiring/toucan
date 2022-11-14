#ifndef __SPI_LCD_H__
#define __SPI_LCD_H__

#include "lcd_graphics.hpp"
#include "lcd_driver.hpp"

#define LCD_1IN28_HEIGHT 240
#define LCD_1IN28_WIDTH 240

/**
 * @brief 1.28 inch round screen
 * 
 */
class RoundLCD {
  private:
    GPIOPin bl;
    uint16_t height, width;
    LCDDriver lcd_driver;

  public:
    RoundLCD(uint16_t h, uint16_t w);
    
    /**
     * @brief Initializes the LCD driver for preparation to display content.
     */
    void initLCD();   

    void setBackLight(uint16_t brightness);

    /** Clears all pixels. */
    void clearDisplay();
};
#endif /* __SPI_LCD_H__ */