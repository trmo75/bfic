/*
	Copyright (c) 2026 - Yann Pierre BOYER
	Standard MIT license terms apply.
*/
#ifndef BFIC_IR_GENERATOR_H
#define BFIC_IR_GENERATOR_H

#include "ir_instructions.h"
#include "lexer.h"

typedef struct {
	Lexer lexer;
} IRGenerator;

void p_bfic_irgen_lazy_inst_combine_optimization(IRGenerator* irgen, char* inst, IRInst* ir_inst);
void bfic_irgen_init(IRGenerator* irgen);
IRInst* bfic_irgen_generate_ir_from_code(IRGenerator* irgen, const char* code);

#endif