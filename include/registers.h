#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

uint16_t *init_regs(void);
void print_regs(uint16_t *regs, int count);

#endif
