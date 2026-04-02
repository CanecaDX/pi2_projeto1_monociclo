#include <stdio.h>
#include <stdlib.h>
#include "data_mem.h"

Memoria_dado *data_memory_create(void){
	Memoria_dado *mem = calloc(1, sizeof(Memoria_dado));
	if (!mem) return NULL;

	mem->dado = calloc(DATA_MEM_SIZE, sizeof(int8_t));
	if (!mem->dado) {
		free(mem);
		return NULL;
	}

	mem->size = DATA_MEM_SIZE;
	return mem;
}

void data_memory_load(Memoria_dado *mem, const char *nome_arquivo){
	if (!mem || !mem->dado) return;

	FILE *file = fopen(nome_arquivo, "rb");
	if (file == NULL) {
		printf("Erro ao abrir o arquivo");
		return;
	}

	int is_binary = 0;
	int ch;
	while ((ch = fgetc(file)) != EOF) {
		unsigned char c = (unsigned char)ch;
		if (!((c >= '0' && c <= '9') || c == '-' || c == '+' || c == ' ' || c == '\n' || c == '\r' || c == '\t')) {
			is_binary = 1;
			break;
		}
	}
	rewind(file);

	if (is_binary) {
		int8_t buffer[DATA_MEM_SIZE];
		size_t count = fread(buffer, sizeof(int8_t), DATA_MEM_SIZE, file);

		for (size_t i = 0; i < count; i++) {
			mem->dado[i] = buffer[i];
		}
		for (size_t i = count; i < DATA_MEM_SIZE; i++) {
			mem->dado[i] = 0;
		}
	} else {
		int cont = 0;
		int aux = 0;

		while (cont < DATA_MEM_SIZE && fscanf(file, "%d", &aux) == 1) {
			if (aux <= 127 && aux >= -128) {
				mem->dado[cont] = (int8_t)aux;
			} else {
				printf("\ndado maior que suportado pelo programa ");
				mem->dado[cont] = 0;
			}
			cont++;
		}
		for (int i = cont; i < DATA_MEM_SIZE; i++) {
			mem->dado[i] = 0;
		}
	}

	printf("\nMemoria carregada com sucesso...");
	fclose(file);
}

void data_memory_print(const Memoria_dado *mem){
	if (!mem || !mem->dado) return;
	printf("\nMemória de dados: ");
	for (int i = 0; i < DATA_MEM_SIZE; i++) {
		printf("\n[%d] : %d", i, mem->dado[i]);
	}
}


Out_data_mem ex_data_mem(In_data_mem input, Memoria_dado *mem){
	Out_data_mem output = {0};
	if (input.adress < 0 || input.adress >= DATA_MEM_SIZE) {
		printf("\nEndereço de memória inválido: %d", input.adress);
		return output;
	}
	if (input.read_mem) {
		output.dado_lido = mem->dado[input.adress];
	}
	if (input.write_mem) {
		mem->dado[input.adress] = input.dado_escrever;
	}
	return output;
}

void data_memory_save(Memoria_dado *mem, const char *nome_arquivo){
	
	if (!mem || !mem->dado) return;
	
	FILE *file = fopen(nome_arquivo, "w"); 
	if (file == NULL) {
		printf("Erro ao abrir o arquivo para escrita");
		return;
	}
	
	for (int i = 0; i < mem->size; i++) {
		fprintf(file, "%d\n", mem->dado[i]);
	}
	
	printf("Memoria salva com sucesso em %s...", nome_arquivo);
	fclose(file);
}