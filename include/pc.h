#ifndef PC_H
#define PC_H

#include <stdint.h>
#include "instruction_mem.h"
#include "ULA.h"

typedef struct {
    uint8_t pc_index;
    uint8_t jump_flag;
    uint8_t beq_flag;
} ProgramCounter;

ProgramCounter *pc_create(uint8_t pc_index);
void pc_set(ProgramCounter *pc, uint8_t pc_index);
void pc_step(ProgramCounter *pc);
void copiaPC(ProgramCounter* pc_backup, ProgramCounter* pc);

#endif
