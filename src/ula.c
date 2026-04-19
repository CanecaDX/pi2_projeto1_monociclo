#include "ULA.h"

Out_ULA ulaExecuta(In_ULA *p){
	
	Out_ULA out;
	
	//variavel para lidar com overflow
	int16_t res = 0;
	
	switch(p->ula_op){
		case 0x0: //soma
			res = (int16_t)p->op1 + (int16_t)p->op2;
			break;
		case 0x2: //subtracao
            res = (int16_t)p->op1 - (int16_t)p->op2; 
            break;
        case 0x4: //AND
            res = (int16_t)(p->op1 & p->op2); 
            break;
        case 0x5: //OR
            res = (int16_t)(p->op1 | p->op2); 
            break;
	}		

	out.Overflow = (res < -128 || res > 127) ? 1 : 0;
	out.resultado = (int8_t)res;
	out.zero = (out.resultado == 0) ? 1 : 0;
	
	if(out.Overflow){
		if(res < -128)
			out.resultado = -128;
		if(res > 127)
			out.resultado = 127;
	}
	
	
    
    return out;
}
