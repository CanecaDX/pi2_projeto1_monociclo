#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include "decoder.h"
#include "extensor.h"

Decoded decode(uint16_t instruction){
    Decoded decode_instruction;
    //printf("INSTRUÇÃO 0x%04X SENDO DECODIFICADA..", instruction);
    //retorna todos os campos preenchidos
    decode_instruction.opcode = (instruction >> 12) & 0xF;    
    decode_instruction.rs     = (instruction >> 9) & 0x7;
    decode_instruction.rt     = (instruction >> 6) & 0x7;
    decode_instruction.rd     = (instruction >> 3) & 0x7;
    decode_instruction.funct  = instruction & 0x7;
    decode_instruction.address = instruction & 0x3F;

    uint8_t imm6 = instruction & 0x3F;
    decode_instruction.imm = extend(imm6);

    if(decode_instruction.opcode == 0){
        decode_instruction.type = TYPE_R;
    } else if(decode_instruction.opcode == 0x8 || decode_instruction.opcode == 0x2){
        decode_instruction.type = TYPE_J;
    } else if(decode_instruction.opcode == 0x4 || decode_instruction.opcode == 0xB || decode_instruction.opcode == 0xF) {
        decode_instruction.type = TYPE_I;
    }

    return decode_instruction;
}
