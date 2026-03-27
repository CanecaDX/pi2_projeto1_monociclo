#include <stdio.h>
#include "decoder.h"

Decoded decode(uint16_t instruction){
    Decoded d;

    d.opcode = (instruction >> 12) & 0xF;    // 4 MSB
    //usa o index do enum para atribuir no tipo
    if (d.opcode == 0x0) {
        d.type = TYPE_R;
    } else if (d.opcode == 0x8 || d.opcode == 0x2) {
        d.type = TYPE_J;
    } else if (d.opcode == 0x4 || d.opcode == 0xB || d.opcode == 0xF) {
        d.type = TYPE_I;
    } else {
        printf("\nOpcode desconhecido: %x", d.opcode);
        printf("\nPulando instrução...");
        d.type = TYPE_R; // Default para evitar comportamento indefinido
    }
    //de acordo com o tipo atribui os valores no campo da struct
    if (d.type == TYPE_R) {
        d.rs     = (instruction >> 9) & 0x7;
        d.rt     = (instruction >> 6) & 0x7;
        d.rd     = (instruction >> 3) & 0x7;
        d.funct  = instruction & 0x7;
        d.imm = 0; 
        d.address = 0;
        printf("\nCampos: opcode: %x, rs: %x, rt: %x, rd: %x, funct: %x", d.opcode, d.rs, d.rt, d.rd, d.funct);
    } else if (d.type == TYPE_I) {
        d.rs     = (instruction >> 9) & 0x7;
        d.rt     = (instruction >> 6) & 0x7;
        d.rd     = 0;
        d.funct  = 0;
        d.address = 0;
        uint8_t imm6 = instruction & 0x3F;
        int8_t imm8;

        if (imm6 & 0x20) {
            imm8 = (int8_t)(imm6 | 0xC0);
        } else {
            imm8 = (int8_t)imm6;
        }
        d.imm = imm8;
        printf("\nCampos: opcode: %x, rs: %x, rt: %x, imm: %d", d.opcode, d.rs, d.rt, d.imm);
    } else if (d.type == TYPE_J) {
        d.rs = 0;
        d.rt = 0;
        d.rd = 0;
        d.funct = 0;
        d.imm = 0;
        d.address = instruction & 0x3F;  
        printf("\nCampos: opcode: %x, address: %x", d.opcode, d.address);
    }

    return d;
}
