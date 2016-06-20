#include <ctype.h>
#include <stdio.h>

#include "core.h"
#include "text_utils.h"

char spar_type_end[] = "end";

void
spar_skip_blank(struct spar_lexinfo *info)
{
	for (; isspace(*info->dat.text); ++info->dat.text)
		if (*info->dat.text == '\n')
			++info->cue.text->lines;
}

void
spar_skip_not_delim(struct spar_lexinfo *info)
{
	for (;; ++info->dat.text) {
		switch (*info->dat.text) {
		case '\n':
		case ' ':
		case '\t':
		case '\v':
		case '\f':
		case '\r':
		case ';':
		case '\0':
			return;
		}
	}
}
