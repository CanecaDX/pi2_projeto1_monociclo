#ifndef MONOCICLO_H
#define MONOCICLO_H

#include <stdint.h>

typedef struct {
    uint32_t pc;
    uint16_t *regs;        // banco de registradores
    uint16_t *mem_data;    // memória de dados
    uint16_t *mem_inst;    // memória de instruções
    int mem_inst_size;
} Monociclo;

Monociclo *monociclo_create(void);
void monociclo_destroy(Monociclo *m);

#endif
