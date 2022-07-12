#include "mbr.h"
#include "fat.h"

// printf("\t\t last_free_data_cluster_count = %" PRIu16 " (0x%04" PRIx16 ")\n", sector.last_free_data_cluster_count, sector.last_free_data_cluster_count);
// printf("\t\t last_free_data_cluster_count = %" PRIu32 " (0x%08" PRIx32 ")\n", sector.last_free_data_cluster_count, sector.last_free_data_cluster_count);
// printf("\t\t last_free_data_cluster_count = %" PRIu8 " (0x%02x)\n", sector.last_free_data_cluster_count, sector.last_free_data_cluster_count);

void print_fat32_bios_parameter_block(FAT_extended_bios_parameter_block block) {
    printf("\t\tDOS2.0 BPB\n");
    printf("\t\t\tbytes_per_logical_sector = %" PRIu16 " (0x%04" PRIx16 ")\n", block.dos31_bpb.dos20_bpb.bytes_per_logical_sector, block.dos31_bpb.dos20_bpb.bytes_per_logical_sector);
    printf("\t\t\tlogical_sectors_per_cluster = %" PRIu8 " (0x%02x)\n", block.dos31_bpb.dos20_bpb.logical_sectors_per_cluster, block.dos31_bpb.dos20_bpb.logical_sectors_per_cluster);
    printf("\t\t\treserved_logical_sector_count = %" PRIu16 " (0x%04" PRIx16 ")\n", block.dos31_bpb.dos20_bpb.reserved_logical_sector_count, block.dos31_bpb.dos20_bpb.reserved_logical_sector_count);
    printf("\t\t\tfile_allocation_table_count = %" PRIu8 " (0x%02x)\n", block.dos31_bpb.dos20_bpb.file_allocation_table_count, block.dos31_bpb.dos20_bpb.file_allocation_table_count);
    printf("\t\t\tmax_root_entries = %" PRIu16 " (0x%04" PRIx16 ")\n", block.dos31_bpb.dos20_bpb.max_root_entries, block.dos31_bpb.dos20_bpb.max_root_entries);
    printf("\t\t\tlogical_sector_count = %" PRIu16 " (0x%04" PRIx16 ")\n", block.dos31_bpb.dos20_bpb.logical_sector_count, block.dos31_bpb.dos20_bpb.logical_sector_count);
    printf("\t\t\tmedia_descriptor = %" PRIu8 " (0x%02x)\n", block.dos31_bpb.dos20_bpb.media_descriptor, block.dos31_bpb.dos20_bpb.media_descriptor);
    printf("\t\t\tlogical_sector_per_file_allocation_table = %" PRIu16 " (0x%04" PRIx16 ")\n", block.dos31_bpb.dos20_bpb.logical_sector_per_file_allocation_table, block.dos31_bpb.dos20_bpb.logical_sector_per_file_allocation_table);
    
    printf("\t\tDOS3.1 BPB\n");
    printf("\t\t\tphysical_sectors_per_track = %" PRIu16 " (0x%04" PRIx16 ")\n", block.dos31_bpb.physical_sectors_per_track, block.dos31_bpb.physical_sectors_per_track);
    printf("\t\t\tnumber_of_heads = %" PRIu16 " (0x%04" PRIx16 ")\n", block.dos31_bpb.number_of_heads, block.dos31_bpb.number_of_heads);
    printf("\t\t\thidden_sector_count = %" PRIu32 " (0x%08" PRIx32 ")\n", block.dos31_bpb.hidden_sector_count, block.dos31_bpb.hidden_sector_count);
    printf("\t\t\tlogical_sector_count = %" PRIu32 " (0x%08" PRIx32 ")\n", block.dos31_bpb.logical_sector_count, block.dos31_bpb.logical_sector_count);
    
    printf("\t\tExtended BPB\n");
    printf("\t\t\tphysical_drive_number = %" PRIu8 " (0x%02" PRIx8 ")\n", block.physical_drive_number, block.physical_drive_number);
    printf("\t\t\tfat16_fat12_reserved = %" PRIu8 " (0x%02" PRIx8 ")\n", block.fat16_fat12_reserved, block.fat16_fat12_reserved);
    printf("\t\t\textended_boot_signature = %" PRIu8 " (0x%02" PRIx8 ")\n", block.extended_boot_signature, block.extended_boot_signature);
    printf("\t\t\tvolume_id = %" PRIu32 " (0x%08" PRIx32 ")\n", block.volume_id, block.volume_id);
    printf("\t\t\tvolume_label = \"%.11s\"\n", block.volume_label);
    printf("\t\t\tfile_system_type = \"%.8s\"\n", block.file_system_type);
}


void print_fat32_bootsector(FAT_boot_sector sector) {
    printf("\t\toem_name = \"%s\"\n" , sector.oem_name);
    print_fat32_bios_parameter_block(sector.bios_parameter_block);
    printf("\t\tphysical_drive_number = %d\n" , sector.physical_drive_number);
    printf("\t\tboot_sector_signature = 0x%04" PRIx16 "\n", sector.signature);
}

void print_fat32_informationsector(FAT_information_sector sector) {
    printf("\t\tsignature1 = \"%s\"\n" , sector.signature1);
    printf("\t\tsignature2 = \"%s\"\n" , sector.signature2);
    printf("\t\tlast_free_data_cluster_count = %" PRIu32 " (0x%08" PRIx32 ")\n", sector.last_free_data_cluster_count, sector.last_free_data_cluster_count);
    printf("\t\trecently_allocated_data_cluster_count = %" PRIu32 " (0x%08" PRIx32 ")\n", sector.recently_allocated_data_cluster_count, sector.recently_allocated_data_cluster_count);
    bool signature3_valid = ((sector.signature3[0] == sector.signature3[1]) == sector.signature3[2]) == sector.signature3[3];
    printf("\t\tsignature2 = %s (%x,%x,%x,%x)\n" , signature3_valid ? "valid" : "invalid", sector.signature3[0] , sector.signature3[1] , sector.signature3[2] , sector.signature3[3]);
}

void print_fat32(FAT32 part) {
    printf("\tboot_sector:\n");
    print_fat32_bootsector(part.boot_sector);
    printf("\tinformation_sector:\n");
    print_fat32_informationsector(part.information_sector);
}


bool read_fat32(FAT32* part, FILE* file) {
    fread(part, sizeof(FAT32), 1, file);
    if(part->boot_sector.signature != 0xaa55) return false;
    return true;
}