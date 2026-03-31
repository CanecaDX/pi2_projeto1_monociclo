#include "ULA.h"

Out_ULA ula_executa(In_ULA input){
	Out_ULA out = {0};
	int16_t res = 0;

	switch (input.ula_op) {
		case 0: res = (int16_t)input.op1 + (int16_t)input.op2; break;
		case 1: res = (int16_t)input.op1 - (int16_t)input.op2; break;
		case 2: res = (int16_t)(input.op1 & input.op2); break;
		case 3: res = (int16_t)(input.op1 | input.op2); break;
		case 4: res = (int16_t)(input.op1 ^ input.op2); break;
		case 5: res = (int16_t)(input.op1 < input.op2 ? 1 : 0); break;
		default: res = 0; break;
	}

	out.resultado = (int8_t)res;
	out.zero = (out.resultado == 0) ? 1 : 0;
	out.Overflow = (res < -128 || res > 127) ? 1 : 0;
	return out;
}
