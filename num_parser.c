#include <ctype.h>
#include <stddef.h>

#include "core.h"
#include "cases.h"
#include "text_utils.h"
#include "num_parser.h"

static enum spar_parsed
parse_num(struct spar_parser *parser, struct spar_lexinfo *info,
	  struct spar_token *token);

const char spar_type_whole[] = "whole";
const char spar_type_decimal[] = "decimal";

SPAR_PARSER_INIT(spar_num_parser, "parse_num", parse_num, NULL);

static enum spar_parsed
parse_num(struct spar_parser *parser, struct spar_lexinfo *info,
	  struct spar_token *token)
{
	enum spar_parsed parsed = SPAR_OK;
	char *curr = info->dat.text;
	int period = 0;

	(void) parser;

	token->dat.text = curr;
	token->type = spar_type_whole;

	if (!isdigit(*curr)) {
		info->error.text = "number does not start with digit";
		info->cue.text->error_line = info->cue.text->lines;
		token->len = SPAR_UNKNOWN_SIZE;
		return SPAR_ERROR;
	}

	for (;; ++curr) {
		switch (*curr) {
		SPAR_DIGIT_CASES:
			continue;
		SPAR_SEP_CASES:
			goto out;
		case '\0':
			if (parsed == SPAR_OK)
				parsed = SPAR_END;
			goto out;
		case '.':
			token->type = spar_type_decimal;
			if (!period) {
				period = 1;
				break;
			}
			info->error.text = "too many decimal points in number";
		        goto error;
		default:
			info->error.text = "invalid character in number";
		error:
			info->cue.text->error_line = info->cue.text->lines;
			if (info->error_leave)
				return SPAR_ERROR;
			parsed = SPAR_ERROR;
			break;
		}
	}
out:
	token->len = curr - token->dat.text;
	return parsed;
}
