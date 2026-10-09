/*
	Copyright (c) 2026 - Yann Pierre BOYER
	Standard MIT license terms apply.
*/
#ifndef BFIC_LEXER_H
#define BFIC_LEXER_H

#include <stddef.h>
#include <stdbool.h>

static const char VALID_INSTS[] = "><+-.,[]";

typedef struct {
	size_t code_pos;
	size_t code_len;
	char* code;
} Lexer;

void bfic_lexer_init(Lexer* lex);
void bfic_lexer_deinit(Lexer* lex);
void bfic_lexer_fill(Lexer* lex, const char* code);
bool bfic_lexer_is_valid_inst(const char inst_to_verify);
char bfic_lexer_next(Lexer* lex);

#endif