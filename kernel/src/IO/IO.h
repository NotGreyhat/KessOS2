#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>


void outportb(uint16_t port, uint8_t byte);
uint8_t inportb(uint16_t port);
uint32_t inportl(uint16_t port);
uint32_t outportl(uint16_t port, uint32_t dword);
void io_wait();


#endif
