#include <ctype.h>
#include <stddef.h>

#include "core.h"
#include "text_utils.h"
#include "word_parser.h"

static enum spar_parsed
parse_word(struct spar_parser *parser, struct spar_lexinfo *info,
	   struct spar_token *token);

const char spar_type_word[] = "word";

struct spar_parser spar_word_parser = {
	.type = SPAR_PRIMATIVE,
	.to_free = SPAR_DONT_FREE,
	.parse = parse_word,
	.str_rep = "parse_word"
};


static enum spar_parsed
parse_word(struct spar_parser *parser, struct spar_lexinfo *info,
	   struct spar_token *token)
{
	enum spar_parsed parsed;

	(void) parser;

	token->dat.text = info->dat.text;
	token->data_size = SPAR_UNKNOWN_SIZE;
	token->type = spar_type_word;

	if (isspace(*info->dat.text) || *info->dat.text == '\0' ||
	    *info->dat.text == ';') {
		info->error.text = "word does not start with valid character";
		info->cue.text->error_line = info->cue.text->lines;
		return SPAR_ERROR;
	}

	while (1) {
		switch (*++info->dat.text) {
		case '\n':
		case ' ':
		case '\t':
		case '\v':
		case '\f':
		case '\r':
		case ';':
			parsed = SPAR_OK;
			goto out;
		case '\0':
			parsed = SPAR_END;
			goto out;
		}
	}
out:
	token->len = info->dat.text - token->dat.text;
	return parsed;
}
