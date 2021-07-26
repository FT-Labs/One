/**
 The One Programming Language

 File: lexer/main.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>
#include <stdlib.h>

#include "tokenizer/tokenizer.h"

#include "lexer.h"

int main(int argc, char** argv)
{
	char* input_file;
	char* output_file;
	Token** tokens;

	if (argc == 2)
	{
		// printf("Error: pass the arguments correctly!\n");
		// printf("./lexer input.one output.tokens\n");
		// return 1;

		tokens = tokenizer_string(argv[1]);
	}
	else if (argc == 3)
	{
		input_file = argv[1];
		output_file = argv[2];

		printf("Input file is: %s\n", input_file);
		printf("Output file is: %s\n", output_file);

		char* data = file_reads(input_file);
		tokens = tokenizer_string(data);

		FILE* file_out = fopen(output_file, "wa+"); // W: clear the file after open,
			 // a+: Append mode, so if we call `fprintf` some time we can append to the file!
		if (!file_out)
		{
			fprintf(stderr, "Error: it's unable to write output to %s file!\n", output_file);
			exit(1);
		}

		while (tokens != NULL && *tokens != NULL)
		{
			Token* t = *tokens;
			char* t_name = token_name(t->type);
			bool has1 = file_convert_index_to_rc(data, t->pos.index, &t->pos.line, &t->pos.column);
			bool has2 = file_convert_index_to_rc(data, t->pos_end.index, &t->pos_end.line, &t->pos_end.column);

			// printf("\n");
			// printf("%s\n", token_name(t->type));
			// printf("\tindex: %d, length: %d\n", t->pos_end.index, t->length);
			// printf("==>%d\n", has == true ? 1 : 0);
			// printf("\tline:col [%d:%d] - [%d:%d]\n", t->pos.line, t->pos.column, t->pos_end.line, t->pos_end.column);
			// printf("\n");

			fprintf(file_out, "[%d:%d] [%d:%d - %d:%d] %s", t->pos.tokens, t->length, t->pos.line, t->pos.column, t->pos_end.line, t->pos_end.column, t_name);

			if (t->value != NULL)
			{
				fprintf(file_out, ": \"%s\"", t->value);
			}
			fprintf(file_out, "\n");
			tokens++;
		}

		fclose(file_out);
	}
	else
	{
		printf("Error: arguments are not correct!\n");
		printf("./lexer input.one output.tokens\n");
		printf("./lexer \"your input here as string\"\n");
		return 1;
	}

	return 0;
}
