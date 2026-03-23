#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//constantes
#define INST_MEM_SIZE 256
//tipo r
struct inst_r{
		uint8_t opcode;
		uint8_t rs;
		uint8_t rt;
		uint8_t rd;
		uint8_t function;
	};
//tipo i
struct inst_i{
		uint8_t opcode;
		uint8_t rs;
		uint8_t rt;
		uint8_t imm;
	};
//tipo j
struct inst_j{
		uint8_t opcode;
		uint8_t addres;
	};
	
//funções
uint16_t *get_mem_file(char *mem_name, int *size);
uint16_t *init_regs();
//recebe PC como parâmetro
uint8_t  *decoder(uint16_t *program_mem, int *PC);


int main(){
	int op;
	uint16_t *regs = init_regs();
	uint16_t *program_mem = NULL;
	uint16_t *data_mem = NULL;
	
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

uint16_t *init_regs(){
	uint16_t *regs = calloc(8, sizeof(uint16_t));
	return regs;
}
	/*
	 * uint8_t  *decoder(uint16_t *program_mem, int *PC){
	uint16_t inst_mem = program_mem[PC];
	
	//pega os 4 MSB de inst
	uint8_t opcode = (inst_mem >> 12) & 0xF; 
	
	if(opcode = 0){
		struct inst_r *inst = NULL;
		inst.opcode   = (inst >> 12) & 0xF;  
		inst.rs       = (inst >> 9)  & 0x7;  
		inst.rt       = (inst >> 6)  & 0x7;  
		inst.rd       = (inst >> 3)  & 0x7; 
		inst.function =  inst        & 0x7;  
		return inst;
	}else if(opcode = 0100){
		struct inst_i *inst = NULL;
		
		
	}
}*/



