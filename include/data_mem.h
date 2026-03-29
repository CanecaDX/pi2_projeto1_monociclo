#ifndef DATA_MEM_H
#define DATA_MEM_H

#include <stdint.h>

#define DATA_MEM_SIZE 256

typedef struct {
	int8_t valor;
} Dado;

typedef struct {
	Dado *dado;
	int size;
} Memoria_dado;

Memoria_dado *data_memory_create(void);
void data_memory_load(Memoria_dado *mem, const char *nome_arquivo);
void data_memory_print(const Memoria_dado *mem);

#endif
