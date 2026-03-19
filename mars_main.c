#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 256

uint16_t *get_mem_file(char *mem_name, int *size);

int main(){
	int op;
	
	do{
		printf("\n------------------------------------");
		printf("\n0_ Fechar programa");
		printf("\n1_ Carregar memória de dados .dat");
		printf("\n2_ Carregar memória de instruções .mem");
		printf("\n3_ Imprimir dados na memória de dados");
		printf("\n4_ Imprimir dados na memória de instruções");
		printf("\n5_ Imprimir banco de registradores");
		printf("\n6_ Imprimir simulador");
		printf("\n7_ Salvar assembly .asm");
		printf("\n8_ Salvar dados .dat");
		printf("\n9_ Rodar programa");
		printf("\n10_ Rodar 1 instrução");
		printf("\n11_ Voltar 1 instrução");
		printf("\n------------------------------------");
		printf("\nInforme a ação desejada: ");
		scanf("%d", &op);
		
		switch(op){
			case 0: 
			printf("\nEncerrando simulador..");
			break;
			case 1:
			printf("\nconstruindo");
			break;
			case 2:
			printf("\nconstruindo");
			break;
			case 3:
			printf("\nconstruindo");
			break;
			case 4:
			printf("\nconstruindo");
			break;
			case 5:
			printf("\nconstruindo");
			break;
			case 6:
			printf("\nconstruindo");
			break;
			case 7:
			printf("\nconstruindo");
			break;
			case 8:
			printf("\nconstruindo");
			break;
			case 9:
			printf("\nconstruindo");
			break;
			case 10:
			printf("\nconstruindo");
			break;
			case 11:
			printf("\nconstruindo");
			break;
		}
	}while(op != 0);
	return 0;
}
