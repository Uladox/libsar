/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 * #include "cases.h"
 * #include "text_utils.h"
 */

#define SAR_PARSE_NUM0(FUNC_NAME, WHOLE_TYPE, WHOLE_SIZE,		\
		       DECIMAL_TYPE, DECIMAL_SIZE, END_CASES,		\
		       VAL, VAL_TYPE, VAL_INIT, INC, DIF)		\
	SAR_PARSE_FUNC(FUNC_NAME)					\
	{								\
		int parsed = 1;						\
	        VAL_TYPE curr = VAL_INIT(info->dat);			\
		int period = 0;						\
									\
		(void) parser;						\
									\
		token->dat = curr;					\
		token->type = WHOLE_TYPE;				\
		token->data_size = WHOLE_SIZE;				\
									\
		switch (VAL(curr)) {					\
		SAR_DIGIT_CASES:					\
			break;						\
		default:						\
			info->error = "number does not start with "	\
				"digit";				\
			return 0;					\
		}							\
									\
		for (;; INC(curr)) {					\
			switch (VAL(curr)) {				\
			SAR_DIGIT_CASES:				\
				continue;				\
			END_CASES:					\
			case '\0':					\
				goto out;				\
			case '.':					\
				token->type = DECIMAL_TYPE;		\
				token->data_size = DECIMAL_SIZE;		\
									\
				if (!period) {				\
					period = 1;			\
					break;				\
				}					\
									\
				info->error = "too many decimal "	\
					"points in number";		\
				goto error;				\
			default:					\
				info->error = "invalid character"	\
					"in number";			\
			error:						\
									\
				if (info->error_leave)			\
					return 0;			\
									\
				parsed = 0;				\
				break;					\
			out:						\
				token->len = curr - SAR_TEXT(token->dat);	\
				return parsed;				\
			}						\
		}							\
	}								\
	SAR_PARSE_FUNC(FUNC_NAME)

#define SAR_PARSE_NUM(FUNC_NAME, WHOLE_TYPE, WHOLE_SIZE,		\
		      DECIMAL_TYPE, DECIMAL_SIZE, END_CASES)		\
	SAR_PARSE_NUM0(FUNC_NAME, WHOLE_TYPE, WHOLE_SIZE,		\
		       DECIMAL_TYPE, DECIMAL_SIZE, END_CASES,		\
		       *, char *, SAR_IDENT, ++, SAR_ADD_DIF)

