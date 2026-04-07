#include <stdlib.h>
#include "pc.h"

ProgramCounter *pc_create(uint8_t pc_index){
    ProgramCounter *pc = malloc(sizeof(ProgramCounter));
    if (!pc) return NULL;
    pc->pc_index = pc_index;
    return pc;
}

void pc_set(ProgramCounter *pc, uint8_t pc_index){
    if (!pc) return;
    pc->pc_index = pc_index;
}

void pc_step(ProgramCounter *pc){
    In_ULA ula_pc_input = {0};
    Out_ULA ula_pc_output = {0};
    ula_pc_input.op1 = pc->pc_index;
    ula_pc_input.op2 = 1;
    ula_pc_input.ula_op = 0x0;
    if (!pc) return;
    ula_pc_output = ulaExecuta(&ula_pc_input);
    pc_set(pc, (uint8_t)ula_pc_output.resultado);  

}

void copiaPC(ProgramCounter* pc_backup, ProgramCounter* pc){
 pc_backup->pc_index = pc->pc_index;
 pc_backup->jump_flag = pc->jump_flag;
 pc_backup->beq_flag = pc->beq_flag;
}