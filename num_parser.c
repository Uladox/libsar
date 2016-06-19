#include <ctype.h>
#include <stddef.h>

#include "core.h"
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
	enum spar_parsed parsed;
	int period = 0;

	(void) parser;

	token->dat.text = info->dat.text;
	token->type = spar_type_whole;

	if (!isdigit(*info->dat.text)) {
		info->error.text = "number does not start with digit";
		info->cue.text->error_line = info->cue.text->lines;
		return SPAR_ERROR;
	}

	while (1) {
		switch (*++info->dat.text) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			continue;
		case '\n':
		case ' ':
		case '\t':
		case '\v':
		case '\f':
		case '\r':
		case ';':
			parsed = SPAR_OK;
			goto out;
		case '\0':
			parsed = SPAR_END;
			goto out;
		case '.':
			token->type = spar_type_decimal;
			if (!period) {
				period = 1;
				break;
			}
			info->error.text = "too many decimal points in number";
			info->cue.text->error_line = info->cue.text->lines;
			return SPAR_ERROR;
		default:
			info->error.text = "invalid character in number";
			info->cue.text->error_line = info->cue.text->lines;
			return SPAR_ERROR;
		}
	}
out:
	token->len = info->dat.text - token->dat.text;
	return parsed;
}
