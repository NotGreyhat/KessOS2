#include <pic/pic-legacy.h>


void pic_init() {
    // Master PIC init.
    outportb(LEGACY_PIC1_COMMAND, LEGACY_PIC_ICW1_INIT | LEGACY_PIC_ICW1_ICW4);
    io_wait();

    // Slave PIC init.
    outportb(LEGACY_PIC2_COMMAND, LEGACY_PIC_ICW1_INIT| LEGACY_PIC_ICW1_ICW4);
    io_wait();

    // PIC remap.
    outportb(LEGACY_PIC1_DATA, 0x20);
    io_wait();
    outportb(LEGACY_PIC2_DATA, 0x28);
    io_wait();

    outportb(LEGACY_PIC1_DATA, 4);
    io_wait();
    outportb(LEGACY_PIC2_DATA, 2);
    io_wait();

    outportb(LEGACY_PIC1_DATA, LEGACY_PIC_ICW4_8086);
    io_wait();
    outportb(LEGACY_PIC2_DATA, LEGACY_PIC_ICW4_8086);
    io_wait();

    // Mask all bits and unmask ones that we want.
    outportb(LEGACY_PIC1_DATA, 0xFF);
    outportb(LEGACY_PIC2_DATA, 0xFF);
}
