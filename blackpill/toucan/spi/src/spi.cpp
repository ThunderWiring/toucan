#include "spi.hpp"

SPI::SPI(): spi_struct({})  {
  spi_default_para_init(&spi_struct);
}