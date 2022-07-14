#include "fat32.h"
#include "fat.h"
#include "pretty_print.h"
#include "utf-convert.h"
#include "ansi.h"


void print_fat32_bios_parameter_block(FAT_FAT32_extended_bios_parameter_block block) {
    print_dos331_bios_parameter_block(block.dos31_bpb);

    pp_title("FAT32 Extended BPB", 1, "", "\n");
    pp_increase_global_indent();
    pp_var("logical_sector_per_file_allocation_table", block.logical_sector_per_file_allocation_table, 1, "", "\n");
    pp_var("drive_description", block.drive_description, 1, "", "\n");
    pp_var("version", block.version, 1, "", "\n");
    pp_var("information_sector_logical_sector_number", block.information_sector_logical_sector_number, 1, "", "\n");
    pp_var("first_boot_sector_copy_logical_sector_number", block.first_boot_sector_copy_logical_sector_number, 1, "", "\n");
    pp_var("physical_drive_number", block.physical_drive_number, 1, "", "\n");
    pp_var("fat16_fat12_reserved", block.fat16_fat12_reserved, 1, "", "\n");
    pp_var("extended_boot_signature", block.extended_boot_signature, 1, "", "\n");
    pp_var("volume_id", block.volume_id, 1, "", "\n");
    pp_var("volume_label", block.volume_label, 1, "", "\n");
    pp_var("file_system_type", block.file_system_type, 1, "", "\n");
    pp_decrease_global_indent();
}
void print_fat32_bootsector(FAT_FAT32_boot_sector sector, uint32_t offset) {
    pp_increase_global_indent();
    pp_title("boot_sector @ disk sector ", 0, "", "");
    printf(CYN "%d\n" COLOR_RESET, offset/512);

    pp_var("oem_name", sector.oem_name, 1, "", "\n");

    print_fat32_bios_parameter_block(sector.bios_parameter_block);

    pp_var("physical_drive_number", sector.physical_drive_number, 1, "", "\n");
    pp_var("signature", sector.signature, 1, "", "\n");
    pp_decrease_global_indent();
}
void print_fat32_information_sector(FAT_FAT32_information_sector sector, uint32_t offset) {
    pp_increase_global_indent();
    pp_indent(0); printf("FAT32 partition, reading information sector\n");
    pp_title("information_sector @ disk sector ", 0, "", "");
     printf(CYN "%d\n" COLOR_RESET, offset/512);

    char text[5] = {0};
    mempcpy(text, sector.signature1, 4);
    pp_var("signature1", text, 1, "", "\n");
    mempcpy(text, sector.signature2, 4);
    pp_var("signature2", text, 1, "", "\n");
    pp_var("last_free_data_cluster_count", sector.last_free_data_cluster_count, 1, "", "\n");
    pp_var("recently_allocated_data_cluster_count", sector.recently_allocated_data_cluster_count, 1, "", "\n");
    pp_var("signature3", sector.signature3, 1, "", "\n");
    pp_decrease_global_indent();
}


void tmp_fat_read_all_lfn_entries(FAT32_PART* part, FILE* file) {
        uint16_t full_name[256];
        char text[256];
        memset(text, 0x00, 256);
        memset(full_name, 0x00, 256*2);

        pp_title("lfn_entries", 1, "", ":\n");

        FAT_lfn_entry lfn_entry;
        fread(&lfn_entry, sizeof(FAT_lfn_entry), 1, file);

        uint16_t len = 0;
        do {
            pp_var("sequence_number", lfn_entry.sequence_number, 2, "- ", "");
            if(lfn_entry.sequence_number == 0xe5) printf(" %s(deleted entry)%s", REDB, COLOR_RESET);
            if((lfn_entry.sequence_number & 0x40) == 0x40) printf(" %s(last)%s", MAG, COLOR_RESET);

            utf16_to_utf8((utf16_t*)lfn_entry.name_characters1, 5, (utf8_t*)text, 5);
            pp_var("name_characters1", text, PP_NO_INDENT, " ", "");

            utf16_to_utf8((utf16_t*)lfn_entry.name_characters2, 6, (utf8_t*)text, 6);
            pp_var("name_characters2", text, PP_NO_INDENT, " ", "");

            utf16_to_utf8((utf16_t*)lfn_entry.name_characters3, 2, (utf8_t*)text, 2);
            pp_var("name_characters3", text, PP_NO_INDENT, " ", "");

            pp_var("checksum", lfn_entry.checksum, PP_NO_INDENT, " ", "\n");

            if(len > 0) {
                memcpy(full_name + 13, full_name, len+13);
            }
            mempcpy(full_name, lfn_entry.name_characters1, sizeof(lfn_entry.name_characters1));
            mempcpy(full_name + 5, lfn_entry.name_characters2, sizeof(lfn_entry.name_characters2));
            mempcpy(full_name + 5 + 6, lfn_entry.name_characters3, sizeof(lfn_entry.name_characters3));
            len += 13;
            
            fread(&lfn_entry, sizeof(FAT_lfn_entry), 1, file);
        } while(lfn_entry.attributes == 0x0F);

        // If we are here it means we read an entry that wasn't a LFN entry, seek back to avoid errors.
        fseek(file, -sizeof(FAT_lfn_entry), SEEK_CUR);

        utf16_to_utf8((utf16_t*)full_name, len+13, (utf8_t*)text, len+13);
        pp_var("long_file_name", text, 1,"", "\n");
}

void tmp_fat_read_cluster_entries(FAT32_PART* part, FILE* file) {
    pp_title("dir_entry @ sector ", 0, "", "");
    printf(CYN "%ld" COLOR_RESET, ftell(file)/512);
    pp_title(" offset ", PP_NO_INDENT, "", "");
    printf(CYN "%ld\n" COLOR_RESET, ftell(file)%512);

    FAT_directory_entry entry;
    fread(&entry, sizeof(FAT_directory_entry), 1, file);

    bool is_lfn_entry = entry.attribute_readonly && entry.attribute_hidden && entry.attribute_system && entry.attribute_volume_label && entry.start_of_file_or_lowbytes == 0;
    if(is_lfn_entry) {
        fseek(file, -sizeof(FAT_lfn_entry), SEEK_CUR); // Seek back and let tmp_fat_read_all_lfn_entries deal with reading the lfns
        tmp_fat_read_all_lfn_entries(part, file);
        // Read the "normal" entry
        fread(&entry, sizeof(FAT_directory_entry), 1, file);
    }

    pp_var("short_name", (char*)entry.short_name, 1, "", "");
    pp_var("short_ext", (char*)entry.short_name_ext, PP_NO_INDENT, " | ", "");
    pp_var("first_byte", (uint8_t)(entry.short_name[0]), PP_NO_INDENT, " | ", "\n");

    pp_enum_start("attributes", 1, "");
    if(entry.attribute_readonly) pp_enum_value("readonly");
    if(entry.attribute_hidden) pp_enum_value("hidden");
    if(entry.attribute_system) pp_enum_value("system");
    if(entry.attribute_volume_label) pp_enum_value("volume_label");
    if(entry.attribute_subdirectory) pp_enum_value("subdirectory");
    if(entry.attribute_archive) pp_enum_value("archive");
    if(entry.attribute_device) pp_enum_value("device");
    if(entry.attribute_reserved) pp_enum_value("reserved");
    pp_enum_end("\n");

    pp_var("create_date", entry.create_date, 1, "", ""); pp_var("fine", (uint8_t)(entry.create_time_fine * 10), PP_NO_INDENT, " | ", "\n", "ms");
    pp_var("last_modified_date", entry.last_modified_date, 1, "", "\n");
    pp_var("last_access_date", entry.last_access_date, 1, "", "\n");
    
    uint32_t cluster_number = entry.high_bytes_cluster_number_or_access_rights<<16  | entry.start_of_file_or_lowbytes;
    pp_var("cluster_number", cluster_number, 1, "", "\n");
    pp_var("file_size_bytes", entry.file_size_bytes, 1, "", "\n", "bytes");

    printf(COLOR_RESET);
}

void read_fat32_fat(FAT32_PART* part, FILE* file, uint32_t offset, uint32_t fatno) {
    pp_increase_global_indent();
    pp_indent(0); printf("Reading FAT tables\n");

    uint32_t fat_offset = offset + (part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.reserved_logical_sector_count + part->boot_sector.bios_parameter_block.logical_sector_per_file_allocation_table*fatno) * part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.bytes_per_logical_sector;
    fseek(file, fat_offset, SEEK_SET);

    pp_title("file_allocation_table @ sector ", 0, "", "");
    printf(CYN "%d\n" COLOR_RESET, fat_offset/512);
    
    uint8_t x1;
    fread(&x1, 1, 1, file);
    pp_var("media_descriptor", x1, 1, "", "\n");
    fread(&x1, 1, 1, file);
    pp_var("ones", x1, 1, "", "\n");
    fread(&x1, 1, 1, file);
    pp_var("ones", x1, 1, "", "\n");
    fread(&x1, 1, 1, file);
    pp_var("ones", x1, 1, "", "\n");

    uint32_t x2;
    fread(&x2, 4, 1, file);
    pp_var("end_of_cluster", x2, 1, "", "\n");

    uint32_t entry_count = part->boot_sector.bios_parameter_block.logical_sector_per_file_allocation_table * part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.bytes_per_logical_sector / 4;
    pp_var("entry_count", entry_count, 1, "", "\n");

    for (uint32_t cluster_no = 0; cluster_no < entry_count; cluster_no++) {
        fread(&x2, 4, 1, file);
        x2 &= 0x0FFFFFFF;

        if(x2 == 0) continue; // Free cluster

        uint32_t disk_sector = offset/512 + part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.reserved_logical_sector_count + part->boot_sector.bios_parameter_block.logical_sector_per_file_allocation_table*2 + (cluster_no) * part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.logical_sectors_per_cluster;

        if(0x00000002 <= x2 && x2 <= 0x0FFFFFEF) {
            pp_fat_chain("next_cluster", x2, cluster_no, disk_sector, 1, "- ", "\n");
        }
        if(x2 >= 0x0FFFFFF8) {
            pp_fat_chain("end_cluster_chain", x2, cluster_no, disk_sector, 1, "- ", "\n");
        }
        if(x2 == 0x0FFFFFF7) {
            pp_fat_chain("bad_cluster", x2, cluster_no, disk_sector, 1, "- ", "\n");
        }
    }

    uint32_t root_dir_cluster = offset/512 + part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.reserved_logical_sector_count + part->boot_sector.bios_parameter_block.logical_sector_per_file_allocation_table*2 + part->boot_sector.bios_parameter_block.root_culster_number - 2;

    pp_increase_global_indent();

    fseek(file, root_dir_cluster*part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.bytes_per_logical_sector, SEEK_SET);
    pp_indent(0); printf("Reading entries in root dir disk sector %d\n", root_dir_cluster);

    tmp_fat_read_cluster_entries(part, file);
    tmp_fat_read_cluster_entries(part, file);
    tmp_fat_read_cluster_entries(part, file);
    tmp_fat_read_cluster_entries(part, file);
    tmp_fat_read_cluster_entries(part, file);

    pp_decrease_global_indent();
    pp_decrease_global_indent();
}

bool read_fat32_part(FAT32_PART* part, FILE* file, uint32_t offset) {
    memset(part, 0x00, sizeof(FAT32_PART));

    //Boot sector
    fseek(file, offset, SEEK_SET);
    fread(&part->boot_sector, sizeof(FAT_FAT32_boot_sector), 1, file);
    if(part->boot_sector.signature != 0xaa55) return false;
    print_fat32_bootsector(part->boot_sector, offset);


    uint32_t information_sector_offet = offset + part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.bytes_per_logical_sector * part->boot_sector.bios_parameter_block.information_sector_logical_sector_number;
    fseek(file, information_sector_offet, SEEK_SET);
    fread(&part->information_sector, sizeof(FAT_FAT32_information_sector), 1, file);
    if(part->information_sector.signature3 != 0xaa550000) return false;
    print_fat32_information_sector(part->information_sector, information_sector_offet);

    read_fat32_fat(part, file, offset, 0);
    // tmp_read_fat(part, file, offset, 1); // Don't bother reading the identical copy

    return true;
}
