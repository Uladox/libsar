#include <ctype.h>
#include <stdio.h>

#define SPAR_LEX_CUE_PTR_TYPES struct spar_text_cue *text;
#include "core.h"
#include "text_utils.h"

void
spar_skip_space(struct spar_lexinfo *info)
{
	for (; isspace(*info->dat.text); ++info->dat.text)
		if (*info->dat.text == '\n')
			++info->cue.text->lines;
}
