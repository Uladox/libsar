#include <stddef.h>

#include "../core.h"
#include "../cases.h"
#include "../text_utils.h"
#include "../cusnum.h"
#include "num_parser.h"

const char spar_type_whole[] = "whole";
const char spar_type_decimal[] = "decimal";

static SPAR_PARSE_FUNC(parse_num) {
	SPAR_BODY_CUSNUM(spar_type_whole, sizeof(unsigned int),
			 spar_type_decimal, sizeof(float),
			 SPAR_SEP_CASES, SPAR_UNKNOWN_SIZE);
}

SPAR_PARSER_INIT(spar_num_parser, "parse_num", parse_num, NULL);
