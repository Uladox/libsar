/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 */

struct spar_text_cue {
	size_t lines;
	size_t error_line;
};

extern char spar_type_end[];

static inline void
spar_text_error(struct spar_lexinfo *info, char *msg, size_t line)
{
	info->error.text = msg;
	info->cue.text->error_line = info->cue.text->lines + line;
}

void
spar_skip_blank(struct spar_lexinfo *info);

void
spar_skip_not_delim(struct spar_lexinfo *info);
