/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 */

/* #define SPAR_MOD_INIT_LOOP(NAME, PARSER, CHECK)		\ */
/* 	struct spar_parser NAME = {			\ */
/* 		.dat.loop = &(struct spar_loop) {	\ */
/* 			.parser = PARSER,		\ */
/* 			.check = CHECK			\ */
/* 		},					\ */
/* 		.type = SPAR_MODDED,			\ */
/* 		.parse = spar_mod_loop_func,		\ */
/* 		.str_rep = spar_type_loop,		\ */
/* 		.to_free = SPAR_DONT_FREE		\ */
/* 	} */

/* struct spar_loop { */
/* 	struct spar_parser *parser; */
/* 	struct spar_parser *check; */
/* }; */

/* extern const char spar_type_loop[]; */

/* /\* For a parser that spits out a parser to parse the data. */
/*  * More useful than you would think in conjunction with a switch statement */
/*  * or jump table. */
/*  *\/ */
/* enum spar_parsed */
/* spar_loop_parse(struct spar_parser *parser, struct spar_lexinfo *info, */
/* 		struct spar_token *token); */

/* enum spar_parsed */
/* spar_mod_loop_func(struct spar_parser *parser, struct spar_lexinfo *info, */
/* 		   struct spar_token *token); */

/* void */
/* spar_mod_loop(struct spar_parser *to_mod, struct spar_parser *input); */
