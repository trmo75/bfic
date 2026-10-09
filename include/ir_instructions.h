/*
	Copyright (c) 2026 - Yann Pierre BOYER
	Standard MIT license terms apply.
*/
#ifndef BFIC_IR_INSTRUCTIONS_H
#define BFIC_IR_INSTRUCTIONS_H

#include <stdint.h>

typedef enum {
	INC_PTR = '>',
	DEC_PTR = '<',
	INC_BYTE = '+',
	DEC_BYTE = '-',
	PRN_BYTE  = '.',
	GET_BYTE = ',',
	JMP_ZE = '[',
	JMP_NZE = ']',
} IRInstKind;

typedef struct {
	IRInstKind i_kind;
	uint8_t i_operand; // Optional IR Instruction operand.
} IRInst;

#endif