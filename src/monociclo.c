
#include <stdlib.h>
#include "monociclo.h"

Monociclo *monociclo_create(void){
    Monociclo *m = malloc(sizeof(Monociclo));
    if (!m) return NULL;

    m->regs_bank = registers_create(8);
    m->mem_data = data_memory_create();
    m->mem_inst = instruction_memory_create();
    m->pc = pc_create(m->mem_inst ? m->mem_inst->instrucao : NULL);
    m->controle = NULL;
    m->decoded_inst = calloc(1, sizeof(Decoded));
    m->ula = calloc(1, sizeof(ULA));

    if (!m->pc || !m->regs_bank || !m->mem_data || !m->mem_inst || !m->decoded_inst || !m->ula) {
        if (m->pc) {
            free(m->pc);
        }
        if (m->regs_bank) {
            free(m->regs_bank->registradores);
            free(m->regs_bank);
        }
        if (m->mem_data) {
            free(m->mem_data->dado);
            free(m->mem_data);
        }
        if (m->mem_inst) {
            free(m->mem_inst->instrucao);
            free(m->mem_inst);
        }
        if (m->decoded_inst) {
            free(m->decoded_inst);
        }
        if (m->ula) {
            free(m->ula);
        }
        free(m);
        return NULL;
    }

    return m;
}

int run_step(Monociclo *m){
    Instrucao *instrucao = NULL;
    size_t size = 0;
    Instrucao *pc_inst = NULL;
    Decoded decoded_inst = {0};
    In_controle in_controle = {0};
    Out_controle sinais = {0};
    int8_t rs_valor = 0;
    int8_t rt_valor = 0;
    uint8_t rd = 0x0;
    int8_t inst_op1 = 0;
    int8_t inst_op2 = 0;
    Out_ULA out_ula = {0};
    uint8_t overflow = 0;
    int8_t mem_data_valor = 0;
    int8_t mem_data_valor_escrever = 0;
    int8_t zero = 0;
    int8_t ula_resultado = 0;

    //verifica se os componentes existem e se o pc aponta para uma instruçao
    if (!m || !m->pc || !m->mem_inst || !m->mem_inst->instrucao) return -1;
    if (!m->pc->adress) return -1;

    // Base e tamanho efetivo da memoria de instrucoes carregada.
    instrucao = m->mem_inst->instrucao;
    size = (size_t)m->mem_inst->size;
    if (size == 0) return 1;

    // Se o PC sair do range do vetor o programa termina
    if (m->pc->adress < instrucao || m->pc->adress >= instrucao + size) return 1;

    //pega a instrução  no endereço do pc->address
    pc_inst = m->pc->adress;
    decoded_inst = decode(pc_inst->instr);
    // passa opcode e function para o controle, gera sinais
    in_controle.opcode = decoded_inst.opcode;
    in_controle.function = decoded_inst.funct;
    
    //sinais
    sinais = controle_sinais(in_controle);

    //incrementa o pc
    pc_step(m->pc);

    //add datapath
    return 0;
}

int run(Monociclo *m){
    int status = 0;
    while ((status = run_step(m)) == 0) {
    }
    return status;
}

int run_back(Monociclo *m){
    (void)m;
    return -1;
}
