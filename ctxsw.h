#ifndef CTXSW_H
#define CTXSW_H

#define RAX    0
#define RBX    8
#define RCX    16
#define RDX    24
#define RBP    32
#define RSI    40
#define RDI    48
#define RSP    56
#define R8     64
#define R9     72
#define R10    80
#define R11    88
#define R12    96
#define R13    104
#define R14    112
#define R15    120

#define REGISTER_TO_INDEX(R) (R/8)

#ifndef ASM
void ctxsw(long* old_registers, long* new_registers);
#endif

#endif
