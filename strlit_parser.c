#include <stdlib.h>

#include "core.h"
#include "text_utils.h"
#include "cusstrlit.h"
#include "strlit_parser.h"

const char spar_type_strlit[] = "strlit";

static SPAR_PARSE_FUNC(parse_strlit)
{
	SPAR_BODY_CUSSTRLIT(spar_type_strlit, SPAR_UNKNOWN_SIZE);
}

SPAR_PARSER_INIT(spar_strlit_parser, "parse_strlit", parse_strlit, NULL);

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
