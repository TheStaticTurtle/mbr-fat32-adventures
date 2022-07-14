#include "mbr.h"
#include "fat.h"
#include "utf-convert.h"
#include "ansi.h"

// printf("\t\t last_free_data_cluster_count = %" PRIu16 " (0x%04" PRIx16 ")\n", sector.last_free_data_cluster_count, sector.last_free_data_cluster_count);
// printf("\t\t last_free_data_cluster_count = %" PRIu32 " (0x%08" PRIx32 ")\n", sector.last_free_data_cluster_count, sector.last_free_data_cluster_count);
// printf("\t\t last_free_data_cluster_count = %" PRIu8 " (0x%02x)\n", sector.last_free_data_cluster_count, sector.last_free_data_cluster_count);

void print_dos331_bios_parameter_block(FAT_DOS331_bios_parameter_block dos31_bpb) {
    printf("\t\tDOS2.0 BPB\n");
    printf("\t\t\tbytes_per_logical_sector = %" PRIu16 " (0x%04" PRIx16 ")\n", dos31_bpb.dos20_bpb.bytes_per_logical_sector, dos31_bpb.dos20_bpb.bytes_per_logical_sector);
    printf("\t\t\tlogical_sectors_per_cluster = %" PRIu8 " (0x%02x)\n", dos31_bpb.dos20_bpb.logical_sectors_per_cluster, dos31_bpb.dos20_bpb.logical_sectors_per_cluster);
    printf("\t\t\treserved_logical_sector_count = %" PRIu16 " (0x%04" PRIx16 ")\n", dos31_bpb.dos20_bpb.reserved_logical_sector_count, dos31_bpb.dos20_bpb.reserved_logical_sector_count);
    printf("\t\t\tfile_allocation_table_count = %" PRIu8 " (0x%02x)\n", dos31_bpb.dos20_bpb.file_allocation_table_count, dos31_bpb.dos20_bpb.file_allocation_table_count);
    printf("\t\t\tmax_root_entries = %" PRIu16 " (0x%04" PRIx16 ")\n", dos31_bpb.dos20_bpb.max_root_entries, dos31_bpb.dos20_bpb.max_root_entries);
    printf("\t\t\tlogical_sector_count = %" PRIu16 " (0x%04" PRIx16 ")\n", dos31_bpb.dos20_bpb.logical_sector_count, dos31_bpb.dos20_bpb.logical_sector_count);
    printf("\t\t\tmedia_descriptor = %" PRIu8 " (0x%02x)\n", dos31_bpb.dos20_bpb.media_descriptor, dos31_bpb.dos20_bpb.media_descriptor);
    printf("\t\t\tlogical_sector_per_file_allocation_table = %" PRIu16 " (0x%04" PRIx16 ")\n", dos31_bpb.dos20_bpb.logical_sector_per_file_allocation_table, dos31_bpb.dos20_bpb.logical_sector_per_file_allocation_table);
    
    printf("\t\tDOS3.1 BPB\n");
    printf("\t\t\tphysical_sectors_per_track = %" PRIu16 " (0x%04" PRIx16 ")\n", dos31_bpb.physical_sectors_per_track, dos31_bpb.physical_sectors_per_track);
    printf("\t\t\tnumber_of_heads = %" PRIu16 " (0x%04" PRIx16 ")\n", dos31_bpb.number_of_heads, dos31_bpb.number_of_heads);
    printf("\t\t\thidden_sector_count = %" PRIu32 " (0x%08" PRIx32 ")\n", dos31_bpb.hidden_sector_count, dos31_bpb.hidden_sector_count);
    printf("\t\t\tlogical_sector_count = %" PRIu32 " (0x%08" PRIx32 ")\n", dos31_bpb.logical_sector_count, dos31_bpb.logical_sector_count);
}

void print_fat16_bios_parameter_block(FAT_extended_bios_parameter_block block) {
    print_dos331_bios_parameter_block(block.dos31_bpb);
    
    printf("\t\tExtended BPB\n");
    printf("\t\t\tphysical_drive_number = %" PRIu8 " (0x%02" PRIx8 ")\n", block.physical_drive_number, block.physical_drive_number);
    printf("\t\t\tfat16_fat12_reserved = %" PRIu8 " (0x%02" PRIx8 ")\n", block.fat16_fat12_reserved, block.fat16_fat12_reserved);
    printf("\t\t\textended_boot_signature = %" PRIu8 " (0x%02" PRIx8 ")\n", block.extended_boot_signature, block.extended_boot_signature);
    printf("\t\t\tvolume_id = %" PRIu32 " (0x%08" PRIx32 ")\n", block.volume_id, block.volume_id);
    printf("\t\t\tvolume_label = \"%.11s\"\n", block.volume_label);
    printf("\t\t\tfile_system_type = \"%.8s\"\n", block.file_system_type);
}
void print_fat32_bios_parameter_block(FAT_FAT32_extended_bios_parameter_block block) {
    print_dos331_bios_parameter_block(block.dos31_bpb);

    printf("\t\tFAT32 Extended BPB\n");

    printf("\t\t\tlogical_sector_per_file_allocation_table = %" PRIu32 " (0x%08" PRIx32 ")\n", block.logical_sector_per_file_allocation_table, block.logical_sector_per_file_allocation_table);
    printf("\t\t\tdrive_description = %" PRIu16 " (0x%04" PRIx16 ")\n", block.drive_description, block.drive_description);
    printf("\t\t\tversion = %" PRIu16 " (0x%04" PRIx16 ")\n", block.version, block.version);
    printf("\t\t\troot_culster_number = %" PRIu32 " (0x%08" PRIx32 ")\n", block.root_culster_number, block.root_culster_number);
    printf("\t\t\tinformation_sector_logical_sector_number = %" PRIu16 " (0x%04" PRIx16 ")\n", block.information_sector_logical_sector_number, block.information_sector_logical_sector_number);
    printf("\t\t\tfirst_boot_sector_copy_logical_sector_number = %" PRIu16 " (0x%04" PRIx16 ")\n", block.first_boot_sector_copy_logical_sector_number, block.first_boot_sector_copy_logical_sector_number);
    printf("\t\t\tphysical_drive_number = %" PRIu8 " (0x%02" PRIx8 ")\n", block.physical_drive_number, block.physical_drive_number);
    printf("\t\t\tfat16_fat12_reserved = %" PRIu8 " (0x%02" PRIx8 ")\n", block.fat16_fat12_reserved, block.fat16_fat12_reserved);
    printf("\t\t\textended_boot_signature = %" PRIu8 " (0x%02" PRIx8 ")\n", block.extended_boot_signature, block.extended_boot_signature);
    printf("\t\t\tvolume_id = %" PRIu32 " (0x%08" PRIx32 ")\n", block.volume_id, block.volume_id);
    printf("\t\t\tvolume_label = \"%.11s\"\n", block.volume_label);
    printf("\t\t\tfile_system_type = \"%.8s\"\n", block.file_system_type);
}

void print_fat16_bootsector(FAT_boot_sector sector) {
    printf("\t\toem_name = \"%s\"\n" , sector.oem_name);
    print_fat16_bios_parameter_block(sector.bios_parameter_block);
    printf("\t\tphysical_drive_number = %d\n" , sector.physical_drive_number);
    printf("\t\tboot_sector_signature = 0x%04" PRIx16 "\n", sector.signature);
}
void print_fat32_bootsector(FAT_FAT32_boot_sector sector) {
    printf("\t\toem_name = \"%s\"\n" , sector.oem_name);
    print_fat32_bios_parameter_block(sector.bios_parameter_block);
    printf("\t\tphysical_drive_number = %d\n" , sector.physical_drive_number);
    printf("\t\tboot_sector_signature = 0x%04" PRIx16 "\n", sector.signature);
}

void print_fat32_informationsector(FAT_FAT32_information_sector sector) {
    printf("\t\tsignature1 = \"%.4s\"\n" , sector.signature1);
    printf("\t\tsignature2 = \"%.4s\"\n" , sector.signature2);
    printf("\t\tlast_free_data_cluster_count = %" PRIu32 " (0x%08" PRIx32 ")\n", sector.last_free_data_cluster_count, sector.last_free_data_cluster_count);
    printf("\t\trecently_allocated_data_cluster_count = %" PRIu32 " (0x%08" PRIx32 ")\n", sector.recently_allocated_data_cluster_count, sector.recently_allocated_data_cluster_count);
    // bool signature3_valid = ((sector.signature3[0] == sector.signature3[1]) == sector.signature3[2]) == sector.signature3[3];
    // printf("\t\tsignature3 = %s (%x,%x,%x,%x)\n" , signature3_valid ? "valid" : "invalid", sector.signature3[0] , sector.signature3[1] , sector.signature3[2] , sector.signature3[3]);
    printf("\t\tsignature3 = %" PRIu32 " (0x%08" PRIx32 ")\n", sector.signature3, sector.signature3);
}

void print_fat16_part(FAT_PART part) {
    printf("\tboot_sector:\n");
    print_fat16_bootsector(part.boot_sector);
}
void print_fat32_part(FAT32_PART part) {
    printf("\tboot_sector:\n");
    print_fat32_bootsector(part.boot_sector);
    printf("\tinformation_sector:\n");
    print_fat32_informationsector(part.information_sector);
}


FAT_FATtype get_fattype(void *rawpart) {
    uint8_t* u8rawpart = (uint8_t*)rawpart;


    FAT_PART part = *(FAT_PART*)rawpart;
    if( part.boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.max_root_entries == 0 && (u8rawpart[0x42] == 0x29 || u8rawpart[0x42] == 0x28)) {
            return FAT_TYPE_FAT32;
    }
    return FAT_TYPE_FAT16;
}
FAT_FATtype get_fattype(FILE* file, uint32_t offset) {
    fseek(file, offset, SEEK_SET);
    FAT_PART part;
    read_fat16_part(&part, file, offset);
    return get_fattype(&part);
}

unsigned char lfn_checksum(const unsigned char *pFCBName)
{
   int i;
   unsigned char sum = 0;

   for (i = 11; i; i--)
      sum = ((sum & 1) << 7) + (sum >> 1) + *pFCBName++;

   return sum;
}


void tmp_print_fat_time(FAT_datetime datetime) {
    printf("%02d:%02d:%02d %04d/%02d/%02d", datetime.hours, datetime.minutes, datetime.seconds*2, datetime.year+1980, datetime.month, datetime.day);
}


void tmp_fat_read_all_lfn_entries(FAT32_PART* part, FILE* file) {
        uint16_t full_name[256];
        char text[256];
        memset(text, 0x00, 256);
        memset(full_name, 0x00, 256*2);

        printf("\t %slfn_entries:%s\n", CYN, COLOR_RESET);
        FAT_lfn_entry lfn_entry;
        fread(&lfn_entry, sizeof(FAT_lfn_entry), 1, file);

        uint16_t len = 0;
        do {

            printf("\t\t- %ssequence%s=0x%02" PRIx8 "", CYN, ANSI_VAL_NUM, lfn_entry.sequence_number);
            if(lfn_entry.sequence_number == 0xe5) printf(" %s(deleted entry)%s", RED, COLOR_RESET);
            if((lfn_entry.sequence_number & 0x40) == 0x40) printf(" %s(last)%s", MAG, COLOR_RESET);

            utf16_to_utf8((utf16_t*)lfn_entry.name_characters1, 5, (utf8_t*)text, 5);
            printf(" %sname_characters1%s=\"%.5s\",", CYN, ANSI_VAL_TXT, text);
            utf16_to_utf8((utf16_t*)lfn_entry.name_characters2, 6, (utf8_t*)text, 6);
            printf(" %sname_characters2%s=\"%.6s\",", CYN, ANSI_VAL_TXT, text);
            utf16_to_utf8((utf16_t*)lfn_entry.name_characters3, 2, (utf8_t*)text, 2);
            printf(" %sname_characters3%s=\"%.2s\",", CYN, ANSI_VAL_TXT, text);

            printf(" %schecksum%s=0x%02" PRIx8 "", CYN, ANSI_VAL_NUM, lfn_entry.checksum);

            printf("\n");
            
            if(len > 0) {
                memcpy(full_name + 13, full_name, len+13);
            }
            mempcpy(full_name, lfn_entry.name_characters1, sizeof(lfn_entry.name_characters1));
            mempcpy(full_name + 5, lfn_entry.name_characters2, sizeof(lfn_entry.name_characters2));
            mempcpy(full_name + 5 + 6, lfn_entry.name_characters3, sizeof(lfn_entry.name_characters3));
            // memcpy(full_name + 13, full_name, len);

            len += 13;
            
            fread(&lfn_entry, sizeof(FAT_lfn_entry), 1, file);
        } while(lfn_entry.attributes == 0x0F);

        // If we are here it means we read an entry that wasn't a LFN entry, seek back to avoid errors.
        fseek(file, -sizeof(FAT_lfn_entry), SEEK_CUR);

        utf16_to_utf8((utf16_t*)full_name, len+13, (utf8_t*)text, len+13);
        printf("\t %slong_file_name%s = \"%s\"%s\n", CYN, ANSI_VAL_TXT, text, COLOR_RESET);

}

void tmp_fat_read_cluster_entries(FAT32_PART* part, FILE* file) {
    printf("reading next entry in cluster,");

    FAT_directory_entry entry;
    fread(&entry, sizeof(FAT_directory_entry), 1, file);

    bool lfn = entry.attribute_readonly && entry.attribute_hidden && entry.attribute_system && entry.attribute_volume_label && entry.start_of_file_or_lowbytes == 0;

    if(lfn) {
        printf(" found an LFN entry, reading all LFN entries before reading the \"normal\" entry.\n");
        fseek(file, -sizeof(FAT_lfn_entry), SEEK_CUR); // Seek back and let tmp_fat_read_all_lfn_entries deal with reading the lfns
        tmp_fat_read_all_lfn_entries(part, file);

        // Read the "normal" entry
        fread(&entry, sizeof(FAT_directory_entry), 1, file);
    } else {
        printf(" found a \"normal\" entry.\n");
    }

    printf("\t %sshort_name%s = \"%.8s\" ", ANSI_VAR, ANSI_VAL_TXT, entry.short_name);
    printf(" %sshort_ext%s = \"%.3s\"", ANSI_VAR, ANSI_VAL_TXT, entry.short_name_ext);
    printf(" %sfirst_byte%s = (0x%02x)\n", ANSI_VAR, ANSI_VAL_TXT, entry.short_name[0]);

    printf("\t %sattributes%s = ", ANSI_VAR, ANSI_VAL_ENUM);
    if(entry.attribute_readonly) printf("readonly ");
    if(entry.attribute_hidden) printf("hidden ");
    if(entry.attribute_system) printf("system ");
    if(entry.attribute_volume_label) printf("volume_label ");
    if(entry.attribute_subdirectory) printf("subdirectory ");
    if(entry.attribute_archive) printf("archive ");
    if(entry.attribute_device) printf("device ");
    if(entry.attribute_reserved) printf("reserved ");
    printf("\n");

    printf("\t %screate_date%s = ", ANSI_VAR, ANSI_VAL_NUM); tmp_print_fat_time(entry.create_date);
    printf(" | %sfine%s = %" PRIu16 "ms (0x%02" PRIx8 ")\n", ANSI_VAR, ANSI_VAL_NUM, entry.create_time_fine * 10, entry.create_time_fine);

    printf("\t %slast_modified_date%s = ", ANSI_VAR, ANSI_VAL_NUM); tmp_print_fat_time(entry.last_modified_date);
    printf("\n");

    // printf("\t last_access_date = %" PRIu16 " (0x%04" PRIx16 ")\n", entry.last_access_date, entry.last_access_date);
    
    uint32_t cluster_number = entry.high_bytes_cluster_number_or_access_rights<<16  | entry.start_of_file_or_lowbytes;
    printf("\t %scluster_number%s = %" PRIu32 " (0x%08" PRIx32 ")\n", ANSI_VAR, ANSI_VAL_NUM, cluster_number, cluster_number);
    printf("\t %sfile_size_bytes%s = %" PRIu32 " (0x%08" PRIx32 ")\n", ANSI_VAR, ANSI_VAL_NUM, entry.file_size_bytes, entry.file_size_bytes);

    printf(COLOR_RESET);
}

void tmp_read_fat(FAT32_PART* part, FILE* file, uint32_t offset, uint32_t fatno) {
    uint32_t fat_offset = offset + (part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.reserved_logical_sector_count + part->boot_sector.bios_parameter_block.logical_sector_per_file_allocation_table*fatno) * part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.bytes_per_logical_sector;
    fseek(file, fat_offset, SEEK_SET);

    printf("\n--- Reading FAT n°%d at sector %" PRIu32 " ---\n\n", fatno, fat_offset/512);
    
    uint32_t x;

    fread(&x, 1, 1, file);
    printf("media_descriptor = %" PRIu8 " (0x%02" PRIx8 ")\n", x, x);
    fread(&x, 1, 1, file);
    printf("ones = %" PRIu8 " (0x%02" PRIx8 ")\n", x, x);
    fread(&x, 1, 1, file);
    printf("ones = %" PRIu8 " (0x%02" PRIx8 ")\n", x, x);
    fread(&x, 1, 1, file);
    printf("ones = %" PRIu8 " (0x%02" PRIx8 ")\n", x, x);

    fread(&x, 4, 1, file);
    printf("end_of_cluster = %" PRIu32 " (0x%08" PRIx32 ")\n", x, x);

    uint32_t entry_count = part->boot_sector.bios_parameter_block.logical_sector_per_file_allocation_table * part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.bytes_per_logical_sector / 4;
    printf("entry_count = %" PRIu32 "\n", entry_count);

    // uint32_t entries[entry_count];

    for (uint32_t i = 0; i < entry_count; i++) {
        fread(&x, 4, 1, file);

        x &= 0x0FFFFFFF;

        if(x == 0) continue; // Free cluster

        uint32_t ddd = offset/512 + part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.reserved_logical_sector_count + part->boot_sector.bios_parameter_block.logical_sector_per_file_allocation_table*2 + (i) * part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.logical_sectors_per_cluster;

        if(0x00000002 <= x && x <= 0x0FFFFFEF) {
            //Cluster
            printf("next_cluster (0x%08" PRIx32 ") cluster no %d, located at %d (%d)\n", x, i, ddd, ddd-2048);
            // entries[i-2] = x;
        }
        if(x >= 0x0FFFFFF8) {
            // End of cluster chain
            printf("end_cluster_chain (0x%08" PRIx32 ") cluster no %d, located at %d (%d)\n", x, i, ddd, ddd-2048);
        }
        if(x == 0x0FFFFFF7) {
            printf("bad_cluster (0x%08" PRIx32 ") cluster no %d, located at %d (%d)\n", x, i, ddd, ddd-2048);
        }
    }

    uint32_t root_dir_cluster = offset/512 + part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.reserved_logical_sector_count + part->boot_sector.bios_parameter_block.logical_sector_per_file_allocation_table*2 + part->boot_sector.bios_parameter_block.root_culster_number - 2;

    fseek(file, root_dir_cluster*part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.bytes_per_logical_sector, SEEK_SET);
    printf("\nReading entries in cluster %d (%d)\n", root_dir_cluster, root_dir_cluster-2048);
    tmp_fat_read_cluster_entries(part, file);
    tmp_fat_read_cluster_entries(part, file);
    tmp_fat_read_cluster_entries(part, file);
    tmp_fat_read_cluster_entries(part, file);
    tmp_fat_read_cluster_entries(part, file);
    // tmp_fat_read_entry(part, file, offset, root_dir_cluster);
    // tmp_fat_read_entry(part, file, offset, root_dir_cluster);
    // tmp_fat_read_entry(part, file, offset, root_dir_cluster);
    // tmp_fat_read_entry(part, file, offset, root_dir_cluster);
    // tmp_fat_read_entry(part, file, offset, root_dir_cluster);
    // tmp_fat_read_entry(part, file, offset, root_dir_cluster);
    // tmp_fat_read_entry(part, file, offset, root_dir_cluster+5);
    // tmp_fat_read_entry(part, file, offset, root_dir_cluster+10);

    // printf("\n\t entry_type type = ");
    // if(root_entry.attribute_readonly && root_entry.attribute_hidden && root_entry.attribute_system && root_entry.attribute_volume_label) { printf("long_file_name "); lfn = true;}
    // if(root_entry.short_name_8_3[0] == 0x00) { printf("end_of_directory "); }
    // if(root_entry.short_name_8_3[0] == 0xe5) { printf("unused "); }
    // printf("\n");


    printf("\n");
}

bool read_fat32_part(FAT32_PART* part, FILE* file, uint32_t offset) {
    memset(part, 0x00, sizeof(FAT32_PART));

    //Boot sector
    fseek(file, offset, SEEK_SET);
    fread(&part->boot_sector, sizeof(FAT_FAT32_boot_sector), 1, file);
    if(part->boot_sector.signature != 0xaa55) return false;

    //Information sector
    uint32_t information_sector_offet = offset + part->boot_sector.bios_parameter_block.dos31_bpb.dos20_bpb.bytes_per_logical_sector * part->boot_sector.bios_parameter_block.information_sector_logical_sector_number;
    fseek(file, information_sector_offet, SEEK_SET);
    fread(&part->information_sector, sizeof(FAT_FAT32_information_sector), 1, file);
    if(part->information_sector.signature3 != 0xaa550000) return false;
    
    print_fat32_part(*part);

    tmp_read_fat(part, file, offset, 0);
    // tmp_read_fat(part, file, offset, 1);

    return true;
}
bool read_fat16_part(FAT_PART* part, FILE* file, uint32_t offset) {
    fseek(file, offset, SEEK_SET);
    fread(part, sizeof(FAT_PART), 1, file);
    if(part->boot_sector.signature != 0xaa55) return false;
    return true;
}