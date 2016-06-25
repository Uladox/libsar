#include <stdlib.h>

#include "../core.h"
#include "../text_utils.h"
#include "../cusstrlit.h"
#include "strlit_parser.h"

const char spar_type_strlit[] = "strlit";

static SPAR_PARSE_FUNC(parse_strlit)
{
	SPAR_BODY_CUSSTRLIT(spar_type_strlit, SPAR_UNKNOWN_SIZE);
}

SPAR_PARSER_INIT(spar_strlit_parser, "parse_strlit", parse_strlit, NULL);
