#include <ctype.h>
#include <stdio.h>

#include "core.h"
#include "text_utils.h"

char sar_type_end[] = "end";

void
sar_skip_blank(Sar_lexi *info)
{
	char *str = info->dat;

	for (; isspace(*str); ++str)
		if (*str == '\n')
			++SAR_TEXT_CUE(info->cue)->lines;

	info->dat = str;
}

void
sar_skip_not_delim(Sar_lexi *info)
{
	char *str = info->dat;

	for (;; ++str) {
		switch (*str) {
		case '\n':
		case ' ':
		case '\t':
		case '\v':
		case '\f':
		case '\r':
		case ';':
		case '\0':
			info->dat = str;
			return;
		}
	}
}
