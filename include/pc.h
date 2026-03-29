#ifndef PC_H
#define PC_H

#include <stdint.h>

typedef struct {
    uint16_t adress;
} ProgramCounter;

ProgramCounter *pc_create(void);
void pc_set(ProgramCounter *pc, uint16_t adress);
void pc_step(ProgramCounter *pc);

#endif
