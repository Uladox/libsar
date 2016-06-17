#include <stddef.h>

#include "core.h"
#include "text_utils.h"
#include "strlit_parser.h"

static enum spar_parsed
parse_strlit(struct spar_parser *parser, struct spar_lexinfo *info,
	     struct spar_token *token);

const char spar_type_strlit[] = "strlit";

struct spar_parser spar_strlit_parser = {
	.type = SPAR_PRIMATIVE,
	.to_free = SPAR_DONT_FREE,
	.parse = parse_strlit,
	.str_rep = "parse_strlit"
};


static enum spar_parsed
parse_strlit(struct spar_parser *parser, struct spar_lexinfo *info,
	     struct spar_token *token)
{
	int backslashed = 0;
	size_t line = 0;
	char *curr = info->dat.text;

	(void) parser;

	/* 1 is for null termination */
	token->data_size = 1;
	token->dat.text = curr;
	token->type = spar_type_strlit;

	if (*curr != '\"') {
		info->error.text = "string has no start quote";
		info->cue.text->error_line = info->cue.text->lines;
		return SPAR_ERROR;
	}

	while (1) {
		switch (*++curr) {
		case '\0':
			info->error.text = "string has no ending quote";
			info->cue.text->error_line = info->cue.text->lines + line;
			return SPAR_ERROR;
		case '\\':
			if (backslashed)
				++token->data_size;
		        backslashed = !backslashed;
			break;
		case '\"':
			if (backslashed) {
				backslashed = 0;
				++token->data_size;
				break;
			}

			++curr;
			goto out;
		case '\n':
			++line;
		default:
			backslashed = 0;
			++token->data_size;
			break;
		}
	}
out:
	token->len = curr - token->dat.text;
	info->dat.text = curr;
	info->cue.text->lines += line;
	return SPAR_OK;
}
