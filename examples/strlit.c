#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../text_utils.h"
#include "../token_print.h"
#include "../parsers/strlit_parser.h"

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

	printf("Enter your string here: ");

	len = getline(&buff, &size, stdin);

	Sar_lexi info = {
		.dat = buff,
		.cue = &text_cue,
		.error_leave = 1
	};

	parsed = sar_parse(&sar_strlit_parser, &info, &token);

	if (!parsed) {
		printf("Error: %s on line %zu.\n", info.error,
		       SAR_TEXT_CUE(info.cue)->lines);
	} else {
		sar_print_text_token(&token);
		printf("\n");
	}

	free(buff);

	return 0;
}
