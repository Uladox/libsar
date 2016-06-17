#include <stdlib.h>
#include <stdio.h>

#define SPAR_LEX_CUE_PTR_TYPES struct spar_text_cue *text;
#include "../core.h"
#include "../text_utils.h"
#include "../strlit_parser.h"
#include "../token_print.h"

int main(int argc, char *argv[])
{
	struct spar_token token;
	struct spar_text_cue text_cue;
	enum spar_parsed parsed;
	union spar_memory mem;

	char *buff = NULL;
	size_t size = 0;
	ssize_t len;

	printf("Enter your string here: ");

	len = getline(&buff, &size, stdin);

	struct spar_lexinfo info = {
		.dat.text = buff,
		.error = NULL,
		.cue.text = &text_cue
	};

	parsed = spar_parse(&spar_strlit_parser, &info, &token, mem);

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
