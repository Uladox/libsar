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

#define SAR_ADD_DIF(CURR, DAT)			\
	(CURR - SAR_TEXT(DAT))

#define SAR_ADD_LINES(CUE, LINE)		\
	(SAR_TEXT_CUE(CUE)->lines += LINE)

#define SAR_TEXT_ERROR(EXPR, STR)				\
	do { if (!EXPR) { info->error = (STR); return 0; } } while (0)

typedef struct {
	size_t lines;
} Sar_text_cue;

extern char sar_type_end[];

void
sar_skip_blank(Sar_lexi *info);

void
sar_skip_not_delim(Sar_lexi *info);
