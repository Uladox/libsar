#include <stddef.h>

#include "../core.h"
#include "../cases.h"
#include "../text_utils.h"
#include "../num.h"
#include "num_parser.h"

const char sar_type_whole[] = "whole";
const char sar_type_decimal[] = "decimal";

static
SAR_PARSE_NUM(parse_num, sar_type_whole, sizeof(unsigned int),
	      sar_type_decimal, sizeof(float),
	      SAR_SEP_CASES);

SAR_PARSER_INIT(sar_num_parser, "parse_num", parse_num, NULL);
