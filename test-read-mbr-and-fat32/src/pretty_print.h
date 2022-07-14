#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "fat.h"

#define PP_NO_INDENT -1

static int global_indent = 0;
void pp_indent(int count);
void pp_increase_global_indent();
void pp_decrease_global_indent();

void pp_int_var(const char* var_name, const char* int_type, const char* hex_type, void* value, const char* prepend, const char* append, const char* unit);
void pp_var(const char* var_name, uint8_t value , int indent_count, const char* prepend, const char* append, const char* unit);
void pp_var(const char* var_name, uint8_t value , int indent_count, const char* prepend, const char* append);
void pp_var(const char* var_name, uint16_t value, int indent_count, const char* prepend, const char* append, const char* unit);
void pp_var(const char* var_name, uint16_t value, int indent_count, const char* prepend, const char* append);
void pp_var(const char* var_name, uint32_t value, int indent_count, const char* prepend, const char* append, const char* unit);
void pp_var(const char* var_name, uint32_t value, int indent_count, const char* prepend, const char* append);

void pp_var(const char* var_name, const char* value, int indent_count, const char* prepend, const char* append);

void pp_var(const char* var_name, FAT_datetime value, int indent_count, const char* prepend, const char* append);
void pp_var(const char* var_name, FAT_date value, int indent_count, const char* prepend, const char* append);

void pp_enum_start(const char* var_name, int indent_count, const char* prepend);
void pp_enum_value(const char* value);
void pp_enum_end(const char* append);

void pp_title(const char* var_name, int indent_count, const char* prepend, const char* append);

void pp_fat_chain(const char* chain_type, uint32_t chain_type_u32, uint32_t cluster_no, uint32_t disk_sector, int indent_count, const char* prepend, const char* append);