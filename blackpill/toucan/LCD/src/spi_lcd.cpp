#include "spi_lcd.hpp"

RoundLCD::RoundLCD() : din(GPIOPin(LCD_PIN_DIN, OUTPUT)),
                       clk(GPIOPin(LCD_PIN_CLK, OUTPUT)),
                       cs(GPIOPin(LCD_PIN_CS, OUTPUT)),
                       dc(GPIOPin(LCD_PIN_DC, OUTPUT)),
                       rst(GPIOPin(LCD_PIN_RST, OUTPUT)),
                       bl(GPIOPin(LCD_PIN_BL, PWM)) { 
  bl.PWMWrite(140);
  init_spi();
}

void RoundLCD::init_spi() {

}
