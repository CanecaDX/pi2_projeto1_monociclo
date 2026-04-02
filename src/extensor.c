#include "extensor.h"

int8_t extend(uint8_t imm6) {
    if (imm6 & 0x20) {          
        return (int8_t)(imm6 | 0xC0); 
    }else {
        return (int8_t)(imm6 & 0x3F);
    }
}