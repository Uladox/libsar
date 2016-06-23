/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 */

extern const char spar_type_strlit[];
extern struct spar_parser spar_strlit_parser;

enum spar_parsed
spar_strlit_str(struct spar_token *token, char **str_ref);
