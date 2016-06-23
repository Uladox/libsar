#include <stdlib.h>

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

static inline char
backslash_curr(char curr)
{
	static const char vals[] = {
		['a'] = '\a',
		['b'] = '\b',
		['f'] = '\f',
		['n'] = '\n',
		['r'] = '\r',
		['t'] = '\t',
		['v'] = '\v',
		['\''] = '\''
	};

	return vals[(int) curr];

}

enum spar_parsed
spar_strlit_str(struct spar_token *token, char **str_ref)
{
	int backslashed = 0;
	const char *curr = token->dat.text;
	char *str = malloc(token->data_size);
	char *begin = str;

	while (1) {
		switch (*++curr) {
		case '\0':
			goto error;
		case '\\':
			if (backslashed) {
				*str = '\\';
				++str;
			}

		        backslashed = !backslashed;
			break;
		case '\"':
			if (backslashed) {
				backslashed = 0;
				*str = '\"';
				++str;
				break;
			}

			goto out;
		case 'a':
		case 'b':
		case 'f':
		case 'n':
		case 'r':
		case 't':
		case 'v':
		case '\'':
			*str = (backslashed) ? backslash_curr(*curr) : *curr;
			backslashed = 0;
			++str;
			break;
		default:
		        if (backslashed)
				goto error;

			*str = *curr;
			++str;
			break;
		}
	}
error:
	free(begin);
	*str_ref = NULL;
	return SPAR_ERROR;
out:
	*str = '\0';
	*str_ref = begin;
	return SPAR_OK;

}
