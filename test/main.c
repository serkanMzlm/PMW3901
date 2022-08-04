#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "spi.h"

static uint8_t mode = 0;
static uint32_t speed = 400000;


int main()
{
	int fd, status;
	int16_t x,y;
	fd = open("/dev/spidev0.0",O_RDWR);
	if(fd<1 )
	{
		printf("can not open file\n");
		return -1;
	}
	if((status=ioctl(fd,SPI_IOC_RD_MODE,&mode))<0)
	{
		printf("can not read SPI mode\n");
		return -1;
	}
	if((status=ioctl(fd,SPI_IOC_WR_MODE,&mode))<0)
	{
		printf("can not set SPI mode\n");
		return -1;
	}
	

	if((status=ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ,&speed))<0)
	{
		printf("can not set SPI speed\n");
		return -1;
	}
	if((status=ioctl(fd,SPI_IOC_RD_MAX_SPEED_HZ,&speed))<0)
	{
		printf("can not read SPI speed\n");
		return -1;
	}

	pmw3901_init(fd);
	while(1)
	{
		usleep(40000);
		pmw3901_readMotion(fd,&x,&y);
		printf("x:%d  |  y:%d\n",x,y);

	}


	return 0;
}
