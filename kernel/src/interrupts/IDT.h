#ifndef __INTERRUPTS_IDT_H__
#define __INTERRUPTS_IDT_H__

#include <stdint.h>


/*
 *  The IDT tells the CPU how to respond to an interruot
 *  by giving it bits of an interrupt service routine (ISR).
 */

typedef struct {
    uint16_t isr_low;           // Low bits of ISR.
    uint16_t cs;                // Code selector to load into CS.
    uint8_t ist : 3;            // Interupt stack table.
    uint8_t reserved : 5;
    uint8_t attr : 4;
    uint8_t reserved1 : 1;
    uint8_t dpl : 2;            // Descriptor priv level.
    uint8_t p : 1;              // Present.
    uint16_t isr_middle;        // Middle bits of ISR.
    uint32_t isr_high;          // High bits of ISR.
    uint32_t reserved2;
} __attribute__((packed)) idt_vector_t;


typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idtr_t;


typedef struct {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((packed)) int_frame_t;


void idt_set_vector(uint8_t vector, void* isr);
void idt_install();


#endif
