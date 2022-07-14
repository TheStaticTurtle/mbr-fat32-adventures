#include "pretty_print.h"
#include "ansi.h"


void pp_indent(int count) {
    if(count != PP_NO_INDENT) {
        for(int i=0; i<count; i++) printf("\t"); 
        for(int i=0; i<global_indent; i++) printf("\t"); 
    }
}

void pp_increase_global_indent() {
    global_indent++;
}
void pp_decrease_global_indent() {
    global_indent--;
}

void pp_int_var(const char* var_name, const char* int_type, const char* hex_type, void* value, const char* prepend, const char* append, const char* unit) {
    char format[512];
    sprintf(format, GRN "%s%s" COLOR_RESET " = " YEL "%%%s%s (0x%%%s)" COLOR_RESET "%s", prepend, var_name, int_type, unit, hex_type, append);
    printf(format, *(uint8_t*)value, *(uint8_t*)value); // uint8_t hack to make it compile
}

void pp_var(const char* var_name, uint8_t value, int indent_count, const  char* prepend, const char* append, const char* unit) {
    pp_indent(indent_count);
    pp_int_var(var_name, PRIu8, "02" PRIx8, &value, prepend, append, unit);
}
void pp_var(const char* var_name, uint8_t value, int indent_count, const  char* prepend, const char* append) {
    pp_indent(indent_count);
    pp_int_var(var_name, PRIu8, "02" PRIx8, &value, prepend, append, "");
}
void pp_var(const char* var_name, uint16_t value, int indent_count, const  char* prepend, const char* append, const char* unit) {
    pp_indent(indent_count);
    pp_int_var(var_name, PRIu16, "04" PRIx16, &value, prepend, append, unit);
}
void pp_var(const char* var_name, uint16_t value, int indent_count, const  char* prepend, const char* append) {
    pp_indent(indent_count);
    pp_int_var(var_name, PRIu16, "04" PRIx16, &value, prepend, append, "");
}
void pp_var(const char* var_name, uint32_t value, int indent_count, const char* prepend, const char* append, const char* unit) {
    pp_indent(indent_count);
    pp_int_var(var_name, PRIu32,"08" PRIx32, &value, prepend, append, unit);
}
void pp_var(const char* var_name, uint32_t value, int indent_count, const char* prepend, const char* append) {
    pp_indent(indent_count);
    pp_int_var(var_name, PRIu32,"08" PRIx32, &value, prepend, append, "");
}


void pp_var(const char* var_name, const char* value, int indent_count, const char* prepend, const char* append) {
    pp_indent(indent_count);
    printf(GRN "%s%s" COLOR_RESET " = " YEL "\"%s\"" COLOR_RESET "%s", prepend, var_name, value, append);
}


void pp_var(const char* var_name, FAT_datetime value, int indent_count, const char* prepend, const char* append) {
    pp_indent(indent_count);
    printf(GRN "%s%s" COLOR_RESET " = " YEL "%02d:%02d:%02d %04d/%02d/%02d" COLOR_RESET "%s", prepend, var_name, value.hours, value.minutes, value.seconds*2, value.year+1980, value.month, value.day, append);
}
void pp_var(const char* var_name, FAT_date value, int indent_count, const char* prepend, const char* append) {
    pp_indent(indent_count);
    printf(GRN "%s%s" COLOR_RESET " = " YEL "%04d/%02d/%02d" COLOR_RESET "%s", prepend, var_name, value.year+1980, value.month, value.day, append);
}


void pp_enum_start(const char* var_name, int indent_count, const char* prepend) {
    pp_indent(indent_count);
    printf(GRN "%s%s" COLOR_RESET " = " MAG "", prepend, var_name);
}
void pp_enum_value(const char* value) {
    printf("%s ", value);
}
void pp_enum_end(const char* append) {
    printf(COLOR_RESET "%s", append);
}


void pp_title(const char* var_name, int indent_count, const char* prepend, const char* append) {
    pp_indent(indent_count);
    printf(CYN "%s%s" COLOR_RESET "%s", prepend, var_name, append);
}


void pp_fat_chain(const char* chain_type, uint32_t chain_type_u32, uint32_t cluster_no, uint32_t disk_sector, int indent_count, const char* prepend, const char* append) {
    pp_indent(indent_count);
    printf(GRN "%s%s " COLOR_RESET "(" YEL "0x%08" PRIx32 "" COLOR_RESET ")", prepend, chain_type, chain_type_u32);
    printf(" cluster no " YEL "%" PRIu32 "" COLOR_RESET " (" YEL "0x%08" PRIx32 "" COLOR_RESET ")", cluster_no, cluster_no);
    printf(" located at disk sector " YEL "%" PRIu32 "" COLOR_RESET " (" YEL "0x%08" PRIx32 "" COLOR_RESET ")", disk_sector, disk_sector);
    printf("%s", append);
}