#ifndef MONOCICLO_H
#define MONOCICLO_H

#include "data_mem.h"
#include "instruction_mem.h"
#include "pc.h"
#include "registers.h"
#include "decoder.h"
#include "controle.h"
#include "ula.h"

typedef struct {
    ProgramCounter *pc;
    Banco_registradores *regs;
    Memoria_dado *mem_data;
    Memoria_instrucao *mem_inst;
    Controle *controle;
    ULA *ula;
} Monociclo;

Monociclo *monociclo_create(void);
Monociclo *run(ProgramCounter *pc, Banco_registradores *regs, Memoria_dado *mem_data, Memoria_instrucao *mem_inst, Controle *controle, ULA *ula);

#endif
