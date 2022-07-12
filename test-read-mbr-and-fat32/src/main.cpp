#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "mbr.h"
#include "fat.h"
#include "part.h"

int error(const char* error, int code) {
    printf("ERROR %d: %s", code, error);
    return code;
}

int main() {
    printf("MBR struct size: %lu\n", sizeof(MBR));
    printf("MBR_partition struct size: %lu\n", sizeof(MBR_partition));
    printf("FAT32 struct size: %lu\n", sizeof(FAT32));
    printf("FAT_boot_sector struct size: %lu\n", sizeof(FAT_boot_sector));
    printf("FAT_DOS20_bios_parameter_block struct size: %lu\n", sizeof(FAT_DOS20_bios_parameter_block));
    printf("FAT_DOS331_bios_parameter_block struct size: %lu\n", sizeof(FAT_DOS331_bios_parameter_block));
    printf("FAT_extended_bios_parameter_block struct size: %lu\n", sizeof(FAT_extended_bios_parameter_block));
    printf("FAT_information_sector struct size: %lu\n", sizeof(FAT_information_sector));


    MBR disk;
    memset(&disk, 0x00, sizeof(MBR));

    FILE *fp = fopen("../file", "r");
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
                printf("is a valid FAT32 partition:\n");
                fseek(fp, get_primary_part_start_bytes(primary_parts[i]), SEEK_SET);
                FAT32 primary_part;
                read_fat32(&primary_part, fp);
                print_fat32(primary_part);
            }
        } else {
            printf("is invalid or empty:\n");
        }
    }





    return 0;
}