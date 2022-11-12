#ifndef __TOUCAN_GPIO_PINS_H__
#define __TOUCAN_GPIO_PINS_H__

#include "at32f403a_407.h"

/** Number of supported GPIO Pins. This number varies per board.
 * For example, the blackpill doesn't has all the port C pins.
 * This value is 16 * 3 = 48, 3 = ports A, B, C.
 * TODO: Claulate this number while taking into consideration the board/chip.
*/
#define GPIO_PINS_COUNT 48
#define ADC_CHANNEL_X ((uint8_t)0xFF)

#define IS_VALID_PIN(pin) pin < GPIO_PINS_COUNT
// #define IS_ADC_PIN(Pin) (IS_VALID_PIN(Pin) && PIN_MAP[Pin].ADCx != nullptr && PIN_MAP[Pin].ADC_Channel  != ADC_CHANNEL_X)
// #define IS_PWM_PIN(Pin) (IS_VALID_PIN(Pin) && PIN_MAP[Pin].TMRx != nullptr && PIN_MAP[Pin].TimerChannel != 0)


/** GPIO Pins supported by the MCU board. */
typedef enum {
  PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
  PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
  PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
} PinType;

typedef enum {HIGH = (uint8_t)1, LOW = !HIGH} DigitalSignal;

typedef enum {
    INPUT,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    INPUT_ANALOG,
    INPUT_ANALOG_DMA,
    OUTPUT,
    OUTPUT_OPEN_DRAIN,
    OUTPUT_AF_OD,
    OUTPUT_AF_PP,
    PWM
} PinMode;

struct PinInfo {
    gpio_type* GPIOx;
    tmr_type* TMRx;
    adc_type* ADCx;
    uint16_t GPIO_PINS_x;
    uint8_t TimerChannel;
    uint8_t ADC_Channel;
};


static const PinInfo PIN_MAP[GPIO_PINS_COUNT] =
{
    /*GPIOx TMR_Type  ADC_Type* uint16_t GPIO_PINS_x uint8_t TimerChannel uint8_t ADC_CHANNEL*/
    {GPIOA, TMR2, ADC1,  GPIO_PINS_0, 1, ADC_CHANNEL_0}, /* PA0 */
    {GPIOA, TMR2, ADC1,  GPIO_PINS_1, 2, ADC_CHANNEL_1}, /* PA1 */
    {GPIOA, TMR2, ADC1,  GPIO_PINS_2, 3, ADC_CHANNEL_2}, /* PA2 */
    {GPIOA, TMR2, ADC1,  GPIO_PINS_3, 4, ADC_CHANNEL_3}, /* PA3 */
    {GPIOA, nullptr, ADC1,  GPIO_PINS_4, 0, ADC_CHANNEL_4}, /* PA4 */
    {GPIOA, nullptr, ADC1,  GPIO_PINS_5, 0, ADC_CHANNEL_5}, /* PA5 */
    {GPIOA, TMR3, ADC1,  GPIO_PINS_6, 1, ADC_CHANNEL_6}, /* PA6 */
    {GPIOA, TMR3, ADC1,  GPIO_PINS_7, 2, ADC_CHANNEL_7}, /* PA7 */
    {GPIOA, TMR1, nullptr,  GPIO_PINS_8, 1, ADC_CHANNEL_X}, /* PA8 */
    {GPIOA, TMR1, nullptr,  GPIO_PINS_9, 2, ADC_CHANNEL_X}, /* PA9 */
    {GPIOA, TMR1, nullptr, GPIO_PINS_10, 3, ADC_CHANNEL_X}, /* PA10 */
    {GPIOA, TMR1, nullptr, GPIO_PINS_11, 4, ADC_CHANNEL_X}, /* PA11 */
    {GPIOA, nullptr, nullptr, GPIO_PINS_12, 0, ADC_CHANNEL_X}, /* PA12 */
    {GPIOA, nullptr, nullptr, GPIO_PINS_13, 0, ADC_CHANNEL_X}, /* PA13 */
    {GPIOA, nullptr, nullptr, GPIO_PINS_14, 0, ADC_CHANNEL_X}, /* PA14 */
    {GPIOA, nullptr, nullptr, GPIO_PINS_15, 1, ADC_CHANNEL_X}, /* PA15 */

    {GPIOB, TMR3, ADC1,  GPIO_PINS_0, 3, ADC_CHANNEL_8}, /* PB0 */
    {GPIOB, TMR3, ADC1,  GPIO_PINS_1, 4, ADC_CHANNEL_9}, /* PB1 */
    {GPIOB, nullptr, nullptr,  GPIO_PINS_2, 0, ADC_CHANNEL_X}, /* PB2 */
    {GPIOB, nullptr, nullptr,  GPIO_PINS_3, 2, ADC_CHANNEL_X}, /* PB3 */
    {GPIOB, TMR3, nullptr,  GPIO_PINS_4, 1, ADC_CHANNEL_X}, /* PB4 */
    {GPIOB, TMR3, nullptr,  GPIO_PINS_5, 2, ADC_CHANNEL_X}, /* PB5 */
    {GPIOB, TMR4, nullptr,  GPIO_PINS_6, 1, ADC_CHANNEL_X}, /* PB6 */
    {GPIOB, TMR4, nullptr,  GPIO_PINS_7, 2, ADC_CHANNEL_X}, /* PB7 */
    {GPIOB, TMR4, nullptr,  GPIO_PINS_8, 3, ADC_CHANNEL_X}, /* PB8 */
    {GPIOB, TMR4, nullptr,  GPIO_PINS_9, 4, ADC_CHANNEL_X}, /* PB9 */
    {GPIOB, nullptr, nullptr, GPIO_PINS_10, 3, ADC_CHANNEL_X}, /* PB10 */
    {GPIOB, nullptr, nullptr, GPIO_PINS_11, 4, ADC_CHANNEL_X}, /* PB11 */
    {GPIOB, nullptr, nullptr, GPIO_PINS_12, 0, ADC_CHANNEL_X}, /* PB12 */
    {GPIOB, nullptr, nullptr, GPIO_PINS_13, 0, ADC_CHANNEL_X}, /* PB13 */
#ifdef TMR12
    {GPIOB, TMR12, nullptr, GPIO_PINS_14, 1, ADC_CHANNEL_X},/* PB14 */
#else
    {GPIOB, nullptr, nullptr, GPIO_PINS_14, 0, ADC_Channel_X},/* PB14 */
#endif /*TMR12*/
    {GPIOB, nullptr, nullptr, GPIO_PINS_15, 0, ADC_CHANNEL_X}, /* PB15 */

    {GPIOC, nullptr, ADC1,  GPIO_PINS_0, 0, ADC_CHANNEL_10},/* PC0 */
    {GPIOC, nullptr, ADC1,  GPIO_PINS_1, 0, ADC_CHANNEL_11},/* PC1 */
    {GPIOC, nullptr, ADC1,  GPIO_PINS_2, 0, ADC_CHANNEL_12},/* PC2 */
    {GPIOC, nullptr, ADC1,  GPIO_PINS_3, 0, ADC_CHANNEL_13},/* PC3 */
    {GPIOC, nullptr, ADC1,  GPIO_PINS_4, 0, ADC_CHANNEL_14},/* PC4 */
    {GPIOC, nullptr, ADC1,  GPIO_PINS_5, 0, ADC_CHANNEL_15},/* PC5 */
    {GPIOC, nullptr, nullptr,  GPIO_PINS_6, 1, ADC_CHANNEL_X}, /* PC6 */
    {GPIOC, nullptr, nullptr,  GPIO_PINS_7, 2, ADC_CHANNEL_X}, /* PC7 */
    {GPIOC, nullptr, nullptr,  GPIO_PINS_8, 3, ADC_CHANNEL_X}, /* PC8 */
    {GPIOC, nullptr, nullptr,  GPIO_PINS_9, 4, ADC_CHANNEL_X}, /* PC9 */
    {GPIOC, nullptr, nullptr, GPIO_PINS_10, 0, ADC_CHANNEL_X}, /* PC10 */
    {GPIOC, nullptr, nullptr, GPIO_PINS_11, 0, ADC_CHANNEL_X}, /* PC11 */
    {GPIOC, nullptr, nullptr, GPIO_PINS_12, 0, ADC_CHANNEL_X}, /* PC12 */
    {GPIOC, nullptr, nullptr, GPIO_PINS_13, 0, ADC_CHANNEL_X}, /* PC13 */
    {GPIOC, nullptr, nullptr, GPIO_PINS_14, 0, ADC_CHANNEL_X}, /* PC14 */
    {GPIOC, nullptr, nullptr, GPIO_PINS_15, 0, ADC_CHANNEL_X}, /* PC15 */
};

class GPIOPin {
  private:
    PinType pin;
    PinMode pin_mode;
    PinInfo pin_info;
    
    bool is_pwm() const;
    bool is_ADC() const;
    void set_compare_timer(uint32_t value);
    void init_pin();
    void GPIOx_Init(
        gpio_type* GPIOx,
        uint16_t GPIO_Pin_x,
        PinMode Mode,
        gpio_drive_type GPIO_Drive_x
    );
  public:
    GPIOPin(PinType p, PinMode mode);

    DigitalSignal digitalRead();
    uint16_t analogRead();
    void digitalWrite(DigitalSignal value);
    void analogWrite(uint8_t value);
    void PWMWrite(uint32_t value);
};

#endif /*__TOUCAN_GPIO_PINS_H__*/