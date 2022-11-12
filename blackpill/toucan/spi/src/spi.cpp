#include "spi.hpp"


// F_CPU is defined in the makefile as the mcd frequency.
#define SPI1_CLOCK  (F_CPU)
#define SPI2_CLOCK  (F_CPU)
#define SPI3_CLOCK  (F_CPU)


SPI::SPI(SPIMode mode): spi_struct({}), spi_clock(0), spiX(nullptr) {
  spi_default_para_init(&spi_struct);
  setDataMode(mode);
}

void SPI::setDataMode(uint8_t dataMode) {
  switch(dataMode)
    {
    case 0:
        spi_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW;
        spi_struct.clock_phase = SPI_CLOCK_PHASE_1EDGE;
        break;
    case 1:
        spi_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW;
        spi_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
        break;
    case 2:
        spi_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;
        spi_struct.clock_phase = SPI_CLOCK_PHASE_1EDGE;
        break;
    case 3:
        spi_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;
        spi_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
        break;
    default:
        return;
    }
}

void SPI::init(
  spi_type* spi_x,
  spi_transmission_mode_type transmission_mode,
  spi_master_slave_mode_type master_slave_mode,
  spi_first_bit_type first_bit_transmission,
  spi_frame_bit_num_type frame_bit_num,
  spi_cs_mode_type cs_mode_selection) {
  set_spi_clock(spi_x);
  spi_struct.transmission_mode = transmission_mode;
  spi_struct.master_slave_mode = master_slave_mode;
  spi_struct.first_bit_transmission = first_bit_transmission;
  spi_struct.frame_bit_num = frame_bit_num;
  spi_struct.cs_mode_selection = cs_mode_selection;
}

void SPI::begin() {
  spi_init(spiX, &spi_struct);
  spi_enable(spiX, TRUE);
}

void SPI::set_spi_clock(spi_type* spi_x) {
  spiX = spi_x;
  spi_i2s_reset(spi_x);
  if(spi_x == SPI1) {
      spi_clock = SPI1_CLOCK;
      crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);
      // pinMode(PA5, OUTPUT_AF_PP);
      // pinMode(PA6, OUTPUT_AF_PP);
      // pinMode(PA7, OUTPUT_AF_PP);
  } else if(spi_x == SPI2) {
      spi_clock = SPI2_CLOCK;
      crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
      // pinMode(PB13, OUTPUT_AF_PP);
      // pinMode(PB14, OUTPUT_AF_PP);
      // pinMode(PB15, OUTPUT_AF_PP);

  } else if(spi_x == SPI3) {
      spi_clock = SPI3_CLOCK;
      crm_periph_clock_enable(CRM_SPI3_PERIPH_CLOCK, TRUE);
      // pinMode(PB3, OUTPUT_AF_PP);
      // pinMode(PB4, OUTPUT_AF_PP);
      // pinMode(PB5, OUTPUT_AF_PP);
  }
}

void SPI::setClockDivider(uint32_t clk_div) {
  if(clk_div == 0) {
    clk_div = 1;
  }
  #if SPI_CLASS_AVR_COMPATIBILITY_MODE
    setClock(16000000 / clk_div); // AVR:16MHz
  #else
    setClock(spi_clock / clk_div);
  #endif
}

void SPI::setClock(uint32_t clock) {
  if(clock == 0) {
    return;
  }
  static const spi_mclk_freq_div_type mclk_freq_div_map[] = {
        SPI_MCLK_DIV_2,
        SPI_MCLK_DIV_2,
        SPI_MCLK_DIV_4,
        SPI_MCLK_DIV_8,
        SPI_MCLK_DIV_16,
        SPI_MCLK_DIV_32,
        SPI_MCLK_DIV_64,
        SPI_MCLK_DIV_128,
        SPI_MCLK_DIV_256,
        SPI_MCLK_DIV_512,
        SPI_MCLK_DIV_1024,
    };
    const uint8_t mapSize = 
        sizeof(mclk_freq_div_map) / sizeof(mclk_freq_div_map[0]);
    uint32_t clockDiv = spi_clock / clock;
    uint8_t mapIndex = 0;

    while(clockDiv > 1) {
        clockDiv = clockDiv >> 1;
        mapIndex++;
    }
    if(mapIndex >= mapSize) {
        mapIndex = mapSize - 1;
    }

    spi_init_struct.mclk_freq_division = mclk_freq_div_map[mapIndex];
    spi_init(spiX, &spi_init_struct);
    spi_enable(spiX, TRUE);
}

uint8_t SPI::transfer(uint8_t data) {
  SPI_I2S_RXDATA_VOLATILE(spiX);
    SPI_I2S_TXDATA(spiX, data);
    SPI_I2S_WAIT_TX(spiX);
    SPI_I2S_WAIT_BUSY(spiX);
    return (uint8_t)SPI_I2S_RXDATA(spiX);
}