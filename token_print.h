/* Include these
 * #include <stdio.h>
 * #include "core.h"
 */

static inline void
spar_print_text_token(struct spar_token *token)
{
	fwrite(token->dat.text, token->len, sizeof(char), stdout);
}

static inline void
spar_fprint_text_token(struct spar_token *token, FILE *file)
{
	fwrite(token->dat.text, token->len, sizeof(char), file);
}
