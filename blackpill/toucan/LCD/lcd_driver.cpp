#include "lcd_driver.hpp"


LCDDriver::LCDDriver() :
    din(GPIOPin(LCD_PIN_DIN, OUTPUT_AF_PP)), // not used but needed for SPI protocole
    clk(GPIOPin(LCD_PIN_CLK, OUTPUT_AF_PP)), // not used but needed for SPI protocole
    cs(GPIOPin(LCD_PIN_CS, OUTPUT)),
    dc(GPIOPin(LCD_PIN_DC, OUTPUT)),
    rst(GPIOPin(LCD_PIN_RST, OUTPUT)),
    spi(SPI(SPI1, SPI_MODE0)) {
  init_spi();
}

void LCDDriver::init_spi() {
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

void LCDDriver::reset() {
  cs.digitalWrite(LOW);
  delay_ms(100);
  rst.digitalWrite(LOW);
  delay_ms(100);
  rst.digitalWrite(HIGH);
  delay_ms(100);
}

void LCDDriver::sendCommand(uint8_t cmd) {
  cs.digitalWrite(LOW);
  dc.digitalWrite(LOW);
  spi.transfer(cmd);
}

void LCDDriver::send8BitData(uint8_t data) {
  cs.digitalWrite(LOW);
  dc.digitalWrite(HIGH);
  spi.transfer(data);
  cs.digitalWrite(HIGH);
}
  
void LCDDriver::send16BitData(uint16_t data) {
  cs.digitalWrite(LOW);
  dc.digitalWrite(HIGH);
  spi.transfer(data >> 8);
  spi.transfer(data);
  cs.digitalWrite(HIGH);
}

void LCDDriver::setCursor(
  uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end) {
  sendCommand(0x2a);
  send8BitData(0x00);
  send8BitData(x_start);
  send8BitData(0x00);  
  send8BitData(x_end);/*********Xend-1********/
  
  sendCommand(0x2b);
  send8BitData(0x00);
  send8BitData(y_start);
  send8BitData(0x00);
  send8BitData(y_end);

  sendCommand(0x2c);
}

void LCDDriver::initDriver() {
    sendCommand(0xEF);
	sendCommand(0xEB);
	send8BitData(0x14); 
	
  sendCommand(0xFE);			 
	sendCommand(0xEF); 

	sendCommand(0xEB);	
	send8BitData(0x14); 

	sendCommand(0x84);			
	send8BitData(0x40); 

	sendCommand(0x85);			
	send8BitData(0xFF); 

	sendCommand(0x86);			
	send8BitData(0xFF); 

	sendCommand(0x87);			
	send8BitData(0xFF);

	sendCommand(0x88);			
	send8BitData(0x0A);

	sendCommand(0x89);			
	send8BitData(0x21); 

	sendCommand(0x8A);			
	send8BitData(0x00); 

	sendCommand(0x8B);			
	send8BitData(0x80); 

	sendCommand(0x8C);			
	send8BitData(0x01); 

	sendCommand(0x8D);			
	send8BitData(0x01); 

	sendCommand(0x8E);			
	send8BitData(0xFF); 

	sendCommand(0x8F);			
	send8BitData(0xFF); 


	sendCommand(0xB6);
	send8BitData(0x00);
	send8BitData(0x20);

	sendCommand(0x36);
	send8BitData(0x08);

	sendCommand(0x3A);			
	send8BitData(0x05); 


	sendCommand(0x90);			
	send8BitData(0x08);
	send8BitData(0x08);
	send8BitData(0x08);
	send8BitData(0x08); 

	sendCommand(0xBD);			
	send8BitData(0x06);
	
	sendCommand(0xBC);			
	send8BitData(0x00);	

	sendCommand(0xFF);			
	send8BitData(0x60);
	send8BitData(0x01);
	send8BitData(0x04);

	sendCommand(0xC3);			
	send8BitData(0x13);
	sendCommand(0xC4);			
	send8BitData(0x13);

	sendCommand(0xC9);			
	send8BitData(0x22);

	sendCommand(0xBE);			
	send8BitData(0x11); 

	sendCommand(0xE1);			
	send8BitData(0x10);
	send8BitData(0x0E);

	sendCommand(0xDF);			
	send8BitData(0x21);
	send8BitData(0x0c);
	send8BitData(0x02);

	sendCommand(0xF0);   
	send8BitData(0x45);
	send8BitData(0x09);
	send8BitData(0x08);
	send8BitData(0x08);
	send8BitData(0x26);
 	send8BitData(0x2A);

 	sendCommand(0xF1);    
 	send8BitData(0x43);
 	send8BitData(0x70);
 	send8BitData(0x72);
 	send8BitData(0x36);
 	send8BitData(0x37);  
 	send8BitData(0x6F);


 	sendCommand(0xF2);   
 	send8BitData(0x45);
 	send8BitData(0x09);
 	send8BitData(0x08);
 	send8BitData(0x08);
 	send8BitData(0x26);
 	send8BitData(0x2A);

 	sendCommand(0xF3);   
 	send8BitData(0x43);
 	send8BitData(0x70);
 	send8BitData(0x72);
 	send8BitData(0x36);
 	send8BitData(0x37); 
 	send8BitData(0x6F);

	sendCommand(0xED);	
	send8BitData(0x1B); 
	send8BitData(0x0B); 

	sendCommand(0xAE);			
	send8BitData(0x77);
	
	sendCommand(0xCD);			
	send8BitData(0x63);		


	sendCommand(0x70);			
	send8BitData(0x07);
	send8BitData(0x07);
	send8BitData(0x04);
	send8BitData(0x0E); 
	send8BitData(0x0F); 
	send8BitData(0x09);
	send8BitData(0x07);
	send8BitData(0x08);
	send8BitData(0x03);

	sendCommand(0xE8);			
	send8BitData(0x34);

	sendCommand(0x62);			
	send8BitData(0x18);
	send8BitData(0x0D);
	send8BitData(0x71);
	send8BitData(0xED);
	send8BitData(0x70); 
	send8BitData(0x70);
	send8BitData(0x18);
	send8BitData(0x0F);
	send8BitData(0x71);
	send8BitData(0xEF);
	send8BitData(0x70); 
	send8BitData(0x70);

	sendCommand(0x63);			
	send8BitData(0x18);
	send8BitData(0x11);
	send8BitData(0x71);
	send8BitData(0xF1);
	send8BitData(0x70); 
	send8BitData(0x70);
	send8BitData(0x18);
	send8BitData(0x13);
	send8BitData(0x71);
	send8BitData(0xF3);
	send8BitData(0x70); 
	send8BitData(0x70);

	sendCommand(0x64);			
	send8BitData(0x28);
	send8BitData(0x29);
	send8BitData(0xF1);
	send8BitData(0x01);
	send8BitData(0xF1);
	send8BitData(0x00);
	send8BitData(0x07);

	sendCommand(0x66);			
	send8BitData(0x3C);
	send8BitData(0x00);
	send8BitData(0xCD);
	send8BitData(0x67);
	send8BitData(0x45);
	send8BitData(0x45);
	send8BitData(0x10);
	send8BitData(0x00);
	send8BitData(0x00);
	send8BitData(0x00);

	sendCommand(0x67);			
	send8BitData(0x00);
	send8BitData(0x3C);
	send8BitData(0x00);
	send8BitData(0x00);
	send8BitData(0x00);
	send8BitData(0x01);
	send8BitData(0x54);
	send8BitData(0x10);
	send8BitData(0x32);
	send8BitData(0x98);

	sendCommand(0x74);			
	send8BitData(0x10);	
	send8BitData(0x85);	
	send8BitData(0x80);
	send8BitData(0x00); 
	send8BitData(0x00); 
	send8BitData(0x4E);
	send8BitData(0x00);					
	
  sendCommand(0x98);			
	send8BitData(0x3e);
	send8BitData(0x07);

	sendCommand(0x35);	
	sendCommand(0x21);

	sendCommand(0x11);
	delay_ms(120);
	sendCommand(0x29);
	delay_ms(20);
}