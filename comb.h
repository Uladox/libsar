/* Include these
 * #include <stdlib.h> all <stddef.h>
 * #include "core.h"
 */

#define SAR_BATCH(PTR)				\
	((Sar_batch *) (PTR))

#define SAR_COMB_INIT_FIRST(NAME, DAT)			\
	Sar_parser NAME = {				\
		.dat = DAT,			\
		.type = SAR_COMPOSITE,			\
		.parse = sar_comb_first_func,		\
		.str_rep = sar_type_first,		\
		.to_free = 0				\
	}

#define SAR_COMB_INIT_ALL(NAME, DAT)			\
        Sar_parser NAME = {				\
		.dat = DAT,				\
		.type = SAR_COMPOSITE,			\
		.parse = sar_comb_all_func,		\
		.str_rep = sar_type_all,		\
		.to_free = 0				\
	}

extern const char sar_type_first[];
extern const char sar_type_all[];

/* A list of parser pointers, duh. */
typedef struct sar_parser_batch Sar_batch;
struct sar_parser_batch {
        Sar_batch *next;
        Sar_parser **parsers;
};

void
sar_comb_add(Sar_parser *comb, Sar_batch *batch);

int
sar_comb_first_func(Sar_parser *parser, Sar_lexi *info, Sar_token *token);

void
sar_comb_first(Sar_parser *comb);

int
sar_comb_all_func(Sar_parser *parser, Sar_lexi *info, Sar_token *token);

void
sar_comb_all(Sar_parser *comb);

static inline void
sar_comb_init(Sar_parser *comb)
{
	comb->type = SAR_COMPOSITE;
}
