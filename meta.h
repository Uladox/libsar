/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 */

#define SPAR_MOD_INIT_META(NAME, DAT)			\
	struct spar_parser NAME = {			\
		.dat.parser = DAT,			\
		.type = SPAR_MODDED,			\
		.parse = spar_mod_meta_func,		\
		.str_rep = spar_type_meta,		\
		.to_free = SPAR_DONT_FREE		\
	}

extern const char spar_type_parser[];
extern const char spar_type_meta[];

/* For a parser that spits out a parser to parse the data.
 * More useful than you would think in conjunction with a switch statement
 * or jump table.
 */
enum spar_parsed
spar_meta_parse(struct spar_parser *parser, struct spar_lexinfo *info,
		struct spar_token *token);

enum spar_parsed
spar_mod_meta_func(struct spar_parser *parser, struct spar_lexinfo *info,
		   struct spar_token *token);

void
spar_mod_meta(struct spar_parser *to_mod, struct spar_parser *input);

void
spar_token_set_parser(struct spar_token *token, struct spar_parser *parser)
{
		token->type.text = spar_type_parser;
		token->dat.parser = parser;
}
