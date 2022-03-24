#ifndef __ACPI_ACPI_H__
#define __ACPI_ACPI_H__

#include <acpi/tables.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/string.h>
#include <util/stivale2.h>
#include <drivers/video/Framebuffer.h>

void acpi_init(struct stivale2_struct_tag_rsdp* rsdp_tag);


#endif
