#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "decoder.h"
#include "monociclo.h"

    
int main(){
    int op;
    Monociclo *m = monociclo_create();
    if (!m) {
        printf("\nFalha ao alocar monociclo.");
        return 1;
    }

    do{
        printf("\n------------------------------------");
        printf("\n0_ Fechar programa");
        printf("\n1_ Carregar memória de dados .dat");
        printf("\n2_ Carregar memória de instruções .mem");
        printf("\n3_ Imprimir dados na memória de dados");
        printf("\n4_ Imprimir dados na memória de instruções");
        printf("\n5_ Imprimir dados no banco de registradores");
        printf("\n6_ Imprimir dados do simulador");
        printf("\n7_ Salvar arquivo assembly .asm");
        printf("\n8_ Salvar dados .dat");
        printf("\n9_ Rodar programa");
        printf("\n10_ Rodar 1 instrução");
        printf("\n11_ Voltar 1 instrução");
        printf("\n------------------------------------");
        printf("\nInforme a opção desejada: ");
        scanf("%d", &op);

        switch(op){
            case 0: printf("\nEncerrando simulador.."); break;
            case 1: {
                char data_name[128];
                printf("\nInforme o arquivo .dat: ");
                scanf("%127s", data_name);
                data_memory_load(m->mem_data, data_name);
                break;
            }
            case 2: {
                char mem_name[128];
                printf("\nInforme o arquivo .mem: ");
                scanf("%127s", mem_name);
                Memoria_instrucao *new_mem = instruction_memory_load_file(mem_name);
                if (new_mem) {
                    if (m->mem_inst) {
                        free(m->mem_inst->instrucao);
                        free(m->mem_inst);
                    }
                    m->mem_inst = new_mem;
                }
                break;
            }
            case 3: data_memory_print(m->mem_data); break;
            case 4: print_instruction_memory(m->mem_inst); break;
            case 5: print_regs(m->regs); break;
            case 6: print_instruction_memory(m->mem_inst); print_regs(m->regs); data_memory_print(m->mem_data); break;
            case 9: break;
            default: printf("\nOpção inválida!"); break;
        }
    }while(op != 0);

    return 0;
}
