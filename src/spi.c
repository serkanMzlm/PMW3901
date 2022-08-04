#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "spi.h"

static uint8_t bwp=8;
static uint16_t delay=1;
static uint32_t speed=400000;

static uint8_t registerRead(int fd, uint8_t reg)
{
    uint8_t tx_buff[2],rx_buff[2];
    int status;

    tx_buff[0]= reg;
    tx_buff[1]= 0;
    struct spi_ioc_transfer spi = {
        .tx_buf = (unsigned long) tx_buff,
        .rx_buf = (unsigned long) rx_buff,
        .len = 2,
        .delay_usecs = delay,
        .speed_hz = speed,
        .bits_per_word = bwp,
    };

    if ((status = ioctl(fd, SPI_IOC_MESSAGE(1),&spi))<1)
    {
        printf("can't send spi message");
        return 0;
    }

    return rx_buff[1];

}

static uint8_t registerWrite(int fd, uint8_t reg, uint8_t value)
{
    int status;
    uint8_t tx_buff[2];
    tx_buff[0] = reg | 0x80;
    tx_buff[1] = value;
    struct spi_ioc_transfer spi = {

        .tx_buf = (unsigned long) tx_buff,
        .rx_buf = 0,
        .len = 2,
        .delay_usecs = delay,
        .speed_hz = speed,
        .bits_per_word = bwp,
    };

    if((status = ioctl(fd, SPI_IOC_MESSAGE(1),&spi))<1)
    {
        printf("can't send spi message");
        return 0;
    }

}

static void initRegisters(int fd) {

	registerWrite(fd, 0x7F, 0x00);
	registerWrite(fd, 0x61, 0xAD);
	registerWrite(fd, 0x7F, 0x03);
	registerWrite(fd, 0x40, 0x00);
	registerWrite(fd, 0x7F, 0x05);
	registerWrite(fd, 0x41, 0xB3);
	registerWrite(fd, 0x43, 0xF1);
	registerWrite(fd, 0x45, 0x14);
	registerWrite(fd, 0x5B, 0x32);
	registerWrite(fd, 0x5F, 0x34);
	registerWrite(fd, 0x7B, 0x08);
	registerWrite(fd, 0x7F, 0x06);
	registerWrite(fd, 0x44, 0x1B);
	registerWrite(fd, 0x40, 0xBF);
	registerWrite(fd, 0x4E, 0x3F);
	/////////////////////////////////////////////////////////////////////
	registerWrite(fd, 0x7F, 0x08);
	registerWrite(fd, 0x65, 0x20);
	registerWrite(fd, 0x6A, 0x18);
	registerWrite(fd, 0x7F, 0x09);
	registerWrite(fd, 0x4F, 0xAF);
	registerWrite(fd, 0x5F, 0x40);
	registerWrite(fd, 0x48, 0x80);
	registerWrite(fd, 0x49, 0x80);
	registerWrite(fd, 0x57, 0x77);
	registerWrite(fd, 0x60, 0x78);
	registerWrite(fd, 0x61, 0x78);
	registerWrite(fd, 0x62, 0x08);
	registerWrite(fd, 0x63, 0x50);
	registerWrite(fd, 0x7F, 0x0A);
	registerWrite(fd, 0x45, 0x60);
	registerWrite(fd, 0x7F, 0x00);
	registerWrite(fd, 0x4D, 0x11);
	registerWrite(fd, 0x55, 0x80);
	registerWrite(fd, 0x74, 0x1F);
	registerWrite(fd, 0x75, 0x1F);
	registerWrite(fd, 0x4A, 0x78);
	registerWrite(fd, 0x4B, 0x78);
	registerWrite(fd, 0x44, 0x08);
	registerWrite(fd, 0x45, 0x50);
	registerWrite(fd, 0x64, 0xFF);
	registerWrite(fd, 0x65, 0x1F);
	registerWrite(fd, 0x7F, 0x14);
	registerWrite(fd, 0x65, 0x60);
	registerWrite(fd, 0x66, 0x08);
	registerWrite(fd, 0x63, 0x78);
	registerWrite(fd, 0x7F, 0x15);
	registerWrite(fd, 0x48, 0x58);
	registerWrite(fd, 0x7F, 0x07);
	registerWrite(fd, 0x41, 0x0D);
	registerWrite(fd, 0x43, 0x14);
	registerWrite(fd, 0x4B, 0x0E);
	registerWrite(fd, 0x45, 0x0F);
	registerWrite(fd, 0x44, 0x42);
	registerWrite(fd, 0x4C, 0x80);
	registerWrite(fd, 0x7F, 0x10);
	registerWrite(fd, 0x5B, 0x02);
	registerWrite(fd, 0x7F, 0x07);
	registerWrite(fd, 0x40, 0x41);
	registerWrite(fd, 0x70, 0x00);
	usleep(100000);
	registerWrite(fd, 0x32, 0x44);
	registerWrite(fd, 0x7F, 0x07);
	registerWrite(fd, 0x40, 0x40);
	registerWrite(fd, 0x7F, 0x06);
	registerWrite(fd, 0x62, 0xf0);
	registerWrite(fd, 0x63, 0x00);
	registerWrite(fd, 0x7F, 0x0D);
	registerWrite(fd, 0x48, 0xC0);
	registerWrite(fd, 0x6F, 0xd5);
	registerWrite(fd, 0x7F, 0x00);
	registerWrite(fd, 0x5B, 0xa0);
	registerWrite(fd, 0x4E, 0xA8);
	registerWrite(fd, 0x5A, 0x50);
	registerWrite(fd, 0x40, 0x80);
}

int pmw3901_init(int fd)
{
    registerWrite(fd,0x3A,0x5A);
    usleep(5000);
uint8_t chipId = registerRead(fd, 0x00);
	uint8_t dIpihc = registerRead(fd, 0x5F);

	printf("chipId: %x  dIpihc: %x \n", chipId, dIpihc);

	if (chipId != 0x49 && dIpihc != 0xB8) {
		printf("bad chipId\n");
		return -1;
	}
	
	registerRead(fd, 0x02);
	registerRead(fd, 0x03);
	registerRead(fd, 0x04);
	registerRead(fd, 0x05);
	registerRead(fd, 0x06);
	usleep(1000);

	initRegisters(fd);

	return 0;
}



void pmw3901_readMotion(int fd, int16_t *deltaX, int16_t *deltaY) {

	registerRead(fd, 0x02);

	*deltaX = ((int16_t)registerRead(fd, 0x04) << 8) | registerRead(fd, 0x03);
	*deltaY = ((int16_t)registerRead(fd, 0x06) << 8) | registerRead(fd, 0x05);
}

