#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../text_utils.h"
#include "../token_print.h"
#include "../parsers/word_parser.h"

int main(int argc, char *argv[])
{
	Sar_token token;
	int parsed;
        Sar_text_cue text_cue = {
		.lines = 0
	};

	char *buff = NULL;
	size_t size = 0;
	ssize_t len;

	printf("Enter your word here: ");

	len = getline(&buff, &size, stdin);

	Sar_lexi info = {
		.dat = buff,
		.cue = &text_cue,
		.error_leave = 1
	};

	parsed = sar_parse(&sar_word_parser, &info, &token);

	if (!parsed) {
		printf("Error: %s.\n", info.error);
	} else {
		sar_print_text_token(&token);
		printf("\n");
	}

	free(buff);

	return 0;
}
