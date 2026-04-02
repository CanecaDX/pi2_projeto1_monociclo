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

void mem_to_asm(Memoria_instrucao *mem) {

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
            }
        } else if (d.type == TYPE_J) {
            switch(d.opcode){
                case 0x8: // beq
                    fprintf(file, "beq $%u, $%u, %d\n", d.rt, d.rs, d.imm);
                    break;
                case 0x2: // j
                    fprintf(file, "j %u\n", d.address);
                    break;
            }
        }
    }

    fclose(file);
}