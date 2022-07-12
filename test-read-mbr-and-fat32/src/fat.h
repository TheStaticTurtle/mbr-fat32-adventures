#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#ifndef FAT_H
#define FAT_H

// BIOS Parameter Block
// Common structure of the first 25 bytes of the BIOS Parameter Block (BPB) used by FAT versions since DOS 2.0 (bytes at sector offset 0x00B to 0x017 are stored since DOS 2.0, but not always used before DOS 3.2, values at 0x018 to 0x01B are used since DOS 3.0):
struct __attribute__((packed)) {
    uint16_t bytes_per_logical_sector;
    uint8_t logical_sectors_per_cluster;
    uint16_t reserved_logical_sector_count;
    uint8_t file_allocation_table_count;
    uint16_t max_root_entries;
    uint16_t logical_sector_count;
    uint8_t media_descriptor;
    uint16_t logical_sector_per_file_allocation_table;
} typedef FAT_DOS20_bios_parameter_block;

// DOS 3.31 BIOS Parameter Block
struct __attribute__((packed)) {
    FAT_DOS20_bios_parameter_block dos20_bpb;
    uint16_t physical_sectors_per_track;
    uint16_t number_of_heads;
    uint32_t hidden_sector_count;
    uint32_t logical_sector_count;
} typedef FAT_DOS331_bios_parameter_block;

//FAT32 Extended BIOS Parameter Block
struct __attribute__((packed)) {
    FAT_DOS331_bios_parameter_block dos31_bpb;
    uint8_t physical_drive_number;
    uint8_t fat16_fat12_reserved;
    uint8_t extended_boot_signature;
    uint32_t volume_id;
    char volume_label[11];
    char file_system_type[8];
} typedef FAT_extended_bios_parameter_block;

// //FAT32 Extended BIOS Parameter Block
// struct __attribute__((packed)) {
//     FAT_DOS331_bios_parameter_block dos31_bpb;
//     uint32_t logical_sector_per_file_allocation_table;
//     uint16_t drive_description;
//     uint16_t version;
//     uint32_t root_culster_number;
//     uint16_t information_sector_logical_sector_number;
//     uint16_t first_boot_sector_copy_logical_sector_number;
//     uint8_t reserved[12];
//     uint8_t physical_drive_number;
//     uint8_t fat16_fat12_1;
//     uint8_t extended_boot_signature;
//     uint32_t volume_id;
//     char volume_label[11];
//     char file_system_type[8];
// } typedef FAT_FAT32_extended_bios_parameter_block;


struct __attribute__((packed)) {
    uint8_t jump_instruction[3];
    char oem_name[8];
    FAT_extended_bios_parameter_block bios_parameter_block;
    uint8_t fs_os_boot_code[447]; // 0x1FD - 0x036 - 8
    uint8_t physical_drive_number;
    uint16_t signature;
} typedef FAT_boot_sector;

struct __attribute__((packed)) {
    char signature1[4];
    uint8_t reserved1[480];
    char signature2[4];
    uint32_t last_free_data_cluster_count;
    uint32_t recently_allocated_data_cluster_count;
    uint8_t reserved2[12];
    char signature3[4];
} typedef FAT_information_sector;

struct __attribute__((packed)) {
    FAT_boot_sector boot_sector;
    FAT_information_sector information_sector;
} typedef FAT32;


void print_fat32_bootsector(FAT_boot_sector sector);
void print_fat32(FAT32 part);

bool read_fat32(FAT32* part, FILE* file);


#endif