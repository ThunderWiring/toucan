#ifndef __TOUCAN_SPI_H__
#define __TOUCAN_SPI_H__

#include "gpio_pins.hpp"
#include "at32f403a_407.h"

#define SPI_I2S_GET_FLAG(spix, SPI_I2S_FLAG) (spix->sts & SPI_I2S_FLAG)
#define SPI_I2S_RXDATA(spix)                 (spix->dt)
#define SPI_I2S_RXDATA_VOLATILE(spix)        do{ volatile uint16_t vn = SPI_I2S_RXDATA(spix); vn = vn; } while(0)
#define SPI_I2S_TXDATA(spix, data)           (spix->dt = (data))
#define SPI_I2S_WAIT_RX(spix)                do{ while (!SPI_I2S_GET_FLAG(spix, SPI_I2S_RDBF_FLAG)); } while(0)
#define SPI_I2S_WAIT_TX(spix)                do{ while (!SPI_I2S_GET_FLAG(spix, SPI_I2S_TDBE_FLAG)); } while(0)
#define SPI_I2S_WAIT_BUSY(spix)              do{ while (SPI_I2S_GET_FLAG(spix,  SPI_I2S_BF_FLAG));   } while(0)


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
    void set_spi_clock();
  public:
    SPI(spi_type* spi_x, SPIMode mode);

    void init(
      SPIMode mode,
      spi_transmission_mode_type transmission_mode,
      spi_master_slave_mode_type master_slave_mode,
      spi_first_bit_type first_bit_transmission,
      spi_frame_bit_num_type frame_bit_num,
      spi_cs_mode_type cs_mode_selection,
      spi_mclk_freq_div_type clk_freq_div
    );

    /**
     * @brief Enables the clock and setup the ends for communication.
     */
    void begin();
    uint8_t transfer(uint8_t data);
};

#endif /* __TOUCAN_SPI_H__ */