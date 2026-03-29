#ifndef CONTROLE_H
#define CONTROLE_H

#include <stdint.h>
#include "decoder.h"

typedef struct{
    uint8_t opcode;
    uint8_t function;
} In_controle;

typedef struct{
    uint8_t Reg_destino;
    uint8_t ULA_op;
    uint8_t MemtoReg;
    uint8_t RegWrite;
    uint8_t MemRead;
    uint8_t MemWrite;
    uint8_t Branch;
} Out_controle;

typedef struct{
    In_controle input;
    Out_controle output;
} Controle;

Out_controle controle_sinais(In_controle in);

#endif