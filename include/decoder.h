#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>

//usa enum para determinar o tipo de instruções
//vai acessar os campos da struct baseado no index do enum

typedef enum { TYPE_R, TYPE_I, TYPE_J } InstrType;

typedef struct {
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t funct;
    int8_t imm;   
    uint16_t address;
    InstrType type;
} Decoded;

Decoded decode(uint16_t instruction);

#endif
