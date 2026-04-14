#ifndef MONOCICLO_H
#define MONOCICLO_H

#include "pc.h"
#include "registers.h"
#include "instruction_mem.h"
#include "data_mem.h"
#include "controle.h"
#include "decoder.h"
#include "ULA.h"

typedef struct {
    ProgramCounter *pc;
    Banco_registradores *regs_bank;
    Memoria_dado *mem_data;
    Memoria_instrucao *mem_inst;
    Controle *controle;
    Decoded *decoded_inst;
    ULA *ula;
    int has_executed;
    int just_rewound;
} Monociclo;

Monociclo *monociclo_create(void);
int run(Monociclo *m);
int run_step(Monociclo *m);
int run_back(Monociclo *m); 
void copiaSimulador (Monociclo * m_backup, Monociclo* m);

#endif
