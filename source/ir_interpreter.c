/*
	Copyright (c) 2026 - Yann Pierre BOYER
	Standard MIT license terms apply.
*/
#include "ir_interpreter.h"
#include "stb_ds.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bfic_irint_init(IRInterpreter* irint) {
	irint->inst_ptr = 0;
	irint->mem_ptr = 0;
	memset(irint->mem_cells, 0, sizeof(irint->mem_cells));
	irint->ir_prg = NULL;
}

void bfic_irint_load_ir_code(IRInterpreter* irint, const IRInst* ir_prg) {
	irint->ir_prg = ir_prg;
}

int bfic_irint_execute_ir_code(IRInterpreter* irint) {
	size_t* jmp_stack = NULL;
	size_t* jmp_targets = NULL;
	size_t ir_prg_len = arrlen(irint->ir_prg);
	arrsetlen(jmp_targets, ir_prg_len);
	memset(jmp_targets, 0, sizeof(size_t) * ir_prg_len);

	// Precomputing jumps.
	for (size_t i = 0, j; i < ir_prg_len; i++) {
		if (irint->ir_prg[i].i_kind == JMP_ZE) arrpush(jmp_stack, i);
		else if (irint->ir_prg[i].i_kind == JMP_NZE) {
			if (arrlen(jmp_stack) == 0) {
				fprintf(stderr, "[FATAL ERROR] Unbalanced loop: missing '['!\n");
				arrfree(jmp_stack);
				arrfree(jmp_targets);
				return -1;
			} else {
				j = arrpop(jmp_stack);
				jmp_targets[i] = j;
				jmp_targets[j] = i;
			}
		}
	}

	if (arrlen(jmp_stack) > 0) {
		fprintf(stderr, "[FATAL ERROR] Unbalanced loop: missing ']'!\n");
		arrfree(jmp_stack);
		arrfree(jmp_targets);
		return -1;
	}

	arrfree(jmp_stack);

	// Executing IR code.
	while (irint->inst_ptr < ir_prg_len) {
		IRInst ir_inst = irint->ir_prg[irint->inst_ptr];

		switch (ir_inst.i_kind) {
			case INC_PTR: irint->mem_ptr += ir_inst.i_operand; break;
			case DEC_PTR: irint->mem_ptr -= ir_inst.i_operand; break;
			case INC_BYTE: irint->mem_cells[irint->mem_ptr] += ir_inst.i_operand; break;
			case DEC_BYTE: irint->mem_cells[irint->mem_ptr] -= ir_inst.i_operand; break;
			case PRN_BYTE:
				fprintf(stdout, "%c", (char)irint->mem_cells[irint->mem_ptr]);
				fflush(stdout);
				break;
			case GET_BYTE:
				fprintf(stderr, "[FATAL ERROR] Unimplemented instruction because fuck you!\n");
				arrfree(jmp_targets);
				return -1;
				break;
			case JMP_ZE:
				if (irint->mem_cells[irint->mem_ptr] == 0)
					irint->inst_ptr = jmp_targets[irint->inst_ptr];
				break;
			case JMP_NZE:
				if (irint->mem_cells[irint->mem_ptr] != 0)
					irint->inst_ptr = jmp_targets[irint->inst_ptr];
				break;
		}

		irint->inst_ptr++;
	}

	arrfree(jmp_targets);

	return 0;
}