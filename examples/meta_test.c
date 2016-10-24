#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../meta.h"
#include "../text_utils.h"
#include "../token_print.h"
#include "../parsers/strlit_parser.h"
#include "../parsers/word_parser.h"

int
str_word_parse(Sar_parser *parser, Sar_lexi *info,
	       Sar_token *token)
{
	token->type = sar_type_parser;

	token->dat = (*SAR_TEXT(info->dat) == '\"')
		? &sar_strlit_parser : &sar_word_parser;

	return 1;
}


SAR_PARSER_INIT(word_str_basic, "word_str_basic", str_word_parse, NULL);

SAR_MOD_INIT_META(word_str_parser, &word_str_basic);

int main(int argc, char *argv[])
{
	Sar_token token;
        Sar_text_cue text_cue = {
		.lines = 0
	};
	int parsed;

	Sar_lexi info = {
		.error = NULL,
		.cue = &text_cue,
		.error_leave = 1,
	};

	char *buff = NULL;
	size_t size = 0;

	printf("Enter your string or word here: ");
        getline(&buff, &size, stdin);

	info.dat = buff;
	parsed = sar_parse(&word_str_parser, &info, &token);

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
