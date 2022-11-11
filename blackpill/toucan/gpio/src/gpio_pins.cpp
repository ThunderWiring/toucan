#include "gpio_pins.hpp"


GPIOPin::GPIOPin(PinType p, PinMode mode): pin(p), pin_mode(mode) {
  if (IS_VALID_PIN(p)) {
    pin_info = PIN_MAP[p];
  }
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