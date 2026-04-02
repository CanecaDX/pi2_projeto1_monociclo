#include <stdlib.h>
#include <stdio.h>
#include "registers.h"

Banco_registradores *registers_create(){
    Banco_registradores *regs = calloc(1, sizeof(Banco_registradores));
    if (!regs) return NULL;

    regs->registradores = calloc((size_t)8, sizeof(uint8_t));
    if (!regs->registradores) {
        free(regs);
        return NULL;
    }

    return regs;
}

void print_regs(const Banco_registradores *regs){
    if (!regs || !regs->registradores) return;
    printf("\nBanco de registradores: ");
    for (int i = 0; i < 8; i++){
        printf("\n$%d = 0x%02X", i, (int8_t)(regs->registradores[i]));
    }
}

Out_registers ex_registers(In_registers input, Banco_registradores *regs){
    Out_registers output = {0};
    output.val1 = (int8_t)(regs->registradores[input.reg_base1]);
    output.val2 = (int8_t)(regs->registradores[input.reg_base2]);

    //so vai escrever o dado se o sinal for 1
    if(input.write_reg == 1){
        regs->registradores[input.reg_destino] = (uint8_t)(input.dado_escrever);
    }
    return output;
}