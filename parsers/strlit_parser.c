#include <stdlib.h>

#include "../core.h"
#include "../text_utils.h"
#include "../strlit.h"
#include "strlit_parser.h"

const char sar_type_strlit[] = "strlit";

static
SAR_PARSE_STRLIT(parse_strlit, sar_type_strlit);

SAR_PARSER_INIT(sar_strlit_parser, "parse_strlit", parse_strlit, NULL);
