#include <acpi/acpi.h>


acpi_madt_t* madt = NULL;

void acpi_init(struct stivale2_struct_tag_rsdp* rsdp_tag) {
    acpi_rsdp_t* rsdp = (acpi_rsdp_t*)rsdp_tag->rsdp;        
    acpi_rsdt_t* rsdt = (acpi_rsdt_t*)(uint64_t)rsdp->rsdtaddr;

    volatile unsigned short tableidx = 0;
    while (tableidx < rsdt->header.length - sizeof(rsdt->header) / 4) {
        acpi_madt_t* _madt = (acpi_madt_t*)(uint64_t)rsdt->tables[tableidx];
        if (strncmp(_madt->header.signature, "APIC", 4)) {
            madt = _madt;
        }

        ++tableidx;
    }
}
