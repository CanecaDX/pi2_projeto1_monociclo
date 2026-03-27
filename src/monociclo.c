
#include <stdlib.h>
#include "monociclo.h"
#include "registers.h"
#include "instruction_mem.h"

#define MEM_DATA_SIZE 256

Monociclo *monociclo_create(void){
    Monociclo *m = malloc(sizeof(Monociclo));
    if (!m) return NULL;

    m->pc = 0;
    m->regs = init_regs();
    m->mem_data = calloc(MEM_DATA_SIZE, sizeof(uint16_t));
    m->mem_inst = NULL;
    m->mem_inst_size = 0;

    return m;
}

void monociclo_destroy(Monociclo *m){
    if (!m) return;
    free(m->regs);
    free(m->mem_data);
    free(m->mem_inst);
    free(m);
}
