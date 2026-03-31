#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "instruction_mem.h"

Memoria_instrucao *instruction_memory_create(void){
    Memoria_instrucao *mem = calloc(1, sizeof(Memoria_instrucao));
    if (!mem) return NULL;

    mem->instrucao = calloc(INSTR_MEM_SIZE, sizeof(Instrucao));
    if (mem->instrucao == NULL) {
        perror("Erro ao alocar memória");
        free(mem);
        return NULL;
    }

    mem->size = 0;
    return mem;
}

static Instrucao *get_mem_file(const char *mem_name, int *size) {
    char line[17];
    int is_binary = 1, i;
    
    FILE *file = fopen(mem_name, "rb");
    if (file == NULL) {
        perror("Erro ao abrir arquivo .mem");
        return NULL;
    }

    if(fgets(line, sizeof(line), file) != NULL){
        for(i = 0; line[i] != '\0'; i++){
            if(line[i] == '\n') continue;
            if(line[i] != '0' && line[i] != '1'){
                is_binary = 0;
                break;
            }
        }

        rewind(file);

        if(is_binary){
            Instrucao *instructions = calloc(INSTR_MEM_SIZE, sizeof(Instrucao));
            if(instructions == NULL){
                perror("Erro ao alocar memória");
                fclose(file);
                return NULL;
            }

            int count = 0;
            while(fgets(line, sizeof(line), file) != NULL){
                instructions[count].instr = (uint16_t)strtol(line, NULL, 2);
                count++;
            }

            *size = count;
            printf("\nMemória de instruções carregada..");
            fclose(file);
            return instructions;
        }
    }

    // binário bruto
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size < 0) {
        perror("Erro ao obter tamanho do arquivo");
        fclose(file);
        return NULL;
    }

    uint16_t *raw = calloc(INSTR_MEM_SIZE, sizeof(uint16_t));
    if (raw == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(raw, 1, (size_t)file_size, file);
    if (bytes_read != (size_t)file_size) {
        perror("Erro ao ler arquivo");
        free(raw);
        fclose(file);
        return NULL;
    }

    Instrucao *instructions = calloc(INSTR_MEM_SIZE, sizeof(Instrucao));
    if (instructions == NULL) {
        perror("Erro ao alocar memória");
        free(raw);
        fclose(file);
        return NULL;
    }

    *size = (int)(file_size / sizeof(uint16_t));
    for (int idx = 0; idx < *size; idx++) {
        instructions[idx].instr = raw[idx];
    }
    free(raw);
    printf("\nMemória de instruções carregada..");
    fclose(file);
    return instructions;
}

Memoria_instrucao *instruction_memory_load_file(const char *mem_name){
    Memoria_instrucao *mem = instruction_memory_create();
    if (!mem) return NULL;

    int size = 0;
    Instrucao *instructions = get_mem_file(mem_name, &size);
    if (!instructions) {
        free(mem->instrucao);
        free(mem);
        return NULL;
    }

    free(mem->instrucao);
    mem->instrucao = instructions;
    mem->size = size;
    return mem;
}

void print_instruction_memory(const Memoria_instrucao *mem){
    if (!mem || !mem->instrucao) return;
    printf("\nMemória de instruções: ");
    for (int i = 0; i < INSTR_MEM_SIZE; i++){
        printf("\nInstr[%d] = ", i);
        print_binary(mem->instrucao[i].instr);
    }
}

void print_binary(uint16_t value){
    for(int i = 15; i >= 0; i--)
        printf("%d", (value >> i) & 1);
}
