#include "mbr.h"
#include "pretty_print.h"
#include "ansi.h"

#pragma region Pretty-Print
const char* MBR_partition_type_to_string(MBR_partition_type t) {
    static const char *strings[] = { 
        "UNUSED",
        "FAT12",
        "UNKNOWN",
        "UNKNOWN",
        "FAT16",
        "EXTENDED",
        "UNKNOWN",
        "HPFS/NTFS/exFAT",
        "UNKNOWN",
        "UNKNOWN",
        "UNKNOWN",
        "FAT32",
        "FAT32 (LBA)",
        "FAT16 (LBA)",
        "EXTENDED (LBA)",
    };
    return strings[t];
}
void print_mbr_partition(MBR_partition partition) {
    pp_increase_global_indent();
    pp_var("status", partition.status, 1, "", "\n");
    pp_var("first_sector_head", partition.first_sector_head, 1, "", "\n");
    pp_var("first_sector_cylinder", partition.first_sector_cylinder, 1, "", "\n");

    const char* type1 = MBR_partition_type_to_string(partition.type);
    pp_enum_start("type", 1, "");
    if(type1==NULL) {
        printf(REDB " NOT FOUND  " COLOR_RESET " %" PRIu8 " (0x%02" PRIx8 ")", (uint8_t)partition.type, (uint8_t)partition.type);
    } else {
        pp_enum_value(type1);
    }
    pp_enum_end("\n");

    pp_var("last_sector_head", partition.last_sector_head, 1, "", "\n");
    pp_var("last_sector_cylinder", partition.last_sector_cylinder, 1, "", "\n");
    pp_var("LBA_first", partition.LBA_first, 1, "", "\n");
    pp_var("sector_count", partition.sector_count, 1, "", "\n");

    pp_decrease_global_indent();
}
void print_mbr_disk_signature(MBR_disk_signature disk_signature) {
    pp_title("disk_signature", 1, "", ":\n");
    pp_increase_global_indent();
    pp_var("signature", disk_signature.signature, 1, "", "\n");
    pp_var("disk_copy_protect", disk_signature.disk_copy_protect, 1, "", "\n");
    pp_decrease_global_indent();
}
void print_mbr_timestamp(MBR_timestamp timestamp) {
    pp_title("timestamp", 1, "", ":\n");
    pp_increase_global_indent();
    pp_var("original_physical_drive", timestamp.original_physical_drive, 1, "", "\n");
    pp_var("seconds", timestamp.seconds, 1, "", "\n");
    pp_var("minutes", timestamp.minutes, 1, "", "\n");
    pp_var("hours", timestamp.hours, 1, "", "\n");
    pp_decrease_global_indent();
}
void print_mbr(MBR disk) {
    print_mbr_timestamp(disk.timestamp);
    print_mbr_disk_signature(disk.disk_signature);

    pp_title("part1", 1, "", ":\n");
    print_mbr_partition(disk.part1);
    pp_title("part2", 1, "", ":\n");
    print_mbr_partition(disk.part2);
    pp_title("part3", 1, "", ":\n");
    print_mbr_partition(disk.part3);
    pp_title("part4", 1, "", ":\n");
    print_mbr_partition(disk.part4);

    pp_var("boot_signature", disk.boot_signature, 1, "", "\n");
}
#pragma endregion

MBR_error read_mbr(MBR* disk, FILE* file) {
    fread(disk, sizeof(MBR), 1, file);
    if(disk->boot_signature != 0xaa55) return MBR_ERROR_INVALID_SIGNATURE;
    return MBR_ERROR_NO;
}

