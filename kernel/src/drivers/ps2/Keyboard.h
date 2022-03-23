#ifndef __PS2_KEYBOARD_H__
#define __PS2_KEYBOARD_H__

#include <stdint.h>

typedef struct {
    uint16_t scancode;
    uint8_t key;
    uint8_t serviced : 1;
    uint8_t press : 1;
} __attribute__((packed)) keystroke_t;


void scancode2keystroke(unsigned int scancode);
void keyboard_isr();


#endif
