#ifndef INSTR_MEM_H
#define INSTR_MEM_H

#include <stdint.h>

#define INSTR_MEM_SIZE 256

typedef enum { TYPE_R = 1, TYPE_I = 2, TYPE_J = 3 } Tipo;

typedef struct {
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t funct;
    int8_t imm;   
    uint16_t address;
    Tipo type;
} Decoded;

typedef struct {
	uint16_t instr;
} Instrucao;

typedef struct {
	Instrucao *instrucao;
	int size;
} Memoria_instrucao;

Memoria_instrucao *instruction_memory_create(void);
Memoria_instrucao *instruction_memory_load_file(const char *mem_name);
void print_instruction_memory(const Memoria_instrucao *mem);
void print_binary(uint16_t value);


#endif
