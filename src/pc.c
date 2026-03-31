#include <stdlib.h>
#include "pc.h"

ProgramCounter *pc_create(Instrucao *adress){
    ProgramCounter *pc = malloc(sizeof(ProgramCounter));
    if (!pc) return NULL;
    pc->adress = adress;
    return pc;
}

void pc_set(ProgramCounter *pc, Instrucao *adress){
    if (!pc) return;
    pc->adress = adress;
}

void pc_step(ProgramCounter *pc){
    if (!pc) return;
    if (!pc->adress) return;
    pc->adress++;
}
