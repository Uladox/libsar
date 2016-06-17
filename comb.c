#include <stddef.h>
#include "core.h"
#include "comb.h"

const char spar_type_first[] = "first";
const char spar_type_all[] = "all";

void
spar_comb_add(struct spar_parser *comb, struct spar_parser_batch *batch)
{
	struct spar_parser_batch *old_batch = comb->dat.batch;

	(comb->dat.batch = batch)->next = old_batch;
}

enum spar_parsed
spar_comb_first_func(struct spar_parser *parser, struct spar_lexinfo *info,
		     struct spar_token *token, union spar_memory mem)
{
	enum spar_parsed parsed;
	struct spar_parser_batch *batch = parser->dat.batch;
	struct spar_parser **parsers;

	/* Lets hope nobody is stupid enough to use an empty batch. */
	for (; batch; batch = batch->next)
	        for (parsers = batch->parsers; *parsers; ++parsers) {
			parsed = spar_parse(*parsers, info, token, mem);
			/* The memory could be used to collect errors. */
			if (parsed != SPAR_ERROR)
				return parsed;
		}

	return SPAR_ERROR;
}

void
spar_comb_first(struct spar_parser *comb)
{
	comb->parse = spar_comb_first_func;
	comb->str_rep = spar_type_first;
}

enum spar_parsed
spar_comb_all_func(struct spar_parser *parser, struct spar_lexinfo *info,
		   struct spar_token *token, union spar_memory mem)
{
	enum spar_parsed parsed = SPAR_ERROR;
	struct spar_parser_batch *batch = parser->dat.batch;
	struct spar_parser **parsers;

	/* Lets hope nobody is stupid enough to use an empty batch. */
	for (; batch; batch = batch->next)
	        for (parsers = batch->parsers; *parsers; ++parsers) {
			/* The memory could be used to collect errors and
			 * results, clearly this is somewhat overengineered for
			 * text, but remember, this is to parse everything!
			 */
		        switch (spar_parse(*parsers, info, token, mem)) {
			case SPAR_ERROR:
				break;
			case SPAR_OK:
				if (parsed != SPAR_END)
					parsed = SPAR_OK;
				break;
			case SPAR_END:
				parsed = SPAR_END;
				break;
			}
		}

	return parsed;
}

void
spar_comb_all(struct spar_parser *comb)
{
	comb->parse = spar_comb_all_func;
	comb->str_rep = spar_type_all;
}
