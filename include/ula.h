#ifndef ULA_H
#define ULA_H

#include <stdint.h>

typedef struct {
    int8_t op1;
    int8_t op2;
    uint8_t ula_op;
}In_ULA;

typedef struct {
    int8_t resultado;
    int8_t Overflow;
    int8_t zero;
}Out_ULA;

typedef struct {
    In_ULA input;
    Out_ULA output;
} ULA;

Out_ULA ulaExecuta(In_ULA *p);
#endif // ULA_H
