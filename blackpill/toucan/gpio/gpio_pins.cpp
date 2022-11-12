#include "gpio_pins.hpp"

GPIOPin::GPIOPin(PinType p, PinMode mode): pin(p), pin_mode(mode) {
  if (IS_VALID_PIN(p)) {
    pin_info = PIN_MAP[p];
  }
  init_pin();
}

void GPIOPin::init_pin() {
  // TODO: add handling for analog (adc) and pwm modes
  GPIOx_Init(
    PIN_MAP[pin].GPIOx,
    PIN_MAP[pin].GPIO_PINS_x,
    pin_mode,
    GPIO_DRIVE_STRENGTH_STRONGER
  );
}

void GPIOPin::GPIOx_Init(
    gpio_type* GPIOx,
    uint16_t GPIO_Pin_x,
    PinMode Mode,
    gpio_drive_type GPIO_Drive_x
) {
    gpio_init_type gpio_init_struct;
    crm_periph_clock_type CRM_GPIOx_PERIPH_CLOCK;

    if(GPIOx == GPIOA)     CRM_GPIOx_PERIPH_CLOCK = CRM_GPIOA_PERIPH_CLOCK;
    else if(GPIOx == GPIOB)CRM_GPIOx_PERIPH_CLOCK = CRM_GPIOB_PERIPH_CLOCK;
    else if(GPIOx == GPIOC)CRM_GPIOx_PERIPH_CLOCK = CRM_GPIOC_PERIPH_CLOCK;
    else if(GPIOx == GPIOD)CRM_GPIOx_PERIPH_CLOCK = CRM_GPIOD_PERIPH_CLOCK;
#ifdef GPIOE
    else if(GPIOx == GPIOE)CRM_GPIOx_PERIPH_CLOCK = CRM_GPIOE_PERIPH_CLOCK;
#endif /*GPIOE*/
#ifdef GPIOF
    else if(GPIOx == GPIOF)CRM_GPIOx_PERIPH_CLOCK = CRM_GPIOF_PERIPH_CLOCK;
#endif /*GPIOF*/
#ifdef GPIOG
    else if(GPIOx == GPIOG)CRM_GPIOx_PERIPH_CLOCK = CRM_GPIOG_PERIPH_CLOCK;
#endif /*GPIOG*/
    else return;
	
	gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_pins = GPIO_Pin_x;
    gpio_init_struct.gpio_drive_strength = GPIO_Drive_x;
    
    if(Mode == INPUT)
    {
        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    }
    else if(Mode == INPUT_PULLUP)
    {
        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    }
    else if(Mode == INPUT_PULLDOWN)
    {
        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
    }
    else if(Mode == INPUT_ANALOG)
    {
        gpio_init_struct.gpio_mode = GPIO_MODE_ANALOG;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    }
    else if(Mode == OUTPUT)
    {
        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    }
    else if(Mode == OUTPUT_OPEN_DRAIN)
    {
        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
    }
    else if(Mode == OUTPUT_AF_PP)
    {
        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    }
    else if(Mode == OUTPUT_AF_OD)
    {
        gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
    }
    else
    {
        return;
    }

    crm_periph_clock_enable(CRM_GPIOx_PERIPH_CLOCK, TRUE);
    gpio_init(GPIOx, &gpio_init_struct);
}

void GPIOPin::digitalWrite(DigitalSignal value) {
  if (value == HIGH) {
    pin_info.GPIOx->scr = pin_info.GPIO_PINS_x;
  } else {
    pin_info.GPIOx->clr = pin_info.GPIO_PINS_x;
  }
}

DigitalSignal GPIOPin::digitalRead() {
  pin_info.GPIOx->idt & pin_info.GPIO_PINS_x != 0 ? HIGH : LOW;
}

void GPIOPin::analogWrite(uint8_t value) {
  if (!is_pwm()) {
    return;
  }
  PWMWrite(value);
}

uint16_t GPIOPin::analogRead() {
  if (!is_ADC()) {
    return 0;
  }
  adc_ordinary_channel_set(
    pin_info.ADCx, (adc_channel_select_type)pin_info.ADC_Channel, 1, ADC_SAMPLETIME_41_5);

  adc_ordinary_software_trigger_enable(pin_info.ADCx, TRUE);
  while(!adc_flag_get(pin_info.ADCx, ADC_CCE_FLAG));
  return adc_ordinary_conversion_data_get(pin_info.ADCx);
}

bool GPIOPin::is_pwm() const {
  return pin_info.TMRx != nullptr && pin_info.TimerChannel != 0;
}

bool GPIOPin::is_ADC() const {
  return pin_info.ADCx != nullptr && pin_info.ADC_Channel != ADC_CHANNEL_X;
}

void GPIOPin::PWMWrite(uint32_t value) {
  set_compare_timer(value);
}

void GPIOPin::set_compare_timer(uint32_t value) {
    switch(pin_info.TimerChannel) {
    case 1:
        tmr_channel_value_set(pin_info.TMRx, TMR_SELECT_CHANNEL_1, value);
        break;
    case 2:
        tmr_channel_value_set(pin_info.TMRx, TMR_SELECT_CHANNEL_2, value);
        break;
    case 3:
        tmr_channel_value_set(pin_info.TMRx, TMR_SELECT_CHANNEL_3, value);
        break;
    case 4:
        tmr_channel_value_set(pin_info.TMRx, TMR_SELECT_CHANNEL_4, value);
        break;
    default:
        break;
    }
}