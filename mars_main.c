#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "decoder.h"
#include "monociclo.h"

    
int main(){
    int op;
    Monociclo *m = monociclo_create();
    Monociclo  *m_backup = monociclo_create();

    if (!m) {
        printf("\nFalha ao alocar monociclo.");
        return 1;
    }
    //teste de representação dos registradores
    //m->regs_bank->registradores[1] = -5;
    //m->regs_bank->registradores[2] = 10;

    do{
        printf("\n------------------------------------");
        printf("\n0_ Fechar programa");
        printf("\n1_ Carregar memória de dados .dat");
        printf("\n2_ Carregar memória de instruções .mem");
        printf("\n3_ Imprimir memória de dados");
        printf("\n4_ Imprimir memória de instruções");
        printf("\n5_ Imprimir banco de registradores");
        printf("\n6_ Imprimir instruçoes em asm");
		printf("\n7_ Imprimir simulador");
        printf("\n8_ Salvar arquivo assembly .asm");
        printf("\n9_ Salvar dados .dat");
        printf("\n10_ Rodar programa");
        printf("\n11_ Rodar 1 instrução");
        printf("\n12_ Voltar 1 instrução");
        printf("\n13_ Exibir estatísticas");
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
            case 5: print_regs(m->regs_bank); break;
            case 6: exibeTodos_asm(m->mem_inst); break;
            case 7:	print_instruction_memory(m->mem_inst); printf("\n"); data_memory_print(m->mem_data); print_regs(m->regs_bank); printf("\n"); exibeTodos_asm(m->mem_inst); printf("\n"); printf("\n\nPC ESTÁ EM : %d\n", m->pc->pc_index); break;
            case 8: mem_to_asm(m->mem_inst); break;
            case 9: data_memory_save(m->mem_data, "output_dados.dat"); break;
            case 10: run(m); break;
            case 11: run_step(m); copiaSimulador(m_backup,m); break;
            case 12: copiaSimulador(m,m_backup); printf("VOLTOU 1 INSTRUCAO ! \n"); printf("PC ESTÁ EM : %d \n", m->pc->pc_index);  break;
            default: printf("\nOpção inválida!"); break;
        }
    }while(op != 0);

    return 0;
}
