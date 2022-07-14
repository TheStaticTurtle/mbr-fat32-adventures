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



void print_dos331_bios_parameter_block(FAT_DOS331_bios_parameter_block dos31_bpb);


FAT_FATtype get_fattype(void *part);
FAT_FATtype get_fattype(FILE* file, uint32_t offset);


unsigned char lfn_checksum(const unsigned char *pFCBName);

// FAT time
struct __attribute__((packed)) {
        uint16_t day :5;
        uint16_t month :4;
        uint16_t year :7;
} typedef FAT_date;

struct __attribute__((packed)) {
        uint16_t seconds :5;
        uint16_t minutes :6;
        uint16_t hours :5;
} typedef FAT_time;

struct __attribute__((packed)) {
        uint16_t seconds :5;
        uint16_t minutes :6;
        uint16_t hours :5;
        uint16_t day :5;
        uint16_t month :4;
        uint16_t year :7;
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
    FAT_datetime create_date;
    FAT_date last_access_date;
    uint16_t high_bytes_cluster_number_or_access_rights;
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