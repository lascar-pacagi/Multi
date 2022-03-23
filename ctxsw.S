#include "ctxsw.h"	
	
/* 
void ctxsw(long* old_registers, long* new_registers)

Au début de cette procédure, la pile ressemble à :

+-----------------------------------------------------------------+
| @ retour (dans reschedule au début du code de enable_interrupt) | <-- %rsp
+-----------------------------------------------------------------+
| ...                                                             |
+-----------------------------------------------------------------+
*/

        .globl ctxsw
ctxsw:
	movq    %rax, RAX(%rdi)       # sauvegarde des registres
	movq    %rbx, RBX(%rdi)       
	movq    %rcx, RCX(%rdi)
	movq    %rdx, RDX(%rdi)
	movq    %rsi, RSI(%rdi)
	movq    %rdi, RDI(%rdi)
	movq    %rsp, RSP(%rdi)
	movq    %rbp, RBP(%rdi)
	movq    %r8,  R8(%rdi)
	movq    %r9,  R9(%rdi)
	movq    %r10, R10(%rdi)
	movq    %r11, R11(%rdi)
	movq    %r12, R12(%rdi)
	movq    %r13, R13(%rdi)
	movq    %r14, R14(%rdi)
	movq    %r15, R15(%rdi)

	movq    RAX(%rsi), %rax       # restauration des registres
	movq    RBX(%rsi), %rbx
	movq    RCX(%rsi), %rcx
	movq    RDX(%rsi), %rdx
	movq    RDI(%rsi), %rdi
	movq    RBP(%rsi), %rbp
	movq    RSP(%rsi), %rsp
	movq    R8(%rsi),  %r8
	movq    R9(%rsi),  %r9
	movq    R10(%rsi), %r10
	movq    R11(%rsi), %r11
	movq    R12(%rsi), %r12
	movq    R13(%rsi), %r13
	movq    R14(%rsi), %r14
	movq    R15(%rsi), %r15	
	movq    RSI(%rsi), %rsi

	ret
