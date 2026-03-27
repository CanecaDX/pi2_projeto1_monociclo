#include <stdlib.h>
#include <stdio.h>
#include "registers.h"

uint16_t *init_regs(void){
    uint16_t *regs = calloc(8, sizeof(uint16_t));
    return regs;
}

void print_regs(uint16_t *regs, int count){
    printf("\nBanco de registradores: ");
    for(int i = 0; i < count; i++){
        printf("\n$[%d] = %u", i, regs[i]);
    }
}
