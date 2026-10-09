/*
	Copyright (c) 2026 - Yann Pierre BOYER
	Standard MIT license terms apply.
*/
#include "ir_generator.h"
#include "stb_ds.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void p_bfic_irgen_lazy_inst_combine_optimization(IRGenerator* irgen, char* inst, IRInst* ir_inst) {
	uint8_t inst_redundancy_counter = 1;
	char next_inst = bfic_lexer_next(&irgen->lexer);

	while (*inst == next_inst) {
		inst_redundancy_counter++;
		next_inst = bfic_lexer_next(&irgen->lexer);
	}

	*ir_inst = (IRInst) { (IRInstKind)*inst, inst_redundancy_counter };
	*inst = next_inst;
}

void bfic_irgen_init(IRGenerator* irgen) {
	bfic_lexer_init(&irgen->lexer);
}

IRInst* bfic_irgen_generate_ir_from_code(IRGenerator* irgen, const char* code) {
	bfic_lexer_fill(&irgen->lexer, code);

	IRInst* tmp_ir_prg = NULL;
	char inst = bfic_lexer_next(&irgen->lexer);	

	while (inst) {
		IRInst ir_inst;
		switch (inst) {
			case '>':
			case '<':
			case '+':
			case '-':
				p_bfic_irgen_lazy_inst_combine_optimization(irgen, &inst, &ir_inst);
				break;
			case '.':
			case ',':
			case '[':
			case ']':
				ir_inst = (IRInst) { (IRInstKind)inst, 0 };
				inst = bfic_lexer_next(&irgen->lexer);
				break;
		}

		arrpush(tmp_ir_prg, ir_inst);
	}

	bfic_lexer_deinit(&irgen->lexer);

	if (arrlen(tmp_ir_prg) == 0) {
		fprintf(stderr, "[FATAL ERROR] Invalid/Empty BF program!\n");
		return NULL;
	}

	return tmp_ir_prg;
}