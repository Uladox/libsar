/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 * #include "text_utils.h"
 */

#define SAR_PARSE_STRLIT0(FUNC_NAME, TYPE, VAL, VAL_TYPE, VAL_INIT,	\
			  INC, DIF, LINE)				\
	SAR_PARSE_FUNC(FUNC_NAME)					\
	{								\
		int parsed = 1;						\
		int backslashed = 0;					\
		size_t line = 0;					\
	        VAL_TYPE curr;						\
									\
		VAL_INIT(curr, info->dat);				\
									\
		(void) parser;						\
									\
		token->data_size = 1;					\
		token->dat = info->dat;					\
		token->type = TYPE;					\
									\
		if (VAL(curr) != '\"') {					\
		        info->error = "string has no start quote";	\
									\
			if (info->error_leave || VAL(curr) == '\0')	\
				return 0;				\
									\
			parsed = 0;					\
		}							\
									\
		while (1) {						\
			INC(curr);					\
			switch (VAL(curr)) {				\
			case '\0':					\
				info->error = "string has no ending"	\
					"quote";			\
									\
				token->len = DIF(curr, token->dat);	\
			        LINE(info->cue, line);			\
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
				INC(curr);				\
									\
				token->len = DIF(curr, token->dat);	\
				LINE(info->cue, line);			\
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


#define SAR_PARSE_STRLIT(FUNC_NAME, TYPE)				\
	SAR_PARSE_STRLIT0(FUNC_NAME, TYPE, *, char *, SAR_EQUAL,	\
			  ++, SAR_ADD_DIF, SAR_ADD_LINES)

int
sar_strlit_str(Sar_token *token, char **str_ref);
