/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 * #include "text_utils.h"
 */

#define SPAR_BODY_CUSWORD_0(TYPE, DAT_SIZE, END_CASES, FAIL_LEN)	\
        char *curr = info->dat.text;					\
									\
	(void) parser;							\
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
		return 0;						\
	}								\
									\
	while (1) {							\
		switch (*++curr) {					\
		END_CASES:						\
		case '\0':						\
			token->len = curr - token->dat.text;		\
			return 1;					\
		}							\
	}								\

#define SPAR_BODY_CUSWORD(TYPE, DAT_SIZE, END_CASES, FAIL_LEN)		\
	SPAR_INSULATE(SPAR_BODY_CUSWORD_0(TYPE, DAT_SIZE,		\
					  END_CASES, FAIL_LEN))

