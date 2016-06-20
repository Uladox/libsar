#include <stddef.h>

#include "core.h"
#include "text_utils.h"
#include "strlit_parser.h"

static enum spar_parsed
parse_strlit(struct spar_parser *parser, struct spar_lexinfo *info,
	     struct spar_token *token);

const char spar_type_strlit[] = "strlit";

SPAR_PARSER_INIT(spar_strlit_parser, "parse_strlit", parse_strlit, NULL);

static enum spar_parsed
parse_strlit(struct spar_parser *parser, struct spar_lexinfo *info,
	     struct spar_token *token)
{
	enum spar_parsed parsed = SPAR_OK;
	int backslashed = 0;
	size_t line = 0;
	char *curr = info->dat.text;

	(void) parser;

	/* 1 is for null termination */
	token->data_size = 1;
	token->dat.text = curr;
	token->type = spar_type_strlit;

	if (*curr != '\"') {
		spar_text_error(info, "string has no start quote", 0);

		if (info->error_leave || *curr == '\0') {
			token->len = SPAR_UNKNOWN_SIZE;
			return SPAR_ERROR;
		}

		parsed = SPAR_ERROR;
	}

	while (1) {
		switch (*++curr) {
		case '\0':
			spar_text_error(info, "string has no ending quote",
					line);

			if (info->error_leave)
				return SPAR_ERROR;

			parsed = SPAR_ERROR;
			goto out;
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
	info->cue.text->lines += line;
	return parsed;
}
