#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "mbr.h"

#ifndef PART_H
#define PART_H

uint32_t get_primary_part_start_bytes(MBR_partition mbr_part);

bool is_fat_part_valid(uint32_t start, FILE* file);

bool is_primary_part_valid(MBR_partition mbr_part, FILE* file);

#endif