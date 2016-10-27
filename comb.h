/* Include these
 * #include <stdlib.h> all <stddef.h>
 * #include "core.h"
 */

#define SAR_BATCH(PTR)				\
	((Sar_batch *) (PTR))

#define SAR_COMB_INIT_FIRST(NAME, ...)			\
	Sar_parser NAME = {				\
		.dat = DAT,			\
		.type = SAR_COMPOSITE,			\
		.parse = sar_prim_comb_first,		\
		.str_rep = sar_type_first,		\
		.to_free = 0				\
	}

#define SAR_COMB_INIT_ALL(NAME, ...)			\
        Sar_parser NAME = {				\
		.dat = &(Sar_batch) {			\
			.prim = 1,			\

		},					\
		.type = SAR_COMPOSITE,			\
		.parse = sar_prim_comb_all,		\
		.str_rep = sar_type_all,		\
		.to_free = 0				\
	}

extern const char sar_type_first[];
extern const char sar_type_all[];

typedef sar_parser_list Sar_parser_list;

struct sar_parser_list {
	Sar_parser_list *next;
	Sar_parser *parser;
};

/* A list of parser pointers, duh. */
typedef struct sar_parser_batch Sar_batch;
struct sar_parser_batch {
	union {
	        Sar_parser_list *list;
		Sar_parser **parsers;
	} val;

	int prim;
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
