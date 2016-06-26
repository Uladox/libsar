#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../meta.h"
#include "../text_utils.h"
#include "../token_print.h"
#include "../parsers/strlit_parser.h"
#include "../parsers/word_parser.h"

int
str_word_parse(struct spar_parser *parser, struct spar_lexinfo *info,
	       struct spar_token *token)
{
	token->type.text = spar_type_parser;

	token->dat.parser = (*info->dat.text == '\"')
		? &spar_strlit_parser : &spar_word_parser;

	return 1;
}


SPAR_PARSER_INIT(word_str_basic, "word_str_basic", str_word_parse, NULL);

SPAR_MOD_INIT_META(word_str_parser, &word_str_basic);

int main(int argc, char *argv[])
{
	struct spar_token token;
	struct spar_text_cue text_cue = {
		.lines = 0
	};
	int parsed;

	struct spar_lexinfo info = {
		.error = NULL,
		.cue.text = &text_cue,
		.error_leave = 1,
	};

	char *buff = NULL;
	size_t size = 0;

	printf("Enter your string or word here: ");
        getline(&buff, &size, stdin);

	info.dat.text = buff;
	parsed = spar_parse(&word_str_parser, &info, &token);

	if (!parsed) {
		printf("Error: neither a word or a string.\n");
	} else {
		printf("parsed \n\t");
		spar_print_text_token(&token);
		printf("\nwith type %s.\n", token.type.text);
	}

	free(buff);

	return 0;
}
