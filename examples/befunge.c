#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../text_utils.h"
#include "../token_print.h"

#define BEFUN_FIELD(PTR) ((Field *) (PTR))
#define BEFUN_VAL(FIELD) (field_val(BEFUN_FIELD(FIELD)))
#define NOTHING2(X, Y)


#define MAX_X 80
#define MAX_Y 25

enum befun_dir {
	BEFUN_UP,
	BEFUN_DOWN,
	BEFUN_LEFT,
	BEFUN_RIGHT
};

typedef struct {
	enum befun_dir dir;
	int x, y, max_x, max_y;
	char **dat;
} Field;

const char befun_com[] = "com";
const char befun_str[] = "str";

int stack[1024];

char f_dat[MAX_Y][MAX_X] = {
	{'>', 'v'},
	{'^', '<'}
};

static inline char
field_val(Field *f)
{
	return f->dat[f->y][f->x];
}

size_t
field_dif(

static inline int
field_next(Field *f, char *val)
{
	switch (f->dir) {
	case BEFUN_UP:
		if (f->y - 1 < 0)
			return 0;

		*val = f->dat[--f->y][f->x];
		break;
	case BEFUN_DOWN:
		if (f->y + 1 >= f->max_y)
			return 0;

		*val = f->dat[++f->y][f->x];
		break;
	case BEFUN_LEFT:
		if (f->x - 1 < 0)
			return 0;

		*val = f->dat[f->y][--f->x];
		break;
	case BEFUN_RIGHT:
		if (f->x + 1 >= f->max_x)
			return 0;

		*val = f->dat[f->y][++f->x];
		break;
	}

	return 1;
}

int
dat_next(Sar_parser *parser, Sar_lexi *info, Sar_token *token)
{
	return field_next(info->dat, info->cue, info->mem, );
}

SAR_PARSE_STRLIT0(str_parse, befun_str, , NOTHING2);



int
main(int argc, char *argv[])
{
	Sar_token token;

	Field field = {
		.max_x = MAX_X,
		.max_y = MAX_Y,
		.dat = f_dat
	};

	Sar_lexi info = {
		.dat = field,
		.error_leave = 1
	};

}
