
#include <stdlib.h>
#include <stdio.h>
#include "monociclo.h"
#include "stats.h"

Monociclo *monociclo_create(void){
    Monociclo *m = malloc(sizeof(Monociclo));
    if (!m) return NULL;

    m->regs_bank = registers_create();
    m->mem_data = data_memory_create();
    m->mem_inst = instruction_memory_create();
    m->pc = pc_create(0);
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
    Out_registers regs_output = {0};
    In_ULA ula_input = {0};
    Out_ULA ula_output = {0};
    In_data_mem data_mem_input = {0};
    Out_data_mem data_mem_output = {0};
    


    //verifica se os componentes existem e se o pc aponta para uma instruçao
    if (!m || !m->pc || !m->mem_inst || !m->mem_inst->instrucao) return -1;

    // Base e tamanho efetivo da memoria de instrucoes carregada.
    instrucao = m->mem_inst->instrucao;
    size = (size_t)m->mem_inst->loaded_count;
    if (size == 0) return 1;

    // Se o PC sair do range do vetor o programa termina
    if ((size_t)m->pc->pc_index >= size) return 1;

    pc_inst = &instrucao[m->pc->pc_index];
    decoded_inst = decode(pc_inst->instr);

    // passa opcode e function para o controle, gera sinais
    in_controle.opcode = decoded_inst.opcode;
    in_controle.function = decoded_inst.funct;
    
    //sinais
    sinais = controle_sinais(in_controle);

    //trata j e beq dentro do pc_step???
    //como voltar ao inicio do fluxo do monociclo???
    pc_step(m->pc);

    //sinaliza qual é o rs
    m->regs_bank->in_regs.write_reg = sinais.RegWrite;
    m->regs_bank->in_regs.reg_base1 = decoded_inst.rs;
    m->regs_bank->in_regs.reg_base2 = decoded_inst.rt;

    //"MUX" que determina se o registrador de destino é rt ou rd
    if(sinais.RegDst == 0x1){
        m->regs_bank->in_regs.reg_destino = decoded_inst.rd;
    } else {
        m->regs_bank->in_regs.reg_destino = decoded_inst.rt;   
    }

    //pega os valores dos registradores base
    regs_output = ex_registers(m->regs_bank->in_regs, m->regs_bank);

    //prepara os dados para a ula(reg base1, reg base2 ou imm)

    ula_input.op1 = regs_output.val1;
    ula_input.ula_op = sinais.ULA_op;

    //"MUX" que determina se o segundo op da ula é reg base 2 ou imm
    if(sinais.ULASrc == 0x1){
        ula_input.op2 = decoded_inst.imm;
    } else {
        ula_input.op2 = regs_output.val2;
    }

    ula_output = ulaExecuta(&ula_input);

    //prepara os dados para a memória de dados
    data_mem_input.adress = ula_output.resultado;
    data_mem_input.write_mem = sinais.MemWrite;
    data_mem_input.read_mem = sinais.MemRead;
    data_mem_input.dado_escrever = regs_output.val2;

    //chama a memória de dados e envia os dados
    data_mem_output = ex_data_mem(data_mem_input, m->mem_data);

    //"MUX" que determina o que vai pro banco
    if(sinais.Memtoreg == 0x1){
        m->regs_bank->in_regs.dado_escrever = data_mem_output.dado_lido;
    } else {
        m->regs_bank->in_regs.dado_escrever = ula_output.resultado;
    }
    //chama a função dos registradores, só escreve se a flag de escrita for 1
    ex_registers(m->regs_bank->in_regs, m->regs_bank);

    return 0;
}

int run(Monociclo *m){
    int status = 0;
    while ((status = run_step(m)) == 0) {
    }
    printf("Programa finalizado!");
    return status;
}

int run_back(Monociclo *m){
    (void)m;
    return -1;
}
