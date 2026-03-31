#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "decoder.h"

Decoded decode(uint16_t instruction){
    Decoded decode_instruction;
    //retorna todos os campos preenchidos
    //no hardware os sinais estão sempre chegando, o que define o que se usa são os sinais no controle
    decode_instruction.opcode = (instruction >> 12) & 0xF;    // 4 MSB
    decode_instruction.type = 0;
    decode_instruction.rs     = (instruction >> 9) & 0x7;
    decode_instruction.rt     = (instruction >> 6) & 0x7;
    decode_instruction.rd     = (instruction >> 3) & 0x7;
    decode_instruction.funct  = instruction & 0x7;
    decode_instruction.address = instruction & 0x3F;
    {
        uint8_t imm6 = instruction & 0x3F;
        if (imm6 & 0x20) {
            decode_instruction.imm = (int8_t)(imm6 | 0xC0);
        } else {
            decode_instruction.imm = (int8_t)imm6;
        }
    }

    return decode_instruction;
}
