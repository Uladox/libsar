/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 */

struct spar_text_cue {
	size_t lines;
	size_t error_line;
};

void
spar_skip_space(struct spar_lexinfo *info);
