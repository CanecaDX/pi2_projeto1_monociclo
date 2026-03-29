#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

typedef struct {
	int8_t reg_base1;
	int8_t reg_base2;
	int8_t reg_destino;
	int8_t dado_escrito;
}In_registradores;

typedef struct {
	int8_t reg_base1;
	int8_t reg_base2;
} Out_registradores;

typedef struct {
	In_registradores input;
	Out_registradores output;
	uint8_t *registradores;
	int count;
} Banco_registradores;

Banco_registradores *registers_create(int count);
void print_regs(const Banco_registradores *regs);

#endif
