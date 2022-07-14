#include "fat16.h"
#include "fat.h"
#include "pretty_print.h"
#include "ansi.h"


void print_fat16_bios_parameter_block(FAT_extended_bios_parameter_block block) {
    print_dos331_bios_parameter_block(block.dos31_bpb);

    pp_title("Extended BPB", 1, "", "\n");
    pp_increase_global_indent();
    pp_var("physical_drive_number", block.physical_drive_number, 1, "", "\n");
    pp_var("fat16_fat12_reserved", block.fat16_fat12_reserved, 1, "", "\n");
    pp_var("extended_boot_signature", block.extended_boot_signature, 1, "", "\n");
    pp_var("volume_id", block.volume_id, 1, "", "\n");
    pp_var("volume_label", block.volume_label, 1, "", "\n");
    pp_var("file_system_type", block.file_system_type, 1, "", "\n");
    pp_decrease_global_indent();

}
void print_fat16_bootsector(FAT_boot_sector sector, uint32_t offset) {
    pp_increase_global_indent();
    pp_title("boot_sector @ disk sector ", 0, "", "");
    printf(CYN "%d\n" COLOR_RESET, offset/512);

    pp_var("oem_name", sector.oem_name, 1, "", "\n");

    print_fat16_bios_parameter_block(sector.bios_parameter_block);

    pp_var("physical_drive_number", sector.physical_drive_number, 1, "", "\n");
    pp_var("signature", sector.signature, 1, "", "\n");
    pp_decrease_global_indent();
}


bool read_fat16_part(FAT_PART* part, FILE* file, uint32_t offset) {
    fseek(file, offset, SEEK_SET);
    fread(part, sizeof(FAT_PART), 1, file);
    if(part->boot_sector.signature != 0xaa55) return false;
    return true;
}

