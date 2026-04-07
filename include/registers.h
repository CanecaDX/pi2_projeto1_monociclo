#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
typedef struct{
	uint8_t reg_base1;
	uint8_t reg_base2;
	uint8_t reg_destino;
	uint8_t write_reg;
	int8_t dado_escrever;
} In_registers;

typedef struct{
	int8_t val1;
	int8_t val2;
}Out_registers;

typedef struct {
	In_registers in_regs;
	Out_registers out_regs;
	uint8_t *registradores;
	int size;
} Banco_registradores;

Banco_registradores *registers_create(); 
Out_registers ex_registers(In_registers input, Banco_registradores *regs);
void print_regs(const Banco_registradores *regs);
void copiaBancoRegistradores(Banco_registradores* banco_backup, Banco_registradores* banco);


#endif
