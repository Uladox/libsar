#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../comb.h"
#include "../text_utils.h"
#include "../token_print.h"
#include "../parsers/word_parser.h"
#include "../parsers/strlit_parser.h"


Sar_batch word_str_batch = {
	.next = NULL,
	.parsers = (Sar_parser *[]) {
		&sar_strlit_parser,
		&sar_word_parser,
		NULL
	}
};

SAR_COMB_INIT_FIRST(word_str_parser, &word_str_batch);

int main(int argc, char *argv[])
{
	Sar_token token;
	Sar_text_cue text_cue = {
		.lines = 0
	};
	int parsed;

	char *buff = NULL;
	size_t size = 0;
	ssize_t len;

	printf("Enter your string or word here: ");

	len = getline(&buff, &size, stdin);

	Sar_lexi info = {
		.dat = buff,
		.cue = &text_cue,
		.error_leave = 1,
	};

	parsed = sar_parse(&word_str_parser,
			    &info, &token);

	if (!parsed) {
		printf("Error: neither a word or a string.\n");
	} else {
		printf("parsed \n\t");
		sar_print_text_token(&token);
		printf("\nwith type %s.\n", token.type);
	}

	free(buff);

	return 0;
}
