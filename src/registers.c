#include <stdlib.h>
#include <stdio.h>
#include "registers.h"

Banco_registradores *registers_create(int count){
    if (count <= 0) count = 8;

    Banco_registradores *regs = calloc(1, sizeof(Banco_registradores));
    if (!regs) return NULL;

    regs->registradores = calloc((size_t)count, sizeof(uint8_t));
    if (!regs->registradores) {
        free(regs);
        return NULL;
    }

    regs->count = count;
    return regs;
}

void print_regs(const Banco_registradores *regs){
    if (!regs || !regs->registradores) return;
    printf("\nBanco de registradores: ");
    for (int i = 0; i < regs->count; i++){
        printf("\n$%d = %u", i, regs->registradores[i]);
    }
}
