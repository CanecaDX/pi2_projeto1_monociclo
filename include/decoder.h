#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include "instruction_mem.h"
//por enquanto usar a struct, depois "emburrecer o fluxo no monociclo"
Decoded decode(uint16_t instruction);

#endif
