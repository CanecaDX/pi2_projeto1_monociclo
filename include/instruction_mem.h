#ifndef INSTR_MEM_H
#define INSTR_MEM_H

#include <stdint.h>

#define INSTR_MEM_SIZE 256

//criar contador para quando carregar arquivo da memória (mem_to_asm)

typedef enum { TYPE_R = 0, TYPE_I, TYPE_J } Tipo;

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

typedef struct{
    uint16_t instr_lida;
}Out_instruction_mem;

typedef struct {
    uint16_t instr;
} Instrucao;

typedef struct {
    Out_instruction_mem out_instr;
    Instrucao *instrucao;
    int size; 
    int loaded_count; 
} Memoria_instrucao;

Memoria_instrucao *instruction_memory_create(void);
Memoria_instrucao *instruction_memory_load_file(const char *mem_name);
void print_instruction_memory(const Memoria_instrucao *mem);
void print_binary(uint16_t value);
void mem_to_asm(Memoria_instrucao *mem);
void print_asm(Decoded d);
void exibe1_asm(Memoria_instrucao *mem, int index);
void exibeTodos_asm(Memoria_instrucao *mem);


#endif
