/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 */

#define SAR_MOD_INIT_META(NAME, DAT)			\
	Sar_parser NAME = {				\
		.dat = DAT,				\
		.type = SAR_MODDED,			\
		.parse = sar_mod_meta_func,		\
		.str_rep = sar_type_meta,		\
		.to_free = 0				\
	}

extern const char sar_type_parser[];
extern const char sar_type_meta[];

/* For a parser that spits out a parser to parse the data.
 * More useful than you would think in conjunction with a switch statement
 * or jump table.
 */
int
sar_meta_parse(Sar_parser *parser, Sar_lexi *info, Sar_token *token);

int
sar_mod_meta_func(Sar_parser *parser, Sar_lexi *info, Sar_token *token);

void
sar_mod_meta(Sar_parser *to_mod, Sar_parser *input);

void
sar_token_set_parser(Sar_token *token, Sar_parser *parser)
{
		token->type = sar_type_parser;
		token->dat = parser;
}
