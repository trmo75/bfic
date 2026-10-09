/*
	Copyright (c) 2026 - Yann Pierre BOYER
	Standard MIT license terms apply.
*/
#ifndef BFIC_IR_INTERPRETER_H
#define BFIC_IR_INTERPRETER_H

#include "ir_instructions.h"

#include <stdint.h>
#include <stddef.h>

#define INTERPRETER_TOTAL_MEM_CELLS_COUNT 100000

typedef struct {
	size_t inst_ptr;
	size_t mem_ptr;
	uint8_t mem_cells[INTERPRETER_TOTAL_MEM_CELLS_COUNT];
	const IRInst* ir_prg;
} IRInterpreter;

void bfic_irint_init(IRInterpreter* irint);
void bfic_irint_load_ir_code(IRInterpreter* irint, const IRInst* ir_prg);
int bfic_irint_execute_ir_code(IRInterpreter* irint);

#endif