#include <stddef.h>

#include "../core.h"
#include "../text_utils.h"
#include "../cusword.h"
#include "../cases.h"
#include "word_parser.h"

const char spar_type_word[] = "word";

static SPAR_PARSE_FUNC(parse_word)
{
        SPAR_BODY_CUSWORD(spar_type_word, SPAR_UNKNOWN_SIZE,
			  SPAR_SEP_CASES, SPAR_UNKNOWN_SIZE);
}

SPAR_PARSER_INIT(spar_word_parser, "parse_word", parse_word, NULL);
