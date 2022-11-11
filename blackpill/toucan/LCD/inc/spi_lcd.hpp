#ifndef __SPI_LCD_H__
#define __SPI_LCD_H__

#include "at32f403a_407_spi.h"
#include "at32f403a_407_crm.h"
#include "delay.h"
#include "gpio_pins.hpp"

#define LCD_1IN28_HEIGHT 240
#define LCD_1IN28_WIDTH 240

#define LCD_PIN_DIN PA7 // PA7 spi data in (MOSI)
#define LCD_PIN_CLK PA5 // PA5 spi clock 
#define LCD_PIN_CS  PB6 // PB6 chip select (low active)
#define LCD_PIN_DC  PA8 // PA8 Data/Command selection (high for data, low for command)
#define LCD_PIN_RST PA9 // PA9 reset (low active)
#define LCD_PIN_BL  PB13 // PB13 back light - pwm (or connected directly to the 3.3v)

/**
 * @brief The controller can send either data or command, 
 * and this config is controlled by the DC pin
 */
typedef enum  {COMMAND = 0, DATA = 1} LCDDataType;
typedef enum {HORIZONTAL = 0, VERTICAL = 1} LCDOrientation;

/**
 * @brief 1.28 inch round screen
 * 
 */
class RoundLCD {
  private:
    GPIOPin din, clk, cs, dc, rst, bl;
    void init_spi();
  public:
    RoundLCD();
};
#endif /* __SPI_LCD_H__ */