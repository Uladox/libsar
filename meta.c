#include <stddef.h>

#include "core.h"

const char spar_type_parser[] = "parser";
const char spar_type_meta[] = "meta";

int
spar_meta_parse(struct spar_parser *parser, struct spar_lexinfo *info,
		struct spar_token *token)
{
	int parsed = spar_parse(parser, info, token);

	if (parsed && token->type.text == spar_type_parser)
		return spar_parse(token->dat.parser, info, token);

	return parsed;
}


int
spar_mod_meta_func(struct spar_parser *parser, struct spar_lexinfo *info,
		   struct spar_token *token)
{
	int parsed = spar_parse(parser->dat.parser, info, token);

	if (parsed && token->type.text == spar_type_parser)
		return spar_parse(token->dat.parser, info, token);

	return parsed;
}

void
spar_mod_meta(struct spar_parser *to_mod, struct spar_parser *input)
{
	to_mod->dat.parser = input;
	to_mod->str_rep = spar_type_meta;
	to_mod->parse = spar_mod_meta_func;
}
