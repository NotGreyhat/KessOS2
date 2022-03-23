#include <stdint.h>
#include <stddef.h>
#include <util/stivale2.h>
#include <util/string.h>
#include <interrupts/IDT.h>
#include <interrupts/exceptions.h>
#include <acpi/acpi.h>
#include <pic/pic-legacy.h>


static uint8_t stack[4000];


void* get_tag(struct stivale2_struct* stivale2_struct, uint64_t id) {
    struct stivale2_tag* curTag = (void*)stivale2_struct->tags;

    while (1) {
        if (!(curTag)) {
            // End.
            return NULL;
        }

        if (curTag->identifier == id) {
            return curTag;
        }

        curTag = (void*)curTag->next;
    }
}


static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },

    .flags = 0
};


static struct stivale2_header_tag_framebuffer lfb_header_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_hdr_tag,
    },

    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};


__attribute__((section(".stivale2hdr"), used)) static struct stivale2_header stivale_header = {
    .entry_point = 0,
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
    .tags = (uintptr_t)&lfb_header_tag
};


static void(*kwrite_master)(const char* str, size_t size);


void kwrite(const char* str) {
    kwrite_master(str, strlen(str));    
}


void _start(struct stivale2_struct* ss) {
    struct stivale2_struct_tag_terminal* term_tag = get_tag(ss, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    struct stivale2_struct_tag_rsdp* rsdp_tag = get_tag(ss, STIVALE2_STRUCT_TAG_RSDP_ID);

    if (!(term_tag)) {
        __asm__ __volatile__("cli; hlt");
    }

    void* kwrite_master_addr = (void*)term_tag->term_write;
    kwrite_master = kwrite_master_addr;

    idt_set_vector(0x0, div0_handler);
    idt_set_vector(0x1, debug_excp_handler);
    idt_set_vector(0x3, breakpoint_handler);
    idt_set_vector(0x4, overflow_handler);
    idt_set_vector(0x5, bre_handler);
    idt_set_vector(0x6, invld_opcode_handler);
    idt_set_vector(0x7, device_not_avail_handler);
    idt_set_vector(0x8, double_fault_handler);
    idt_set_vector(0x9, cso_handler);
    idt_set_vector(0xA, invalid_tss_handler);
    idt_set_vector(0xB, snp_handler);
    idt_set_vector(0xC, ssf_handler);
    idt_set_vector(0xD, gpf_handler);
    idt_set_vector(0xE, page_fault_handler);
    idt_set_vector(0xF, fpe_handler);
    idt_install();

    acpi_init(rsdp_tag);

    extern acpi_madt_t* madt;

    // If MADT is NULL we will just use legacy PIC.
    if (!(madt)) {
        kwrite("Using legacy hardware!\n");     // Display a nice little message saying we are using legacy.
        pic_init();
    }
    
    while (1) {
        __asm__ __volatile__("hlt");
    }
}
