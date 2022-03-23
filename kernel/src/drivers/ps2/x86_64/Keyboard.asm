bits 64
global keyboard_isr
extern inportb              ; Makes things easy.
extern outportb             ; Same thing is above comment.
extern SC_ASCII
extern lastKeyStroke


keyboard_isr: 
    ; Read byte from keyboard controller data port.
    mov rdi, 0x60           
    call inportb

    mov r9, rax       
    and r9, 0x80            ; AND scancode by 0x80, if it is zero it is a keypress.
    
    ; Check if zero.
    or r9, r9   
    jnz key_release

    mov [lastKeyStroke], rax            ; Put scancode into first entry of lastKeyStroke.
    mov r9, SC_ASCII                    ; Puts the base addr of SC_ASCII into r9.
    add r9, rax                         ; This adds the scancode as an offset to the base.
    mov r8, [r9]                        ; Moves the key value into r8.
    mov [lastKeyStroke + 2], r8         ; Moves key value into second entry of lastKeyStroke.
    mov [lastKeyStroke + 3], byte 0     ; This moves 0 into lastKeyStroke.
    mov [lastKeyStroke + 4], byte 1     ; Key was pressed.


isr_end:
    mov rdi, 0x20
    mov rsi, 0x20
    call outportb
    iretq 

key_release:
    ; NOTE: Make sure to check if it is
    ; a key press before checking other values
    ; because other values will be undefined if
    ; the key is just released.

    mov [lastKeyStroke + 4], byte 0
    jmp isr_end
