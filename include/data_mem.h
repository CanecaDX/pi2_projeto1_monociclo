#ifndef DATA_MEM_H
#define DATA_MEM_H

#include <stdint.h>

#define Tam_Memoria 256

typedef struct {
	int16_t valor;
} Memoria_D;

Memoria_D *inicializa_memoria_dados(void);
void Carregar_memoria_dados(Memoria_D *memoria_dados, const char *nome_arquivo);
void imprimir_memoria_dados(Memoria_D *memoria_dados);

#endif
