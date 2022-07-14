#include "mbr.h"
#include "fat.h"
#include "ansi.h"
#include "pretty_print.h"

void print_dos331_bios_parameter_block(FAT_DOS331_bios_parameter_block dos31_bpb) {
    pp_title("DOS2.0 BPB", 1, "", "\n");
    pp_increase_global_indent();
    pp_var("bytes_per_logical_sector", dos31_bpb.dos20_bpb.bytes_per_logical_sector, 1, "", "\n");
    pp_var("logical_sectors_per_cluster", dos31_bpb.dos20_bpb.logical_sectors_per_cluster, 1, "", "\n");
    pp_var("reserved_logical_sector_count", dos31_bpb.dos20_bpb.reserved_logical_sector_count, 1, "", "\n");
    pp_var("file_allocation_table_count", dos31_bpb.dos20_bpb.file_allocation_table_count, 1, "", "\n");
    pp_var("max_root_entries", dos31_bpb.dos20_bpb.max_root_entries, 1, "", "\n");
    pp_var("logical_sector_count", dos31_bpb.dos20_bpb.logical_sector_count, 1, "", "\n");
    pp_var("media_descriptor", dos31_bpb.dos20_bpb.media_descriptor, 1, "", "\n");
    pp_var("logical_sector_per_file_allocation_table", dos31_bpb.dos20_bpb.logical_sector_per_file_allocation_table, 1, "", "\n");
    pp_decrease_global_indent();

    pp_title("DOS3.31 BPB", 1, "", "\n");
    pp_increase_global_indent();
    pp_var("physical_sectors_per_track", dos31_bpb.physical_sectors_per_track, 1, "", "\n");
    pp_var("number_of_heads", dos31_bpb.number_of_heads, 1, "", "\n");
    pp_var("hidden_sector_count", dos31_bpb.hidden_sector_count, 1, "", "\n");
    pp_var("logical_sector_count", dos31_bpb.logical_sector_count, 1, "", "\n");
    pp_decrease_global_indent();
}


FAT_FATtype get_fattype(void *rawpart) {
    uint8_t* u8rawpart = (uint8_t*)rawpart;

    // https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system
    // 0x11 => Maximum number of FAT12 or FAT16 root directory entries. 0 for FAT32, where the root directory is stored in ordinary data clusters
    // 0x42 => Extended boot signature, 0x29 ...... Most FAT32 file system ...... implementations should accept 0x28 as an alternative signature
    if(u8rawpart[0x11] == 0 && (u8rawpart[0x42] == 0x29 || u8rawpart[0x42] == 0x28)) {
        return FAT_TYPE_FAT32;
    }
    return FAT_TYPE_FAT16;
}
FAT_FATtype get_fattype(FILE* file, uint32_t offset) {
    uint8_t buffer[512];
    memset(buffer, 0x0, 512);

    fseek(file, offset, SEEK_SET);
    fread(buffer, 512, 1, file);
    return get_fattype(buffer);
}


