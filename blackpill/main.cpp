#include "at32f403a_407_clock.h"
#include "delay.h"
#include "spim.h"
#include "usbd_core.h"
#include "usbd_int.h"
#include "custom_hid_class.h"
#include "custom_hid_desc.h"
#include "board.h"

#include "hid_usb_lib.hpp"
#include "spi_lcd.hpp"

extern uint8_t toggle_speed_from_host;
#ifdef __cplusplus
extern "C" {
#endif

uint8_t report_buf[USBD_CUSTOM_IN_MAXPACKET_SIZE];
CustomUSBHID usb = CustomUSBHID();

void testLCD(RoundLCD& lcd) {
  lcd.initLCD();
  lcd.setBackLight(1000);
  lcd.clearDisplay();
  
  Point2d pt1(50,50), pt2(50,80), pt3(70,80);
  Line line1(PX_2X2, RED, pt1, pt2);
  Line line2(PX_1X1, LBBLUE, pt1, pt3);

  lcd.drawShape(line1);
  lcd.drawShape(line2);
}

int main(void) {
  system_clock_config();
  delay_init();
  button_init();
  button_exint_init();
  led_init();

  RoundLCD lcd = RoundLCD(LCD_1IN28_HEIGHT, LCD_1IN28_WIDTH);
  testLCD(lcd);
  
  usb.initUSB();
  usb.connect();
  
  while (1)
  {
    led_toggle();
    delay_ms(toggle_speed_from_host * DELAY);
  }
  return 0;
}

/**
 * @brief  this function handles usb interrupt.
 * @param  none
 * @retval none
 */
void USBFS_L_CAN1_RX0_IRQHandler(void)
{
  usbd_irq_handler(usb.getDevice());
}

/**
 * @brief  usb delay millisecond function.
 * @param  ms: number of millisecond delay
 * @retval none
 */
void usb_delay_ms(uint32_t ms)
{
  /* user can define self delay function */
  delay_ms(ms);
}

/**
 * @brief  usb delay microsecond function.
 * @param  us: number of microsecond delay
 * @retval none
 */
void usb_delay_us(uint32_t us)
{
  delay_us(us);
}

#ifdef __cplusplus
}
#endif
