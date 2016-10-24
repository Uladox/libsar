/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 * #include "text_utils.h"
 */

#define SAR_PARSE_WORD0(FUNC_NAME, TYPE, DAT_SIZE, END_CASES, VAL, INC, DIF) \
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
		switch (VAL(curr)) {					\
		END_CASES:						\
		case '\0':						\
		        info->error = "word has invalid"			\
				" first character";			\
			return 0;					\
		}							\
									\
		while (1) {						\
			switch (VAL(INC(curr))) {			\
			END_CASES:					\
			case '\0':					\
				token->len = DIF(curr, token->dat);	\
				return 1;				\
			}						\
		}							\
	}								\
	SAR_PARSE_FUNC(FUNC_NAME)



#define SAR_PARSE_WORD(FUNC_NAME, TYPE, DAT_SIZE, END_CASES)		\
	SAR_PARSE_WORD0(FUNC_NAME, TYPE, DAT_SIZE, END_CASES,		\
			*, ++, SAR_ADD_DIF)
