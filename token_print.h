/* Include these
 * #include <stdio.h>
 * #include "core.h"
 */

static inline void
sar_print_text_token(Sar_token *token)
{
	fwrite(token->dat, token->len, sizeof(char), stdout);
}

static inline void
sar_fprint_text_token(Sar_token *token, FILE *file)
{
	fwrite(token->dat, token->len, sizeof(char), file);
}
