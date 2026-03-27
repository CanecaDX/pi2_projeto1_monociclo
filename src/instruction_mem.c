#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "instruction_mem.h"

#define MEM_SIZE 256

uint16_t *get_mem_file(char *mem_name, int *size) {
    char line[32];
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
            uint16_t *instructions = malloc(MEM_SIZE * sizeof(uint16_t));
            if(instructions == NULL){
                perror("Erro ao alocar memória");
                fclose(file);
                return NULL;
            }

            int count = 0;
            while(fgets(line, sizeof(line), file) != NULL){
                instructions[count] = (uint16_t)strtol(line, NULL, 2);
                count++;
            }

            *size = count;
            fclose(file);
            printf("\nArquivo texto binário detectado");
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

    uint16_t *instructions = (uint16_t *)malloc(MEM_SIZE * sizeof(uint16_t));
    if (instructions == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(instructions, 1, (size_t)file_size, file);
    if (bytes_read != (size_t)file_size) {
        perror("Erro ao ler arquivo");
        free(instructions);
        fclose(file);
        return NULL;
    }

    *size = file_size / sizeof(uint16_t);
    fclose(file);
    return instructions;
}

void print_instruction_memory(uint16_t *instructions, int size){
    printf("\nMemória de instruções: ");
    for(int i = 0; i < size; i++){
        printf("\nInstr[%d] = ", i);
        print_binary(instructions[i]);
    }
}

void print_binary(uint16_t value){
    for(int i = 15; i >= 0; i--)
        printf("%d", (value >> i) & 1);
}
