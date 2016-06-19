#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../word_parser.h"
#include "../token_print.h"

int main(int argc, char *argv[])
{
	struct spar_token token;
	enum spar_parsed parsed;

	char *buff = NULL;
	size_t size = 0;
	ssize_t len;

	printf("Enter your word here: ");

	/* len = getline(&buff, &size, stdin); */

	struct spar_lexinfo info = {
		.dat.text = "word",
		.error = NULL,
		.mem.stuff = NULL
	};

	parsed = spar_parse(&spar_word_parser, &info, &token);

	if (parsed == SPAR_ERROR) {
		printf("Error: %s.\n", info.error.text);
	} else {
		spar_print_text_token(&token);
		printf("\n");
	}

	free(buff);

	return 0;
}
