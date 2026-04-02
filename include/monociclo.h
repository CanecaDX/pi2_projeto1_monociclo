#ifndef MONOCICLO_H
#define MONOCICLO_H

#include "pc.h"
#include "registers.h"
#include "instruction_mem.h"
#include "data_mem.h"
#include "controle.h"
#include "decoder.h"
#include "ULA.h"
#include "stats.h"

typedef struct {
    ProgramCounter *pc;
    Banco_registradores *regs_bank;
    Memoria_dado *mem_data;
    Memoria_instrucao *mem_inst;
    Controle *controle;
    Decoded *decoded_inst;
    ULA *ula;
    Estatisticas stats;
} Monociclo;

Monociclo *monociclo_create(void);
int run(Monociclo *m);
int run_step(Monociclo *m);
int run_back(Monociclo *m); //precisa implementação

#endif
