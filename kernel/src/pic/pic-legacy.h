#ifndef __PIC_LEGACY_PIC__
#define __PIC_LEGACY_PIC__

#define LEGACY_PIC1_COMMAND 0x20
#define LEGACY_PIC1_DATA 0x21
#define LEGACY_PIC2_COMMAND 0xA0
#define LEGACY_PIC2_DATA 0xA1

#define LEGACY_PIC_ICW1_INIT 0x10
#define LEGACY_PIC_ICW1_ICW4 0x01
#define LEGACY_PIC_ICW4_8086 0x01
#define LEGACY_PIC_EOI 0x20

#include <stdint.h>
#include <IO/IO.h>

void pic_init();


#endif
