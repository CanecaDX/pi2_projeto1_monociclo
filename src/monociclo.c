
#include <stdlib.h>
#include "monociclo.h"
#include "pc.h"

Monociclo *monociclo_create(void){
    Monociclo *m = malloc(sizeof(Monociclo));
    if (!m) return NULL;

    m->pc = pc_create();
    m->regs = registers_create(8);
    m->mem_data = data_memory_create();
    m->mem_inst = instruction_memory_create();
    m->controle = NULL;

    if (!m->pc || !m->regs || !m->mem_data || !m->mem_inst) {
        if (m->pc) {
            free(m->pc);
        }
        if (m->regs) {
            free(m->regs->registradores);
            free(m->regs);
        }
        if (m->mem_data) {
            free(m->mem_data->dado);
            free(m->mem_data);
        }
        if (m->mem_inst) {
            free(m->mem_inst->instrucao);
            free(m->mem_inst);
        }
        free(m);
        return NULL;
    }

    return m;
}

