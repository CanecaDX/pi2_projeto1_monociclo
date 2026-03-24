#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MEM_SIZE 256

uint16_t *get_mem_file(char *mem_name, int *size);
void print_binary(uint16_t value);
void print_instruction_memory(uint16_t *instructions, int size);

int main(){
	
	int op;
	int num_instructions = 0;
	uint16_t *instructions = NULL;
	
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
				free(instructions);
			break;
			case 1:
			printf("\nconstruindo");
			break;
			case 2:
				uint16_t *instructions = get_mem_file("instructions.mem", &num_instructions);		
				if (instructions == NULL) {
					fprintf(stderr, "Falha ao carregar arquivo\n");
						return 1;
				}
					
				printf("\nCarregadas %d instruções\n", num_instructions);				
			break;
			case 3:
			printf("\nconstruindo");
			break;
			case 4:
				printf("\nMostrando instruções carregadas: ");
				print_instruction_memory(instructions, num_instructions);
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

uint16_t *get_mem_file(char *mem_name, int *size) {
    FILE *file = fopen(mem_name, "rb");
    if (file == NULL) {
        perror("Erro ao abrir arquivo .mem");
        return NULL;
    }
    
    // Obter tamanho do arquivo (o ponteiro ira apontar para o final do arquivo e o valor sera armazenado no váriavel file_size)
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    
    // Alocar memória para as instruções (uint16_t = 2 bytes)
    uint16_t *instructions = (uint16_t *)malloc(file_size);
    if (instructions == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }
    printf("\nMemória alocada.");
    
    // Ler arquivo
    size_t bytes_read = fread(instructions, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Erro ao ler arquivo");
        free(instructions);
        fclose(file);
        return NULL;
    }
    
    *size = file_size / sizeof(uint16_t);  // Converter bytes em quantidade de uint16_t
    fclose(file); 	 	
    
    return instructions;
}

void print_instruction_memory(uint16_t *instructions, int size){

    printf("\nMemória de instruções:\n");

    for(int i = 0; i < size; i++)
    {
        printf("Instr[%d] = ", i);
        print_binary(instructions[i]);
        printf("\n");
    }
}

void print_binary(uint16_t value){

    for(int i = 15; i >= 0; i--)
        printf("%d", (value >> i) & 1);
        
}



