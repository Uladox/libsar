/* Include these
 * #include <stdlib.h> all <stddef.h>
 * #include "core.h"
 */

#define SPAR_COMB_INIT_FIRST(NAME, DAT)			\
	struct spar_parser NAME = {			\
		.dat.batch = DAT,			\
		.type = SPAR_COMPOSITE,			\
		.parse = spar_comb_first_func,		\
		.str_rep = spar_type_first,		\
		.to_free = SPAR_DONT_FREE		\
	}

#define SPAR_COMB_INIT_ALL(NAME, DAT)			\
	struct spar_parser NAME = {			\
		.dat.batch = DAT,			\
		.type = SPAR_COMPOSITE,			\
		.parse = spar_comb_all_func,		\
		.str_rep = spar_type_all,		\
		.to_free = SPAR_DONT_FREE		\
	}

extern const char spar_type_first[];
extern const char spar_type_all[];

/* A list of parser pointers, duh. */
struct spar_parser_batch {
	struct spar_parser_batch *next;
	struct spar_parser **parsers;
};

void
spar_comb_add(struct spar_parser *comb, struct spar_parser_batch *batch);

enum spar_parsed
spar_comb_first_func(struct spar_parser *parser, struct spar_lexinfo *info,
		     struct spar_token *token, union spar_memory mem);

void
spar_comb_first(struct spar_parser *comb);

enum spar_parsed
spar_comb_all_func(struct spar_parser *parser, struct spar_lexinfo *info,
		   struct spar_token *token, union spar_memory mem);

void
spar_comb_all(struct spar_parser *comb);

static inline void
spar_comb_init(struct spar_parser *comb)
{
	comb->type = SPAR_COMPOSITE;
}
