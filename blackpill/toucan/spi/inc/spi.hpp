#ifndef __TOUCAN_SPI_H__
#define __TOUCAN_SPI_H__

#include "gpio_pins.hpp"
#include "at32f403a_407.h"

typedef enum
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3
} SPIMode;

class SPI {
  private:
    spi_init_type spi_struct;
    uint32_t spi_clock;
    spi_type* spiX;

    void setDataMode(uint8_t dataMode);
    void set_spi_clock(spi_type* spi_x);
    void setClock(uint32_t clock);
  public:
    SPI(SPIMode mode);

    void init(
      spi_type* spi_x,
      spi_transmission_mode_type transmission_mode,
      spi_master_slave_mode_type master_slave_mode,
      spi_first_bit_type first_bit_transmission,
      spi_frame_bit_num_type frame_bit_num,
      spi_cs_mode_type cs_mode_selection
    );

    /**
     * @brief Enables the clock and setup the ends for communication.
     */
    void begin();
    void setClockDivider(uint32_t clk_div);
};

#endif /* __TOUCAN_SPI_H__ */