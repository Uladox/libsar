#include <stdlib.h>
#include "core.h"

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

int
sar_strlit_str(Sar_token *token, char **str_ref)
{
	int backslashed = 0;
	const char *curr = token->dat;
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
	return 0;
out:
	*str = '\0';
	*str_ref = begin;
	return 1;

}
