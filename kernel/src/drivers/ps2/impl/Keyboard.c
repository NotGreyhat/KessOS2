#include <drivers/ps2/Keyboard.h>

uint8_t SC_ASCII[] = "\x00\x1B" "1234567890-=" "\x08"
"\x00" "qwertyuiop[]" "\x0D\x1D" "asdfghjkl;'`" "\x00" "\\"
"zxcvbnm,./" "\x00\x00\x00" " ";

keystroke_t lastKeyStroke;


void scancode2keystroke(unsigned int scancode) {
    lastKeyStroke.scancode = scancode;
    lastKeyStroke.key = SC_ASCII[scancode];
    lastKeyStroke.serviced = 0;
}

void service() {
    lastKeyStroke.serviced = 1;
}
