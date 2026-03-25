#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Tam_Memoria 256


typedef struct {
    int valor;
} Memoria_D;

typedef struct {
    int pc;
    Memoria_D* memoria_dados; 
} Monociclo;

Memoria_D * aloca_memoria_dados();
Monociclo * alocaMonociclo();

void inicializa_memoria_dados(Memoria_D * memoria_dados);
void CarregarMemoriaDados(Memoria_D * memoria_dados);
void imprimir_memoria_dados(Memoria_D * memoria_dados);


int main(){
	
	Monociclo* monociclo;
	monociclo = NULL;
	monociclo = alocaMonociclo();

inicializa_memoria_dados(monociclo->memoria_dados);
CarregarMemoriaDados(monociclo->memoria_dados);
imprimir_memoria_dados(monociclo->memoria_dados);

printf("teste");


return 0;
}


//Alloca memória de instruções
Memoria_D * aloca_memoria_dados(){
    Memoria_D* memoria_dados;
    memoria_dados = (Memoria_D*) malloc(Tam_Memoria*sizeof(Memoria_D));
    return memoria_dados;
}

Monociclo * alocaMonociclo() {
	Monociclo* monociclo;
	monociclo = (Monociclo*) malloc(sizeof(Monociclo));
	monociclo->memoria_dados = aloca_memoria_dados();
	return monociclo;
	}

void inicializa_memoria_dados(Memoria_D * memoria_dados){
	int i;
	for(i = 0; i< Tam_Memoria; i++) {
		(memoria_dados+i)->valor = 0;
}
}

void CarregarMemoriaDados(Memoria_D * memoria_dados){
	int cont=0;
	int aux[Tam_Memoria];
    char nome_arquivo[100];
   
	strcpy(nome_arquivo,"memoria1.dat");
	
	FILE *file = fopen(nome_arquivo, "r");
	if (file == NULL) {
		printf("Erro ao abrir o arquivo");

	}
	
 while (cont < Tam_Memoria && fscanf(file, "%d", &aux[cont]) == 1) {
		if (aux[cont] < 127 && aux[cont] > -128) {
			(memoria_dados+cont)->valor = aux[cont];
		} else {
			printf("dado maior que suportado pelo programa \n");
			(memoria_dados+cont)->valor = 0;
		};
		
        cont++;
    }

	printf("Memoria carregada com sucesso...\n");
	free(*aux);
	fclose(file);
}	

void imprimir_memoria_dados(Memoria_D * memoria_dados){
	int i;
	for(i = 0; i< Tam_Memoria; i++) {
		printf("[%d] : %d \n",i, (memoria_dados+i)->valor);
}
}





