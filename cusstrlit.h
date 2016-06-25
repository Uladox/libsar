/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 * #include "text_utils.h"
 */

#define SPAR_BODY_CUSSTRLIT_0(TYPE, FAIL_LEN)				\
	enum spar_parsed parsed = SPAR_OK;				\
	int backslashed = 0;						\
	size_t line = 0;						\
	char *curr = info->dat.text;					\
									\
	(void) parser;							\
									\
	token->data_size = 1;						\
	token->dat.text = curr;						\
	token->type.generic = TYPE;					\
									\
	if (*curr != '\"') {						\
		spar_text_error(info, "string has no start quote", 0);	\
									\
		if (info->error_leave || *curr == '\0') {		\
			token->len = FAIL_LEN;				\
			return SPAR_ERROR;				\
		}							\
									\
		parsed = SPAR_ERROR;					\
	}								\
									\
	while (1) {							\
		switch (*++curr) {					\
		case '\0':						\
			spar_text_error(info,				\
					"string has no ending quote",	\
					line);				\
									\
			token->len = curr - token->dat.text;		\
			info->cue.text->lines += line;			\
			return SPAR_ERROR;				\
		case '\\':						\
			if (backslashed)				\
				++token->data_size;			\
									\
		        backslashed = !backslashed;			\
			break;						\
		case '\"':						\
			if (backslashed) {				\
				backslashed = 0;			\
				++token->data_size;			\
				break;					\
			}						\
									\
			++curr;						\
									\
			token->len = curr - token->dat.text;		\
			info->cue.text->lines += line;			\
			return parsed;					\
		case '\n':						\
			++line;						\
		default:						\
			backslashed = 0;				\
			++token->data_size;				\
			break;						\
		}							\
	}								\

#define SPAR_BODY_CUSSTRLIT(TYPE, FAIL_LEN)			\
	SPAR_INSULATE(SPAR_BODY_CUSSTRLIT_0(TYPE, FAIL_LEN))

enum spar_parsed
spar_strlit_str(struct spar_token *token, char **str_ref);
