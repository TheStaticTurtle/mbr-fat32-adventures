#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#ifndef FAT_H
#define FAT_H

enum : uint8_t {
    FAT_TYPE_FAT12=12,
    FAT_TYPE_FAT16=16,
    FAT_TYPE_FAT32=32,
} typedef FAT_FATtype;

// BIOS Parameter Block
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


// Boot sector
struct __attribute__((packed)) {
    uint8_t jump_instruction[3];
    char oem_name[8];
    FAT_extended_bios_parameter_block bios_parameter_block;
    uint8_t fs_os_boot_code[447]; // 0x1FD - 0x036 - 8
    uint8_t physical_drive_number;
    uint16_t signature;
} typedef FAT_boot_sector;
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


struct __attribute__((packed)) {
    FAT_boot_sector boot_sector;
} typedef FAT_PART;

// Struct is not readable directly 
struct __attribute__((packed)) {
    FAT_FAT32_boot_sector boot_sector;
    FAT_FAT32_information_sector information_sector;
} typedef FAT32_PART;

void print_dos331_bios_parameter_block(FAT_DOS331_bios_parameter_block dos31_bpb);
void print_fat16_bios_parameter_block(FAT_extended_bios_parameter_block block);
void print_fat32_bios_parameter_block(FAT_FAT32_extended_bios_parameter_block block);
void print_fat16_bootsector(FAT_boot_sector sector);
void print_fat32_bootsector(FAT_FAT32_boot_sector sector);

void print_fat32_information_sector(FAT_FAT32_information_sector sector);

void print_fat16_part(FAT_PART part);
void print_fat32_part(FAT32_PART part);
void print_fat(void *part);

FAT_FATtype get_fattype(void *part);
FAT_FATtype get_fattype(FILE* file, uint32_t offset);

bool read_fat16_part(FAT_PART* part, FILE* file, uint32_t partition_start);
bool read_fat32_part(FAT32_PART* part, FILE* file, uint32_t partition_start);

unsigned char lfn_checksum(const unsigned char *pFCBName);

// FAT time
// struct __attribute__((packed)) {
//     uint8_t seconds : 5;
//     uint8_t minutes : 6;
//     uint8_t hours : 5;
// } typedef FAT_time;
// struct __attribute__((packed)) {
//     uint8_t year : 7;
//     uint8_t month : 4;
//     uint8_t day : 5;
// } typedef FAT_date;
struct __attribute__((packed)) {
        uint8_t seconds :5;
        uint8_t minutes :6;
        uint8_t hours :5;
        uint8_t day :5;
        uint8_t month :4;
        uint8_t year :7;
} typedef FAT_datetime;

// Directory entry
struct __attribute__((packed)) {
    uint8_t short_name[8];
    uint8_t short_name_ext[3];
    bool attribute_readonly : 1;
    bool attribute_hidden : 1;
    bool attribute_system : 1;
    bool attribute_volume_label : 1;
    bool attribute_subdirectory : 1;
    bool attribute_archive : 1;
    bool attribute_device : 1;
    bool attribute_reserved : 1;
    uint8_t reserved;
    uint8_t create_time_fine;
    // uint16_t create_time;
    // uint16_t create_date;
    FAT_datetime create_date;
    uint16_t last_access_date;
    uint16_t high_bytes_cluster_number_or_access_rights;
    // uint16_t last_modified_time;
    // uint16_t last_modified_date;
    FAT_datetime last_modified_date;
    uint16_t start_of_file_or_lowbytes;
    uint32_t file_size_bytes;
} typedef FAT_directory_entry;

// LFN entry
struct __attribute__((packed)) {
    uint8_t sequence_number;
    // uint8_t name_characters1[10];
    uint16_t name_characters1[5];
    uint8_t attributes;
    uint8_t type;
    uint8_t checksum;
    // uint8_t name_characters2[12];
    uint16_t name_characters2[6];
    uint16_t first_cluster;
    // uint8_t name_characters3[4];
    uint16_t name_characters3[2];
} typedef FAT_lfn_entry;

#endif