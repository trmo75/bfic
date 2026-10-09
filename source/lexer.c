/*
	Copyright (c) 2026 - Yann Pierre BOYER
	Standard MIT license terms apply.
*/
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include "lexer.h"

#include <string.h>

void bfic_lexer_init(Lexer* lex) {
	lex->code_pos = 0;
	lex->code_len = 0;
	lex->code = NULL;
}

void bfic_lexer_deinit(Lexer* lex) {
	if (lex->code) arrfree(lex->code);
}

void bfic_lexer_fill(Lexer* lex, const char* code) {
	size_t len = strlen(code);
	for (size_t i = 0; i < len; i++) {
		arrpush(lex->code, code[i]);
	}
	lex->code_len = arrlen(lex->code);
}

bool bfic_lexer_is_valid_inst(const char inst_to_verify) {
	return strchr(VALID_INSTS, inst_to_verify) != NULL ? true : false;
}

char bfic_lexer_next(Lexer* lex) {
	while (lex->code_pos < lex->code_len && !bfic_lexer_is_valid_inst(lex->code[lex->code_pos]))
		lex->code_pos++;

	if (lex->code_pos >= lex->code_len) return 0;
	return lex->code[lex->code_pos++];
}