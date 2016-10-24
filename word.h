/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 * #include "text_utils.h"
 */

#define SAR_PARSE_WORD(FUNC_NAME, TYPE, DAT_SIZE, END_CASES)		\
	SAR_PARSE_FUNC(FUNC_NAME)					\
	{								\
		char *curr = info->dat;					\
									\
		(void) parser;						\
									\
		token->dat = curr;					\
		token->type = TYPE;					\
		token->data_size = DAT_SIZE;				\
									\
		switch (*curr) {					\
		END_CASES:						\
		case '\0':						\
			sar_text_error(info,				\
				       "word has invalid "		\
				       "first character", 0);		\
			return 0;					\
		}							\
									\
		while (1) {						\
			switch (*++curr) {				\
			END_CASES:					\
			case '\0':					\
				token->len = curr - SAR_TEXT(token->dat);	\
				return 1;				\
			}						\
		}							\
	}								\
	SAR_PARSE_FUNC(FUNC_NAME)

