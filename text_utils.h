/* Include these
 * #include <stdlib.h> or <stddef.h>
 * #include "core.h"
 */

#define SAR_TEXT_CUE_INIT(NAME, LINES)		\
	struct sar_text_cue NAME = {		\
		.lines = LINES			\
	}
#define SAR_TEXT_CUE(PTR)			\
	((Sar_text_cue *) (PTR))

typedef struct {
	size_t lines;
	size_t error_line;
} Sar_text_cue;

extern char sar_type_end[];

static inline void
sar_text_error(Sar_lexi *info, char *msg, size_t line)
{
	Sar_text_cue *cue = info->cue;

	info->error = msg;
        cue->error_line = cue->lines + line;
}

void
sar_skip_blank(Sar_lexi *info);

void
sar_skip_not_delim(Sar_lexi *info);
