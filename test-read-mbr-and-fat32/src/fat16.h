
#include "fat.h"

// Extended BIOS Parameter Block
struct __attribute__((packed)) {
    FAT_DOS331_bios_parameter_block dos31_bpb;
    uint8_t physical_drive_number;
    uint8_t fat16_fat12_reserved;
    uint8_t extended_boot_signature;
    uint32_t volume_id;
    char volume_label[11];
    char file_system_type[8];
} typedef FAT_extended_bios_parameter_block;

// Boot sector
struct __attribute__((packed)) {
    uint8_t jump_instruction[3];
    char oem_name[8];
    FAT_extended_bios_parameter_block bios_parameter_block;
    uint8_t fs_os_boot_code[447]; // 0x1FD - 0x036 - 8
    uint8_t physical_drive_number;
    uint16_t signature;
} typedef FAT_boot_sector;


struct __attribute__((packed)) {
    FAT_boot_sector boot_sector;
} typedef FAT_PART;


void print_fat16_bios_parameter_block(FAT_extended_bios_parameter_block block);
void print_fat16_bootsector(FAT_boot_sector sector, uint32_t offset);


bool read_fat16_part(FAT_PART* part, FILE* file, uint32_t partition_start);