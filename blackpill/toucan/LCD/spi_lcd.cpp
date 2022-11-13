#include "spi_lcd.hpp"

RoundLCD::RoundLCD(uint16_t h, uint16_t w) : 
      din(GPIOPin(LCD_PIN_DIN, OUTPUT_AF_PP)), // not used
      clk(GPIOPin(LCD_PIN_CLK, OUTPUT_AF_PP)), // not used
      cs(GPIOPin(LCD_PIN_CS, OUTPUT)),
      dc(GPIOPin(LCD_PIN_DC, OUTPUT)),
      rst(GPIOPin(LCD_PIN_RST, OUTPUT)),
      bl(GPIOPin(LCD_PIN_BL, PWM)),
      spi(SPI(SPI1, SPI_MODE0)),
      height(h),
      width(w) { 
  bl.PWMWrite(140);
  init_spi();
}

void RoundLCD::init_spi() {
  spi.init(
    SPI_MODE0,
    SPI_TRANSMIT_FULL_DUPLEX,
    SPI_MODE_MASTER,
    SPI_FIRST_BIT_MSB,
    SPI_FRAME_8BIT,
    SPI_CS_SOFTWARE_MODE,
    SPI_MCLK_DIV_8);
  spi.begin();
}

void RoundLCD::reset() {
  cs.digitalWrite(LOW);
  delay_ms(100);
  rst.digitalWrite(LOW);
  delay_ms(100);
  rst.digitalWrite(HIGH);
  delay_ms(100);
}

void RoundLCD::send_command(uint8_t cmd) {
 cs.digitalWrite(LOW);
 dc.digitalWrite(LOW);
 spi.transfer(cmd);
}

void RoundLCD::send_8bit_data(uint8_t data) {
  cs.digitalWrite(LOW);
  dc.digitalWrite(HIGH);
  spi.transfer(data);
  cs.digitalWrite(HIGH);
}

void RoundLCD::send_16bit_data(uint16_t data) {
  cs.digitalWrite(LOW);
  dc.digitalWrite(HIGH);
  spi.transfer(data >> 8);
  spi.transfer(data);
  cs.digitalWrite(HIGH);
}

void RoundLCD::initLCD() {
  reset();
  init_lcd_driver();
}

void RoundLCD::setBackLight(uint16_t brightness) {
  bl.analogWrite(brightness);
}

void RoundLCD::clearDisplay() {
  uint16_t i,j;    
  set_cursor(0, 0, width - 1,height - 1);
  for(i = 0; i < width; i++){
    for(j = 0; j < height; j++){
      send_16bit_data(BLACK);
    }
   }
}

void RoundLCD::set_cursor(
  uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end) {
  send_command(0x2a);
  send_8bit_data(0x00);
  send_8bit_data(x_start);
  send_8bit_data(0x00);  
  send_8bit_data(x_end);/*********Xend-1********/
  
  send_command(0x2b);
  send_8bit_data(0x00);
  send_8bit_data(y_start);
  send_8bit_data(0x00);
  send_8bit_data(y_end);

  send_command(0x2c);
}

void RoundLCD::init_lcd_driver() {
  send_command(0xEF);
	send_command(0xEB);
	send_8bit_data(0x14); 
	
  send_command(0xFE);			 
	send_command(0xEF); 

	send_command(0xEB);	
	send_8bit_data(0x14); 

	send_command(0x84);			
	send_8bit_data(0x40); 

	send_command(0x85);			
	send_8bit_data(0xFF); 

	send_command(0x86);			
	send_8bit_data(0xFF); 

	send_command(0x87);			
	send_8bit_data(0xFF);

	send_command(0x88);			
	send_8bit_data(0x0A);

	send_command(0x89);			
	send_8bit_data(0x21); 

	send_command(0x8A);			
	send_8bit_data(0x00); 

	send_command(0x8B);			
	send_8bit_data(0x80); 

	send_command(0x8C);			
	send_8bit_data(0x01); 

	send_command(0x8D);			
	send_8bit_data(0x01); 

	send_command(0x8E);			
	send_8bit_data(0xFF); 

	send_command(0x8F);			
	send_8bit_data(0xFF); 


	send_command(0xB6);
	send_8bit_data(0x00);
	send_8bit_data(0x20);

	send_command(0x36);
	send_8bit_data(0x08);

	send_command(0x3A);			
	send_8bit_data(0x05); 


	send_command(0x90);			
	send_8bit_data(0x08);
	send_8bit_data(0x08);
	send_8bit_data(0x08);
	send_8bit_data(0x08); 

	send_command(0xBD);			
	send_8bit_data(0x06);
	
	send_command(0xBC);			
	send_8bit_data(0x00);	

	send_command(0xFF);			
	send_8bit_data(0x60);
	send_8bit_data(0x01);
	send_8bit_data(0x04);

	send_command(0xC3);			
	send_8bit_data(0x13);
	send_command(0xC4);			
	send_8bit_data(0x13);

	send_command(0xC9);			
	send_8bit_data(0x22);

	send_command(0xBE);			
	send_8bit_data(0x11); 

	send_command(0xE1);			
	send_8bit_data(0x10);
	send_8bit_data(0x0E);

	send_command(0xDF);			
	send_8bit_data(0x21);
	send_8bit_data(0x0c);
	send_8bit_data(0x02);

	send_command(0xF0);   
	send_8bit_data(0x45);
	send_8bit_data(0x09);
	send_8bit_data(0x08);
	send_8bit_data(0x08);
	send_8bit_data(0x26);
 	send_8bit_data(0x2A);

 	send_command(0xF1);    
 	send_8bit_data(0x43);
 	send_8bit_data(0x70);
 	send_8bit_data(0x72);
 	send_8bit_data(0x36);
 	send_8bit_data(0x37);  
 	send_8bit_data(0x6F);


 	send_command(0xF2);   
 	send_8bit_data(0x45);
 	send_8bit_data(0x09);
 	send_8bit_data(0x08);
 	send_8bit_data(0x08);
 	send_8bit_data(0x26);
 	send_8bit_data(0x2A);

 	send_command(0xF3);   
 	send_8bit_data(0x43);
 	send_8bit_data(0x70);
 	send_8bit_data(0x72);
 	send_8bit_data(0x36);
 	send_8bit_data(0x37); 
 	send_8bit_data(0x6F);

	send_command(0xED);	
	send_8bit_data(0x1B); 
	send_8bit_data(0x0B); 

	send_command(0xAE);			
	send_8bit_data(0x77);
	
	send_command(0xCD);			
	send_8bit_data(0x63);		


	send_command(0x70);			
	send_8bit_data(0x07);
	send_8bit_data(0x07);
	send_8bit_data(0x04);
	send_8bit_data(0x0E); 
	send_8bit_data(0x0F); 
	send_8bit_data(0x09);
	send_8bit_data(0x07);
	send_8bit_data(0x08);
	send_8bit_data(0x03);

	send_command(0xE8);			
	send_8bit_data(0x34);

	send_command(0x62);			
	send_8bit_data(0x18);
	send_8bit_data(0x0D);
	send_8bit_data(0x71);
	send_8bit_data(0xED);
	send_8bit_data(0x70); 
	send_8bit_data(0x70);
	send_8bit_data(0x18);
	send_8bit_data(0x0F);
	send_8bit_data(0x71);
	send_8bit_data(0xEF);
	send_8bit_data(0x70); 
	send_8bit_data(0x70);

	send_command(0x63);			
	send_8bit_data(0x18);
	send_8bit_data(0x11);
	send_8bit_data(0x71);
	send_8bit_data(0xF1);
	send_8bit_data(0x70); 
	send_8bit_data(0x70);
	send_8bit_data(0x18);
	send_8bit_data(0x13);
	send_8bit_data(0x71);
	send_8bit_data(0xF3);
	send_8bit_data(0x70); 
	send_8bit_data(0x70);

	send_command(0x64);			
	send_8bit_data(0x28);
	send_8bit_data(0x29);
	send_8bit_data(0xF1);
	send_8bit_data(0x01);
	send_8bit_data(0xF1);
	send_8bit_data(0x00);
	send_8bit_data(0x07);

	send_command(0x66);			
	send_8bit_data(0x3C);
	send_8bit_data(0x00);
	send_8bit_data(0xCD);
	send_8bit_data(0x67);
	send_8bit_data(0x45);
	send_8bit_data(0x45);
	send_8bit_data(0x10);
	send_8bit_data(0x00);
	send_8bit_data(0x00);
	send_8bit_data(0x00);

	send_command(0x67);			
	send_8bit_data(0x00);
	send_8bit_data(0x3C);
	send_8bit_data(0x00);
	send_8bit_data(0x00);
	send_8bit_data(0x00);
	send_8bit_data(0x01);
	send_8bit_data(0x54);
	send_8bit_data(0x10);
	send_8bit_data(0x32);
	send_8bit_data(0x98);

	send_command(0x74);			
	send_8bit_data(0x10);	
	send_8bit_data(0x85);	
	send_8bit_data(0x80);
	send_8bit_data(0x00); 
	send_8bit_data(0x00); 
	send_8bit_data(0x4E);
	send_8bit_data(0x00);					
	
  send_command(0x98);			
	send_8bit_data(0x3e);
	send_8bit_data(0x07);

	send_command(0x35);	
	send_command(0x21);

	send_command(0x11);
	delay_ms(120);
	send_command(0x29);
	delay_ms(20);
}