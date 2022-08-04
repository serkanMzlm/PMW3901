#ifndef __SPI_
#define __SPI_
#include <stdint.h>
extern int pmw3901_init(int fd);
extern void pmw3901_readMotion(int fd, int16_t *deltaX, int16_t *deltaY);

#endif 
