#include <stddef.h>
#include "core.h"
#include "comb.h"

const char sar_type_first[] = "first";
const char sar_type_all[] = "all";

void
sar_comb_add(Sar_parser *comb, Sar_batch *batch)
{
	Sar_batch *old_batch = comb->dat;

	SAR_BATCH(comb->dat = batch)->next = old_batch;
}

int
sar_prim_comb_first(Sar_parser *parser, Sar_lexi *info, Sar_token *token)
{
	Sar_batch *batch = parser->dat;
	Sar_parser **parsers = batch->val.parsers;

	for (; *parsers; ++parsers)
		if (sar_parse(*parsers, info, token))
				return 1;

	return 0;
}

void
sar_comb_first(Sar_parser *comb)
{
	comb->parse = sar_comb_first_func;
	comb->str_rep = sar_type_first;
}

int
sar_prim_comb_all(Sar_parser *parser, Sar_lexi *info, Sar_token *token)
{
	int parsed = 0;
	Sar_batch *batch = parser->dat;
	Sar_parser **parsers = batch->val.parsers;

	for (parsers = batch->parsers; *parsers; ++parsers)
			if (sar_parse(*parsers, info, token))
				parsed = 1;

	return parsed;
}

void
sar_comb_all(Sar_parser *comb)
{
	comb->parse = sar_comb_all_func;
	comb->str_rep = sar_type_all;
}
