#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../comb.h"
#include "../text_utils.h"
#include "../token_print.h"
#include "../parsers/word_parser.h"
#include "../parsers/strlit_parser.h"


struct spar_parser_batch word_str_batch = {
	.next = NULL,
	.parsers = (struct spar_parser *[]) {
		&spar_strlit_parser,
		&spar_word_parser,
		NULL
	}
};

SPAR_COMB_INIT_FIRST(word_str_parser, &word_str_batch);

int main(int argc, char *argv[])
{
	struct spar_token token;
	struct spar_text_cue text_cue = {
		.lines = 0
	};
	int parsed;

	char *buff = NULL;
	size_t size = 0;
	ssize_t len;

	printf("Enter your string or word here: ");

	len = getline(&buff, &size, stdin);

	struct spar_lexinfo info = {
		.dat.text = buff,
		.cue.text = &text_cue,
		.error_leave = 1,
	};

	parsed = spar_parse(&word_str_parser,
			    &info, &token);

	if (!parsed) {
		printf("Error: neither a word or a string.\n");
	} else {
		printf("parsed \n\t");
		spar_print_text_token(&token);
		printf("\nwith type %s.\n", token.type);
	}

	free(buff);

	return 0;
}
