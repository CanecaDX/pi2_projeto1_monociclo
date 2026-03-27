#include <stdio.h>
#include "run.h"
#include "decoder.h"

void executar_programa(uint16_t *program_mem, int program_mem_size){
    if (!program_mem || program_mem_size <= 0) {
        printf("\nCarregue a memoria de instrucoes antes.");
        return;
    }

    for (int pc = 0; pc < program_mem_size; pc++) {
        decode(program_mem[pc]);
    }
}
