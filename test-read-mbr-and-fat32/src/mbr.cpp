#include "mbr.h"

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
    printf("\t\tstatus = 0x%02x\n", partition.status);
    printf("\t\tfirst_sector_head = %d (0x%02x)\n" , partition.first_sector_head, partition.first_sector_head);
    printf("\t\tfirst_sector_cylinder = %d (0x%02x)\n" , partition.first_sector_cylinder, partition.first_sector_cylinder);
    const char* type1 = MBR_partition_type_to_string(partition.type);
    if(type1==NULL) {
        printf("\t\ttype = NOTFOUND:0x%02x\n", partition.type);
    } else {
        printf("\t\ttype = %s\n", type1);
    }
    printf("\t\tlast_sector_head = %d (0x%02x)\n" , partition.last_sector_head, partition.last_sector_head);
    printf("\t\tlast_sector_cylinder = %d (0x%02x)\n" , partition.last_sector_cylinder, partition.last_sector_cylinder);
    printf("\t\tlba_first = %" PRIu32 " (0x%08" PRIx32 ")\n", partition.LBA_first, partition.LBA_first);
    printf("\t\tsector_count = %" PRIu32 " (0x%08" PRIx32 ")\n", partition.sector_count, partition.sector_count);
}
void print_mbr_disk_signature(MBR_disk_signature disk_signature) {
    printf("\t\tsignature = %" PRIu32 " (0x%08" PRIx32 ")\n", disk_signature.signature, disk_signature.signature);
    printf("\t\tdisk_copy_protect = %" PRIu32 " (0x%08" PRIx32 ")\n", disk_signature.disk_copy_protect, disk_signature.disk_copy_protect);
}
void print_mbr_timestamp(MBR_timestamp timestamp) {
    printf("\t\toriginal_physical_drive = 0x%02x\n", timestamp.original_physical_drive);
    printf("\t\tseconds = %d\n" , timestamp.seconds);
    printf("\t\tminutes = %d\n" , timestamp.minutes);
    printf("\t\thours = %d\n" , timestamp.hours);
}
void print_mbr(MBR disk) {
    printf("\ttimestamp:\n");
    print_mbr_timestamp(disk.timestamp);

    printf("\tdisk_signature:\n");
    print_mbr_disk_signature(disk.disk_signature);

    printf("\tpart1:\n");
    print_mbr_partition(disk.part1);
    printf("\tpart2:\n");
    print_mbr_partition(disk.part2);
    printf("\tpart3:\n");
    print_mbr_partition(disk.part3);
    printf("\tpart4:\n");
    print_mbr_partition(disk.part4);

    printf("\tboot_signature = 0x%04" PRIx16 "\n", disk.boot_signature);
}
#pragma endregion

MBR_error read_mbr(MBR* disk, FILE* file) {
    fread(disk, sizeof(MBR), 1, file);
    if(disk->boot_signature != 0xaa55) return MBR_ERROR_INVALID_SIGNATURE;
    return MBR_ERROR_NO;
}

