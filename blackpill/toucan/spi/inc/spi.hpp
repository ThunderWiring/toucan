#ifndef __TOUCAN_SPI_H__
#define __TOUCAN_SPI_H__

#include "at32f403a_407.h"

class SPI {
  private:
    spi_init_type spi_struct;

  public:
    SPI();

    void init(
      spi_type* spi_x,
      spi_transmission_mode_type transmission_mode,
      spi_master_slave_mode_type master_slave_mode,
      spi_mclk_freq_div_type mclk_freq_division,
      spi_first_bit_type first_bit_transmission,
      spi_frame_bit_num_type frame_bit_num,
      spi_clock_polarity_type clock_polarity,
      spi_clock_phase_type clock_phase,
      spi_cs_mode_type cs_mode_selection,
    );

    /**
     * @brief Enables the clock and setup the ends for communication.
     * 
     */
    void begin();
};

#endif /* __TOUCAN_SPI_H__ */