#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "mbr.h"
#include "fat.h"
#include "part.h"

int error(const char* error, int code) {
    printf("ERROR %d: %s\n", code, error);
    return code;
}

int main(int argc, char** argv) {
    printf("MBR struct size: %lu\n", sizeof(MBR));
    printf("MBR_partition struct size: %lu\n", sizeof(MBR_partition));
    printf("FAT32 struct size: %lu\n", sizeof(FAT32_PART));
    printf("FAT_boot_sector struct size: %lu\n", sizeof(FAT_boot_sector));
    printf("FAT_DOS20_bios_parameter_block struct size: %lu\n", sizeof(FAT_DOS20_bios_parameter_block));
    printf("FAT_DOS331_bios_parameter_block struct size: %lu\n", sizeof(FAT_DOS331_bios_parameter_block));
    printf("FAT_extended_bios_parameter_block struct size: %lu\n", sizeof(FAT_extended_bios_parameter_block));
    printf("FAT_information_sector struct size: %lu\n", sizeof(FAT_FAT32_information_sector));
    printf("FAT_directory_entry struct size: %lu\n", sizeof(FAT_directory_entry));
    printf("FAT_lfn_entry struct size: %lu\n", sizeof(FAT_lfn_entry));
    printf("FAT_datetime struct size: %lu\n", sizeof(FAT_datetime));


    MBR disk;
    memset(&disk, 0x00, sizeof(MBR));

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL) return error("Failed to open file", -1);

    if(read_mbr(&disk, fp) != MBR_ERROR_NO) return error("Failed to read disk MBR", -2);
    printf("\n\nValid MBR Disk found, printing structure:\n");
    print_mbr(disk);
    
    printf("\n\n");

    MBR_partition primary_parts[4] = {disk.part1, disk.part2, disk.part3, disk.part4};

    for(int i=0; i<4; i++) {
        printf("Primary partion %d ", i+1);

        if(is_primary_part_valid(primary_parts[i], fp)) {
            if(disk.part1.type == MBR_PARTITION_FAT32) {
                uint32_t partition_start = get_primary_part_start_bytes(primary_parts[i]);

                FAT_FATtype fat_type = get_fattype(fp, partition_start);
                printf("is a valid FAT%d partition:\n",fat_type);

                if(fat_type == FAT_FATtype::FAT_TYPE_FAT16) {
                    FAT_PART primary_part;
                    read_fat16_part(&primary_part, fp, partition_start);
                    print_fat16_part(primary_part);
                } else if(fat_type == FAT_FATtype::FAT_TYPE_FAT32) {
                    FAT32_PART primary_part;
                    read_fat32_part(&primary_part, fp, partition_start);
                    // print_fat32_part(primary_part);
                } 
                
            }
        } else {
            printf("is invalid or empty:\n");
        }
    }





    return 0;
}