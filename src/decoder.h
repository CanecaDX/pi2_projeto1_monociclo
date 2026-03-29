#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include "instruction_mem.h"

//usa enum para determinar o tipo de instruções
//vai acessar os campos da struct baseado no index do enum

Decoded decode(uint16_t instruction);

#endif
