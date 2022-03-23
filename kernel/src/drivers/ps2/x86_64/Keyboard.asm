bits 64
global keyboard_isr
extern inportb              ; Makes things easy.
extern outportb             ; Same thing is above comment.
extern SC_ASCII
extern lastKeyStroke
extern kwrite


keyboard_isr: 
    ; Read byte from keyboard controller data port.
    mov rdi, 0x60           
    call inportb

    mov [lastKeyStroke], rax            ; Put scancode into first entry of lastKeyStroke.
    mov r9, SC_ASCII                    ; Puts the base addr of SC_ASCII into r9.
    add r9, rax                         ; This adds the scancode as an offset to the base.
    mov r8, [r9]                        ; Moves the key value into r8.
    mov [lastKeyStroke + 2], r8         ; Moves key value into second entry of lastKeyStroke.
    mov [lastKeyStroke + 3], byte 0          ; This moves 0 into lastKeyStroke.

    mov rdi, 0x60
    call inportb

    mov rdi, 0x20
    mov rsi, 0x20
    call outportb

    iretq    
