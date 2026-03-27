#include <stdio.h>
#include <stdlib.h>
#include "data_mem.h"

Memoria_D *inicializa_memoria_dados(void){
	int i;
	Memoria_D *memoria_dados = calloc(Tam_Memoria, sizeof(Memoria_D));
	if (!memoria_dados) return NULL;

	for(i = 0; i< Tam_Memoria; i++) {
		(memoria_dados+i)->valor = 0;
	}

	return memoria_dados;
}

void Carregar_memoria_dados(Memoria_D *memoria_dados, const char *nome_arquivo){
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
		int8_t buffer[Tam_Memoria];
		size_t count = fread(buffer, sizeof(int8_t), Tam_Memoria, file);

		for (size_t i = 0; i < count; i++) {
			(memoria_dados + i)->valor = buffer[i];
		}
		for (size_t i = count; i < Tam_Memoria; i++) {
			(memoria_dados + i)->valor = 0;
		}
	} else {
		int cont = 0;
		int aux = 0;

		while (cont < Tam_Memoria && fscanf(file, "%d", &aux) == 1) {
			if (aux <= 127 && aux >= -128) {
				(memoria_dados + cont)->valor = (int8_t)aux;
			} else {
				printf("\ndado maior que suportado pelo programa ");
				(memoria_dados + cont)->valor = 0;
			}
			cont++;
		}
		for (int i = cont; i < Tam_Memoria; i++) {
			(memoria_dados + i)->valor = 0;
		}
	}

	printf("\nMemoria carregada com sucesso...");
	fclose(file);
}

void imprimir_memoria_dados(Memoria_D * memoria_dados){
	int i;
	printf("\nMemória de dados: ");
	for(i = 0; i< Tam_Memoria; i++) {
		printf("\n[%d] : %d",i, (memoria_dados+i)->valor);
}
}

