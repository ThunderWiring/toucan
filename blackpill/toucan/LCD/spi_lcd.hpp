#ifndef __SPI_LCD_H__
#define __SPI_LCD_H__

#include "at32f403a_407_spi.h"
#include "at32f403a_407_crm.h"
#include "delay.h"
#include "gpio_pins.hpp"
#include "spi.hpp"
#include "lcd_graphics.hpp"

#define LCD_1IN28_HEIGHT 240
#define LCD_1IN28_WIDTH 240

#define LCD_PIN_DIN PA7 // PA7 spi data in (MOSI)
#define LCD_PIN_CLK PA5 // PA5 spi clock 
#define LCD_PIN_CS  PB6 // PB6 chip select (low active)
#define LCD_PIN_DC  PA8 // PA8 Data/Command selection (high for data, low for command)
#define LCD_PIN_RST PA9 // PA9 reset (low active)
#define LCD_PIN_BL  PB13 // PB13 back light - pwm (or connected directly to the 3.3v)


class LCDDriver {
  private:
    GPIOPin din, clk, cs, dc, rst;
    SPI spi;

    void init_spi();

  public:
    LCDDriver();

    /** writes a command to the LCD driver */
    void sendCommand(uint8_t cmd);
    /** writes a byte to the LCD driver */
    void send8BitData(uint8_t data);
    void send16BitData(uint16_t data);

    void reset();
    void initDriver();
    void setCursor(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
};

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