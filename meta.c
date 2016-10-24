#include <stddef.h>

#include "core.h"

const char sar_type_parser[] = "parser";
const char sar_type_meta[] = "meta";

int
sar_meta_parse(Sar_parser *parser, Sar_lexi *info, Sar_token *token)
{
	int parsed = sar_parse(parser, info, token);

	if (parsed && token->type == sar_type_parser)
		return sar_parse(token->dat, info, token);

	return parsed;
}


int
sar_mod_meta_func(Sar_parser *parser, Sar_lexi *info,
		   Sar_token *token)
{
	int parsed = sar_parse(parser->dat, info, token);

	if (parsed && token->type == sar_type_parser)
		return sar_parse(token->dat, info, token);

	return parsed;
}

void
sar_mod_meta(Sar_parser *to_mod, Sar_parser *input)
{
	to_mod->dat = input;
	to_mod->str_rep = sar_type_meta;
	to_mod->parse = sar_mod_meta_func;
}
