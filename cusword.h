/* Include these
 * #include <stddef.h>
 * #include "core.h"
 * #include "text_utils.h"
 */

#define SPAR_BODY_CUSWORD(TYPE, END_CASES, DAT_SIZE, FAIL_LEN)		\
        char *curr = info->dat.text;					\
									\
	token->dat.text = curr;						\
	token->type.generic = TYPE;					\
	token->data_size = DAT_SIZE;					\
									\
	switch (*curr) {						\
	END_CASES:							\
	case '\0':							\
		spar_text_error(info,					\
				"word has invalid first character", 0);	\
		token->len = FAIL_LEN;					\
		return SPAR_ERROR;					\
	}								\
									\
	while (1) {							\
		switch (*++curr) {					\
		END_CASES:						\
			token->len = curr - token->dat.text;		\
			return SPAR_OK;					\
		case '\0':						\
			token->len = curr - token->dat.text;		\
			return SPAR_END;				\
		}							\
	}								\
	(void) parser


