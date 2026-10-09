/*
	Copyright (c) 2026 - Yann Pierre BOYER
	Standard MIT license terms apply.
*/
#include "ir_generator.h"
#include "ir_interpreter.h"
#include "ir_instructions.h"
#include "stb_ds.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "[FATAL ERROR] No BF program provided!\n");
		fprintf(stdout, "[INFO] Usage: ./bfic program.bf\n");
		return EXIT_FAILURE;
	}

	const char* prg_file_path = argv[1];

	FILE* prg_file = fopen(prg_file_path, "rb");
	if (!prg_file) {
		fprintf(stderr, "[FATAL ERROR] Unable to open the file!\n");
		return EXIT_FAILURE;
	}

	fseek(prg_file, 0, SEEK_END);
	size_t prg_buf_len = ftell(prg_file);
	rewind(prg_file);

	char* prg_buf = (char*)malloc(sizeof(char) * (prg_buf_len + 1));
	if (!prg_buf) {
		fprintf(stderr, "[FATAL ERROR] Mem Alloc Failed!\n");
		fclose(prg_file);
		return EXIT_FAILURE;
	}

	size_t bytes_read = fread(prg_buf, 1, prg_buf_len, prg_file);
	fclose(prg_file);
	if (bytes_read != prg_buf_len) {
		fprintf(stderr, "[FATAL ERROR] Unable to read the full file correctly!\n");
		free(prg_buf);
		return EXIT_FAILURE;
	}
	prg_buf[prg_buf_len] = '\0';

	IRGenerator irgen;
	bfic_irgen_init(&irgen);
	IRInst* ir_prg = bfic_irgen_generate_ir_from_code(&irgen, prg_buf);
	free(prg_buf);
	if (!ir_prg) return EXIT_FAILURE;

	IRInterpreter irint;
	bfic_irint_init(&irint);
	bfic_irint_load_ir_code(&irint, ir_prg);
	if (bfic_irint_execute_ir_code(&irint) < 0) {
		arrfree(ir_prg);
		return EXIT_FAILURE;
	}
	arrfree(ir_prg);
	return EXIT_SUCCESS;
}
