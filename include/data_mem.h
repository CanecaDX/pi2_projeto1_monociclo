#ifndef DATA_MEM_H
#define DATA_MEM_H

#include <stdint.h>

#define DATA_MEM_SIZE 256

typedef struct {
	uint8_t write_mem;
	uint8_t read_mem;
	int adress;
	int8_t dado_escrever;
}In_data_mem;

typedef struct{
	int8_t dado_lido;
}Out_data_mem;

typedef struct {
	In_data_mem in_data;
	Out_data_mem out_data;
	int8_t *dado;
	int size;
} Memoria_dado;


Memoria_dado *data_memory_create(void);
void data_memory_load(Memoria_dado *mem, const char *nome_arquivo);
void data_memory_print(const Memoria_dado *mem);
Out_data_mem ex_data_mem(In_data_mem input, Memoria_dado *mem);
void data_memory_save(Memoria_dado *mem, const char *nome_arquivo);
void copiaMemoria(Memoria_dado* memoria_backup, Memoria_dado* memoria);


#endif
