
#ifndef INSTR_MEM_H
#define INSTR_MEM_H

#include <stdint.h>

uint16_t *get_mem_file(char *mem_name, int *size);
void print_instruction_memory(uint16_t *instructions, int size);
void print_binary(uint16_t value);

#endif
