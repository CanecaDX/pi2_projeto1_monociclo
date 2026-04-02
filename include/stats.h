#ifndef STATS_H
#define STATS_H

typedef struct {
    int num_instrucoes;
    int num_ciclos;
    int num_instrucoes_tipo[3]; //índice equivale ao enum de tipos
    int num_ula;
    int acessos_data_mem;
    int acessos_banco_reg;
} Estatisticas;

#endif
