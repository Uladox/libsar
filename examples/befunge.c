#include <stdlib.h>
#include <stdio.h>

#include "../core.h"
#include "../text_utils.h"
#include "../token_print.h"
#include "../strlit.h"

#define BEFUN_FIELD(PTR) ((Field *) (PTR))
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
	int x, y;
} Pos;

typedef union {
	int num;
	char *str;
} Stack_dat;

typedef struct {
	enum befun_dir dir;
	int x, y, max_x, max_y;
	char (*dat)[MAX_X];
} Field;

const char befun_com[] = "com";
const char befun_str[] = "str";

Stack_dat stack[1024];

char f_dat[MAX_Y][MAX_X] = {
	{ '"', 'h', 'e', 'l', 'l', 'o', '"' },
	{'^', '<'}
};


static inline Field *
field_inc(Field *f)
{
	switch (f->dir) {
	case BEFUN_UP:
		if (f->y - 1 < 0)
			return NULL;

		--f->y;
		break;
	case BEFUN_DOWN:
		if (f->y + 1 >= f->max_y)
			return NULL;

		++f->y;
		break;
	case BEFUN_LEFT:
		if (f->x - 1 < 0)
			return NULL;

		--f->x;
		break;
	case BEFUN_RIGHT:
		if (f->x + 1 >= f->max_x)
			return NULL;

		++f->x;
		break;
	}

	return f;
}

char
field_val(Field *f)
{
	return f->dat[f->y][f->x];
}

Field *
field_init(Field *f)
{
	Field *f2 = malloc(sizeof(*f2));

        if (!f2)
		return NULL;

	f2->dir = f->dir;
	f2->x = f->x;
	f2->y = f->y;
	f2->max_x = f->max_x;
	f2->max_y = f->max_y;
	f2->dat = f->dat;

	return f2;
}

int
field_dif(Field *curr, Field *dat)
{
	/* if (curr == dat) */
	/* 	printf("curr %i, dat %i\n", curr->x, dat->x); */
	if (curr->x != dat->x) {
		return curr->x - dat->x;
	}

	return curr->y - dat->y;
}

#define BEFUN_VAL(VAL) field_val(VAL)
#define BEFUN_VAL_INIT(CURR, DAT)				\
	SAR_TEXT_ERROR((CURR = field_init(DAT)), "could not init")
#define BEFUN_INC(CURR) SAR_TEXT_ERROR(field_inc(CURR), "could not inc field")
#define BEFUN_DIF(CURR, DAT) field_dif(CURR, DAT)

SAR_PARSE_STRLIT0(parse_strlit, befun_str, BEFUN_VAL, Field *,
		  BEFUN_VAL_INIT, BEFUN_INC, BEFUN_DIF, NOTHING2);

SAR_PARSER_INIT(strlit_parser, "parse_strlit", parse_strlit, NULL);

void
befun_print_token(Sar_token *token)
{
	Field *f = token->dat;
	size_t len = token->len;
	size_t count = 0;

	printf("%zu\n", len);

	switch (f->dir) {
	case BEFUN_UP:
		for (; count < len; ++count)
			putchar(f->dat[f->y - count][f->x]);
		break;
	case BEFUN_DOWN:
		for (; count < len; ++count)
			putchar(f->dat[f->y + count][f->x]);
		break;
	case BEFUN_LEFT:
		for (; count < len; ++count)
			putchar(f->dat[f->y][f->x - count]);
		break;
	case BEFUN_RIGHT:
		for (; count < len; ++count)
			putchar(f->dat[f->y][f->x + count]);
		break;

	}
}

int
main(int argc, char *argv[])
{
	Sar_token token;

	Field field = {
		.dir = BEFUN_RIGHT,
		.max_x = MAX_X,
		.max_y = MAX_Y,
		.x = 0,
		.y = 0,
		.dat = f_dat
	};

	Sar_lexi info = {
		.dat = &field,
		.error_leave = 1
	};

	int parsed = sar_parse(&strlit_parser, &info, &token);

	if (!parsed) {
		printf("Error: %s\n", info.error);
		/* printf("Error: %s on x = %i, y = %i.\n", info.error, */
		/*        SAR_TEXT_CUE(info.cue)->lines); */
	} else {
	        befun_print_token(&token);
		printf("\n");
	}

}
