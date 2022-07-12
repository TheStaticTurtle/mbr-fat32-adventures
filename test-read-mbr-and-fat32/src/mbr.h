#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#ifndef MBR_H
#define MBR_H

enum : int {
    MBR_ERROR_NO = 0,
    MBR_ERROR_INVALID_SIGNATURE = -1
} typedef MBR_error;

enum : uint8_t {
    MBR_PARTITION_ENTRY_UNUSED    = 0x00, // Entry unused
    MBR_PARTITION_FAT_12          = 0x01, // 12-bit FAT entries
    MBR_PARTITION_FAT_16          = 0x04, // 16-bit FAT entries
    MBR_PARTITION_EXTENDED        = 0x05, // Extended partition entry
    MBR_PARTITION_IFS             = 0x07, // HPFS/NTFS/exFAT Partition
    MBR_PARTITION_FAT32           = 0x0B, // FAT32
    MBR_PARTITION_FAT32_XINT13    = 0x0C, // FAT32 using extended int13 services
    MBR_PARTITION_FAT16_XINT13    = 0x0E, // Win95 partition using extended int13 services
    MBR_PARTITION_XINT13_EXTENDED = 0x0F, // Same as type 5 but uses extended int13 services
} typedef MBR_partition_type;

struct __attribute__((packed)) {
    uint16_t reserved;
    uint8_t original_physical_drive;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
} typedef MBR_timestamp;

struct __attribute__((packed)) {
    uint32_t signature;
    uint16_t disk_copy_protect;
} typedef MBR_disk_signature;

struct __attribute__((packed)) {
    uint8_t status;
    uint8_t first_sector_head;
    uint16_t first_sector_cylinder;
    MBR_partition_type type;
    uint8_t last_sector_head;
    uint16_t last_sector_cylinder;
    uint32_t LBA_first;
    uint32_t sector_count;
} typedef MBR_partition;

struct __attribute__((packed)) {
    uint8_t bootstrap_code_1[218];
    MBR_timestamp timestamp;
    uint8_t bootstrap_code_2[216];
    MBR_disk_signature disk_signature;
    MBR_partition part1;
    MBR_partition part2;
    MBR_partition part3;
    MBR_partition part4;
    uint16_t boot_signature;
} typedef MBR;

const char* MBR_partition_type_to_string(MBR_partition_type t);
void print_mbr_partition(MBR_partition partition);
void print_mbr_disk_signature(MBR_disk_signature disk_signature);
void print_mbr_timestamp(MBR_timestamp timestamp);
void print_mbr(MBR disk);

MBR_error read_mbr(MBR* disk, FILE* file);

#endif