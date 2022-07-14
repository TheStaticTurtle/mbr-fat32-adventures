#include "fat.h"

// FAT32 Extended BIOS Parameter Block
struct __attribute__((packed)) {
    FAT_DOS331_bios_parameter_block dos31_bpb;
    uint32_t logical_sector_per_file_allocation_table;
    uint16_t drive_description;
    uint16_t version;
    uint32_t root_culster_number;
    uint16_t information_sector_logical_sector_number;
    uint16_t first_boot_sector_copy_logical_sector_number;
    uint8_t reserved[12];
    uint8_t physical_drive_number;
    uint8_t fat16_fat12_reserved;
    uint8_t extended_boot_signature;
    uint32_t volume_id;
    char volume_label[11];
    char file_system_type[8];
} typedef FAT_FAT32_extended_bios_parameter_block;


// FAT32 Boot sector
struct __attribute__((packed)) {
    uint8_t jump_instruction[3];
    char oem_name[8];
    FAT_FAT32_extended_bios_parameter_block bios_parameter_block;
    uint8_t fs_os_boot_code[419]; // 0x1FD - 0x052 - 8
    uint8_t physical_drive_number;
    uint16_t signature;
} typedef FAT_FAT32_boot_sector;


//FAT32 Information sector
struct __attribute__((packed)) {
    char signature1[4];
    uint8_t reserved1[480];
    char signature2[4];
    uint32_t last_free_data_cluster_count;
    uint32_t recently_allocated_data_cluster_count;
    uint8_t reserved2[12];
    // char signature3[4];
    uint32_t signature3;
} typedef FAT_FAT32_information_sector;


// Struct is not readable directly 
struct __attribute__((packed)) {
    FAT_FAT32_boot_sector boot_sector;
    FAT_FAT32_information_sector information_sector;
} typedef FAT32_PART;


void print_fat32_bios_parameter_block(FAT_FAT32_extended_bios_parameter_block block);
void print_fat32_bootsector(FAT_FAT32_boot_sector sector, uint32_t offset);

void print_fat32_information_sector(FAT_FAT32_information_sector sector, uint32_t offset);

bool read_fat32_part(FAT32_PART* part, FILE* file, uint32_t partition_start);