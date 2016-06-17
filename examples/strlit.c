#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../text_utils.h"
#include "../strlit_parser.h"
#include "../token_print.h"

int main(int argc, char *argv[])
{
	struct spar_token token;
	struct spar_text_cue text_cue;
	enum spar_parsed parsed;

	char *buff = NULL;
	size_t size = 0;
	ssize_t len;

	printf("Enter your string here: ");

	len = getline(&buff, &size, stdin);

	struct spar_lexinfo info = {
		.dat.text = buff,
		.error = NULL,
		.cue.text = &text_cue,
		.mem.stuff = NULL
	};

	parsed = spar_parse(&spar_strlit_parser, &info, &token);

	if (parsed == SPAR_ERROR) {
		printf("Error: %s on line %zu.\n", info.error.text,
		       info.cue.text->error_line);
	} else {
		spar_print_text_token(&token);
		printf("\n");
	}

	free(buff);

	return 0;
}
