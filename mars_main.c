#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "registers.h"
#include "instruction_mem.h"
#include "decoder.h"
#include "data_mem.h"
#include "run.h"

int main(){
    int op;
    //inicializa regs, memória de instruções e de dados
    uint16_t *regs = init_regs();
    uint16_t *program_mem = NULL;
    //serve para saber o tamanho do programa carregado, atuaiza a cada carga
    int program_mem_size = 0;
    Memoria_D *data_mem = inicializa_memoria_dados();
    if (!data_mem) {
        printf("\nFalha ao alocar memoria de dados.");
        free(regs);
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
                Carregar_memoria_dados(data_mem, data_name);
                break;
            }
            case 2: {
                char mem_name[128];
                printf("\nInforme o arquivo .mem: ");
                scanf("%127s", mem_name);
                free(program_mem);
                program_mem = get_mem_file(mem_name, &program_mem_size); 
                break;
            }
            case 3: imprimir_memoria_dados(data_mem); break;
            case 4: print_instruction_memory(program_mem, program_mem_size); break;
            case 5: print_regs(regs, 8); break;
			case 6: print_instruction_memory(program_mem, program_mem_size); print_regs(regs, 8); imprimir_memoria_dados(data_mem); break;
            //no momento, somente passa por todas as instruções decodificando
            case 9: executar_programa(program_mem, program_mem_size); break;
            default: printf("\nOpção inválida!"); break;
        }
    }while(op != 0);

    free(regs);
    free(program_mem);
    free(data_mem);
    return 0;
}
