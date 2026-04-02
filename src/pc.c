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
    if(pc->jump_flag == 1){
        // TODO: calcular salto via ULA e atualizar pc_index
        //chama o pc_set
        pc->jump_flag = 0;
    }else if(pc->beq_flag == 1){
        // TODO: calcular beq via ULA e atualizar pc_index
        //chama o pc_set
        pc->beq_flag = 0;
    }else{
        ula_pc_output = ulaExecuta(&ula_pc_input);
        pc_set(pc, (uint8_t)ula_pc_output.resultado);
    }
}
