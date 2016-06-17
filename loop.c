#include <stddef.h>

#include "core.h"

const char spar_type_loop[] = "loop";

enum spar_parsed
spar_loop_parse(struct spar_parser *parser, struct spar_lexinfo *info,
		struct spar_token *token)
{
	enum spar_parsed parsed;

	do {
		parsed = spar_parse(parser, info, token);
	} while (parsed == SPAR_OK);

	return parsed;
}


enum spar_parsed
spar_mod_loop_func(struct spar_parser *parser, struct spar_lexinfo *info,
		   struct spar_token *token)
{
	enum spar_parsed parsed;

	while ((parsed = spar_parse(parser->dat.loop.parser,
				    info, token)) == SPAR_OK) {
		switch (spar_parse(parser->dat.loop.check, info, token)) {
		case SPAR_OK:
			continue;
		case SPAR_END:
			return SPAR_OK;
		case SPAR_ERROR:
			return SPAR_ERROR;
		}
	}

	return parsed;
}

void
spar_mod_loop(struct spar_parser *to_mod, struct spar_loop *input)
{
	to_mod->dat.loop = input;
	to_mod->str_rep = spar_type_loop;
	to_mod->parse = spar_mod_loop_func;
}
