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

bool is_fat_part_valid(MBR_partition mbr_part, FILE* file) {
    uint32_t offset = get_primary_part_start_bytes(mbr_part);
    if(fseek(file, offset, SEEK_SET) != 0) {
        printf("\tSeek failed\n");
        return false;
    }

    FAT_PART part;
    if(!read_fat16_part(&part, file, offset)) {
        return false;
    }
    return true;
}


bool is_primary_part_valid(MBR_partition mbr_part, FILE* file) {
    if(mbr_part.type == MBR_PARTITION_FAT32 && is_fat_part_valid(mbr_part, file)) return true;
    return false;
}
