#include <ctype.h>
#include <stddef.h>

#include "core.h"
#include "cases.h"
#include "text_utils.h"
#include "word_parser.h"

static enum spar_parsed
parse_word(struct spar_parser *parser, struct spar_lexinfo *info,
	   struct spar_token *token);

const char spar_type_word[] = "word";

SPAR_PARSER_INIT(spar_word_parser, "parse_word", parse_word, NULL);

static enum spar_parsed
parse_word(struct spar_parser *parser, struct spar_lexinfo *info,
	   struct spar_token *token)
{
	enum spar_parsed parsed;
        char *curr = info->dat.text;

	(void) parser;

	token->dat.text = curr;
	token->type = spar_type_word;

	if (isspace(*curr) || *curr == '\0' || *curr == ';') {
		spar_text_error(info, "word has invalid first character", 0);
		token->len = SPAR_UNKNOWN_SIZE;
		return SPAR_ERROR;
	}

	while (1) {
		switch (*++curr) {
		SPAR_SEP_CASES:
			parsed = SPAR_OK;
			goto out;
		case '\0':
			parsed = SPAR_END;
			goto out;
		}
	}
out:
	token->len = curr - token->dat.text;
	return parsed;
}
