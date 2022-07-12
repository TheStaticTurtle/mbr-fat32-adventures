#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "part.h"
#include "mbr.h"
#include "fat.h"

uint32_t get_primary_part_start_bytes(MBR_partition mbr_part) {
    return mbr_part.LBA_first * 512;
}

bool is_fat32_part_valid(MBR_partition mbr_part, FILE* file) {
    if(fseek(file, get_primary_part_start_bytes(mbr_part), SEEK_SET) != 0) {
        printf("\tSeek failed\n");
        return false;
    }

    FAT32 part;
    if(!read_fat32(&part, file)) {
        return false;
    }
    return true;
}


bool is_primary_part_valid(MBR_partition mbr_part, FILE* file) {
    if(mbr_part.type == MBR_PARTITION_FAT32 && is_fat32_part_valid(mbr_part, file)) return true;
    return false;
}
