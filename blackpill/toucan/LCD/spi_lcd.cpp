#include "spi_lcd.hpp"

RoundLCD::RoundLCD(uint16_t h, uint16_t w) : 
      bl(GPIOPin(LCD_PIN_BL, PWM)),
      height(h),
      width(w),
      painter(LCDPaint(nullptr, h, w)) { 
  lcd_driver = LCDDriver();
  painter = LCDPaint(&lcd_driver, h, w);
  bl.PWMWrite(140);
}

void RoundLCD::initLCD() {
  lcd_driver.reset();
  lcd_driver.initDriver();
}

void RoundLCD::setBackLight(uint16_t brightness) {
  bl.analogWrite(brightness);
}

void RoundLCD::clearDisplay() {
  uint16_t i,j;    
  lcd_driver.setCursor(0, 0, width - 1,height - 1);
  for(i = 0; i < width; i++){
    for(j = 0; j < height; j++){
      lcd_driver.send16BitData(MAGENTA);
    }
   }
}

void RoundLCD::drawShape(Shape& shape) {
  shape.render(&painter);
}