#include "at32f403a_407_clock.h"
#include "delay.h"
#include "spim.h"
#include "usbd_core.h"
#include "usbd_int.h"
#include "custom_hid_class.h"
#include "custom_hid_desc.h"
#include "board.h"

#include "robot_driver.hpp"

#ifdef __cplusplus
extern "C" {
#endif

Robot* robot = Robot_getInstance();

int main(void) {
  system_clock_config();
  delay_init();
  button_init();
  button_exint_init();
  led_init();

  Robot_init(robot);
  
  while (1)
  {
    led_toggle();
    delay_ms( DELAY);
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
  usbd_irq_handler(robot->getUsbDevice());
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
