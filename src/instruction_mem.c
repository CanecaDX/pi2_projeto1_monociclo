#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "instruction_mem.h"
#include "decoder.h"

Memoria_instrucao *instruction_memory_create(void){
    Memoria_instrucao *mem = calloc(1, sizeof(Memoria_instrucao));
    if (!mem) return NULL;

    mem->instrucao = calloc(INSTR_MEM_SIZE, sizeof(Instrucao));
    if (mem->instrucao == NULL) {
        perror("Erro ao alocar memória");
        free(mem);
        return NULL;
    }

    mem->size = INSTR_MEM_SIZE;
    mem->loaded_count = 0;
    return mem;
}

static int get_mem_file(const char *mem_name, Instrucao *instructions, int *size) {
    char line[18]; 
    int is_binary = 1, i;

    if (!instructions || !size) return -1;

    FILE *file = fopen(mem_name, "rb");
    if (file == NULL) {
        perror("Erro ao abrir arquivo .mem");
        return -1;
    }

    if (fgets(line, sizeof(line), file) != NULL) {
        for (i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n' || line[i] == '\r') continue;
            if (line[i] != '0' && line[i] != '1') {
                is_binary = 0;
                break;
            }
        }

        rewind(file);

        if (is_binary) {
            int count = 0;
            while (fgets(line, sizeof(line), file) != NULL) {
                // Remover \n e \r do final da linha
                char *p = line;
                while (*p != '\0') {
                    if (*p == '\n' || *p == '\r') {
                        *p = '\0';
                        break;
                    }
                    p++;
                }
                if (line[0] == '\0') continue; // Ignora linhas vazias
                instructions[count].instr = (uint16_t)strtol(line, NULL, 2);
                count++;
                if (count >= INSTR_MEM_SIZE) break;
            }

            *size = count;
            printf("\nMemória de instruções carregada..");
            fclose(file);
            return 0;
        }
    }

    // binário bruto
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size < 0) {
        perror("Erro ao obter tamanho do arquivo");
        fclose(file);
        return -1;
    }

    uint16_t raw[INSTR_MEM_SIZE];
    size_t bytes_expected = (size_t)file_size;
    size_t max_bytes = sizeof(raw);
    if (bytes_expected > max_bytes) bytes_expected = max_bytes;

    size_t bytes_read = fread(raw, 1, bytes_expected, file);
    if (bytes_read != bytes_expected) {
        perror("Erro ao ler arquivo");
        fclose(file);
        return -1;
    }

    *size = (int)(bytes_read / sizeof(uint16_t));
    for (int idx = 0; idx < *size; idx++) {
        instructions[idx].instr = raw[idx];
    }
    printf("\nMemória de instruções carregada..");
    fclose(file);
    return 0;
}
 
Memoria_instrucao *instruction_memory_load_file(const char *mem_name){
    Memoria_instrucao *mem = instruction_memory_create();
    if (!mem) return NULL;

    int size = 0;
    if (get_mem_file(mem_name, mem->instrucao, &size) != 0) {
        free(mem->instrucao);
        free(mem);
        return NULL;
    }

    mem->loaded_count = size;
    return mem;
}

void print_instruction_memory(const Memoria_instrucao *mem){
    if (!mem || !mem->instrucao) return;
    printf("\n\n\n");
    printf("MEMÓRIA DE INSTRUÇÕES: ");
    for (int i = 0; i < INSTR_MEM_SIZE; i++){
        printf("\nInstr[%d] = ", i);
        print_binary(mem->instrucao[i].instr);
    }
    printf("\n");
}

void print_binary(uint16_t value){
    for(int i = 15; i >= 0; i--)
        printf("%d", (value >> i) & 1);
}

void mem_to_asm(Memoria_instrucao *mem) {
    printf("GERANDO ARQUIVO .ASM ...");
    FILE *file = fopen("program.asm", "w");
    if (!file) {
        perror("Erro ao criar arquivo .asm");
        return;
    }

    int count = mem ? mem->loaded_count : 0;
    for (int i = 0; i < count; i++) {
        Instrucao raw = mem->instrucao[i];
        Decoded d = decode(raw.instr);

        if (d.type == TYPE_R) {
            switch (d.funct) {
                case 0x0: // add
                    fprintf(file, "add $%u, $%u, $%u\n", d.rd, d.rs, d.rt);
                    break;
                case 0x2: // sub
                    fprintf(file, "sub $%u, $%u, $%u\n", d.rd, d.rs, d.rt);
                    break;
                case 0x4: // and
                    fprintf(file, "and $%u, $%u, $%u\n", d.rd, d.rs, d.rt);
                    break;
                case 0x5: // or
                    fprintf(file, "or $%u, $%u, $%u\n", d.rd, d.rs, d.rt);
                    break;
            }
        } else if (d.type == TYPE_I) {
            switch (d.opcode) {
                case 0x4: // addi
                    fprintf(file, "addi $%u, $%u, %d\n", d.rt, d.rs, d.imm);
                    break;
                case 0xB: // lw
                    fprintf(file, "lw $%u, %d($%u)\n", d.rt, d.imm, d.rs);
                    break;
                case 0xF: // sw
                    fprintf(file, "sw $%u, %d($%u)\n", d.rt, d.imm, d.rs);
                    break;
                case 0x8: // beq
                    fprintf(file, "beq $%u, $%u, %d\n", d.rt, d.rs, d.imm);
                    break;
            }
        } else if (d.type == TYPE_J) {
            switch(d.opcode){
                case 0x2: // j
                    fprintf(file, "j %u\n", d.address);
                    break;
            }
        }
    }

    fclose(file);
}

void print_asm(Decoded d){
	   
        if (d.type == TYPE_R) {
            switch (d.funct) {
                case 0x0: // add
                    printf("add $%u, $%u, $%u\n", d.rd, d.rs, d.rt);
                    break;
                case 0x2: // sub
                    printf("sub $%u, $%u, $%u\n", d.rd, d.rs, d.rt);
                    break;
                case 0x4: // and
                    printf("and $%u, $%u, $%u\n", d.rd, d.rs, d.rt);
                    break;
                case 0x5: // or
                    printf("or $%u, $%u, $%u\n", d.rd, d.rs, d.rt);
                    break;
            }
        } else if (d.type == TYPE_I) {
            switch (d.opcode) {
                case 0x4: // addi
                    printf("addi $%u, $%u, %d\n", d.rt, d.rs, d.imm);
                    break;
                case 0xB: // lw
                    printf("lw $%u, %d($%u)\n", d.rt, d.imm, d.rs);
                    break;
                case 0xF: // sw
                    printf("sw $%u, %d($%u)\n", d.rt, d.imm, d.rs);
                    break;
                case 0x8: // beq
                    printf("beq $%u, $%u, %d\n", d.rt, d.rs, d.imm);
                    break;
            }
        } else if (d.type == TYPE_J) {
            switch(d.opcode){
                case 0x2: // j
                    printf("j %u\n", d.address);
                    break;
            }
        }
    }	

void exibe1_asm(Memoria_instrucao *mem, int index){
	
	int count = mem ? mem->loaded_count : 0;
	
	if(!count){
		printf("Erro ao imprimir assembly");
		return;
	}
	
        Instrucao raw = mem->instrucao[index];
        Decoded d = decode(raw.instr);
		print_asm(d);
			if (d.type == TYPE_R) {
				switch (d.funct) {
					case 0x0: // add
						printf("Soma o conteudo do registrador $%u com o conteudo de $%u e armazena em $%u", d.rs, d.rt, d.rd);
						break;
					case 0x2: // sub
						printf("Subtrai o conteudo do registrador $%u com o conteudo de $%u e armazena em $%u", d.rs, d.rt, d.rd);
						break;
					case 0x4: // and
						printf("Faz um AND com o conteudo do registrador $%u com o conteudo de $%u e armazena em $%u", d.rs, d.rt, d.rd);
						break;
					case 0x5: // or
						printf("Faz um OR com o conteudo do registrador $%u com o conteudo de $%u e armazena em $%u", d.rs, d.rt, d.rd);
						break;
				}
			}else if(d.type == TYPE_I){
				switch (d.opcode){
				case 0x4: // addi
                    printf("Soma o valor imediato %d com o conteudo do registrador $%u e armazena em $%u", d.imm, d.rs, d.rt);
                    break;
                case 0xB: // lw
					printf("Carrega o conteudo armazenado na posicao %d da memoria para o registrador $%u", d.imm, d.rt);
                    break;
                case 0xF: // sw
                    printf("Armazena o conteudo do registrador $%u na posicao %d da memoria", d.rt, d.imm);
                    break;
                case 0x8: // beq
                    printf("Se os valores dos registradores $%u e $%u forem iguais, realiza um salto para a posicao informada.", d.rt, d.rs);
                break;
				}	
            }else if(d.type == TYPE_J){
               switch (d.opcode){
                case 0x2: // j
                    printf("Realiza um salto para posicao %u", d.address);
                    break;
               }
            }
		printf("\n");
}

void exibeTodos_asm(Memoria_instrucao *mem){
	
	int count = mem ? mem->loaded_count : 0;
	
	if(!count){
		printf("Não há instruções carregadas na memória ainda. Para visualizá-las, carregue um arquivo .mem primeiro.");
		return;
	}
	
	  for (int i = 0; i < count; i++) {
        Instrucao raw = mem->instrucao[i];
        Decoded d = decode(raw.instr);
        print_asm(d);
      }
}

void exibeEst(Memoria_instrucao *mem){
	
	//tipos
	int r = 0, im = 0, j = 0;
	
	//classes
	int mem_d = 0, desC = 0, arit = 0;
	
	int count = mem ? mem->loaded_count : 0;
	
	printf("\n");
	printf("%d instruções carregadas", count);
	printf("\n");
	
	for (int i = 0; i < count; i++) {
        Instrucao est = mem->instrucao[i];
        Decoded d = decode(est.instr);
        
        if(d.type == TYPE_R){
			r++;
		}else if(d.type == TYPE_I){
			im++;
		}else{
			j++;	
		}	
		
		if(d.type == TYPE_I && (d.opcode == 0xB || d.opcode == 0xF))
			mem_d++;
			
		if(d.type == TYPE_I && d.opcode == 0x8)
			desC++;
			
		if((d.type == TYPE_R || d.type == TYPE_I) && (d.opcode != 0x8 && d.opcode  && 0xB && d.opcode != 0xF))
			arit++;
    }
    printf("\nTIPOS");
    printf("\n%d instruções do tipo R", r);
    printf("\n%d instruções do tipo I", im);
    printf("\n%d instruções do tipo J", j);
    
    printf("\n");
    
    printf("\nCLASSES");
    printf("\n%d operações de lógica e aritimética;", arit);
    printf("\n%d operações de desvio incodicional;", j);
    printf("\n%d operações de desvio condicional;", desC);
    printf("\n%d operações de transferência de dados.", mem_d);
    
    return;
}


