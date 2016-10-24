#include <stddef.h>

#include "../core.h"
#include "../text_utils.h"
#include "../word.h"
#include "../cases.h"
#include "word_parser.h"

const char sar_type_word[] = "word";

static SAR_PARSE_WORD(parse_word, sar_type_word,
		      SAR_UNKNOWN_SIZE, SAR_SEP_CASES);
/* static SAR_PARSE_FUNC(parse_word) */
/* { */
/*         SAR_BODY_CUSWORD(sar_type_word, SAR_UNKNOWN_SIZE, */
/* 			  SAR_SEP_CASES, SAR_UNKNOWN_SIZE); */
/* } */

SAR_PARSER_INIT(sar_word_parser, "parse_word", parse_word, NULL);
