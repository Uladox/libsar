/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 * #include "text_utils.h"
 */

#define SAR_PARSE_STRLIT(FUNC_NAME, TYPE)				\
	SAR_PARSE_FUNC(FUNC_NAME)					\
	{								\
		int parsed = 1;						\
		int backslashed = 0;					\
		size_t line = 0;					\
		char *curr = info->dat;					\
									\
		(void) parser;						\
									\
		token->data_size = 1;					\
		token->dat = curr;					\
		token->type = TYPE;					\
									\
		if (*curr != '\"') {					\
			sar_text_error(info,				\
				       "string has no start quote", 0);	\
									\
			if (info->error_leave || *curr == '\0')		\
				return 0;				\
									\
			parsed = 0;					\
		}							\
									\
		while (1) {						\
			switch (*++curr) {				\
			case '\0':					\
				sar_text_error(info,			\
					       "string has no ending"	\
					       "quote",			\
					       line);			\
									\
				token->len = curr - SAR_TEXT(token->dat); \
				SAR_TEXT_CUE(info->cue)->lines += line;	\
				return 0;				\
			case '\\':					\
				if (backslashed)			\
					++token->data_size;		\
									\
				backslashed = !backslashed;		\
				break;					\
			case '\"':					\
				if (backslashed) {			\
					backslashed = 0;		\
					++token->data_size;		\
					break;				\
				}					\
									\
				++curr;					\
									\
				token->len = curr - SAR_TEXT(token->dat); \
				SAR_TEXT_CUE(info->cue)->lines += line;	\
				return parsed;				\
			case '\n':					\
				++line;					\
			default:					\
				backslashed = 0;			\
				++token->data_size;			\
				break;					\
			}						\
		}							\
	}								\
	SAR_PARSE_FUNC(FUNC_NAME)

int
sar_strlit_str(Sar_token *token, char **str_ref);
