/* Include these
 * #include <stdlib.h> or <stddef.h>
 */

#define SAR_TEXT(PTR)				\
	((char *) (PTR))

#define SAR_IDENT(I) I
#define SAR_EQUAL(X, Y) (X = Y)

#define SAR_UNKNOWN_SIZE -1
#define SAR_SIZE_UNKNOWN(SIZE)			\
	((SIZE) < 0)

#define SAR_PARSE_FUNC(NAME)						\
        int								\
	NAME(Sar_parser *parser, Sar_lexi *info, Sar_token *token)

#define SAR_PARSER_INIT(NAME, STR_REP, PARSE, DAT)		\
        Sar_parser NAME = {					\
		.dat = DAT,					\
		.parse = PARSE,					\
		.str_rep = STR_REP,				\
		.type = SAR_PRIMATIVE,				\
		.to_free = 0					\
	}

#define SAR_LEXI_INIT(NAME, ERROR_LEAVE, CUE, MEM, DAT)			\
        Sar_lexi NAME = {						\
		.dat.generic = DAT,					\
		.cue.generic = CUE,					\
		.mem.generic = MEM,					\
		.error_leave = ERROR_LEAVE				\
	}

#define SAR_TOKEN_INIT(NAME, START_TYPE)	\
        Sar_token NAME = {			\
		.type = START_TYPE		\
	}

/* Contains the current point in the parsed data and error string. */

typedef struct {
	/* What we are reading! */
	void *dat;
	/* Holds stuff like line numbers & extra useful stuff. */
	void *cue;
	/* What we want to remember, useful for contex-sensitive parsing. */
        void *mem;
	/* If we should continue parsing on error, if reasonable. */
	int error_leave;
	/* Errors can be non-textual, especially for representing the mind. */
	void *error;
} Sar_lexi;

/* Contains structure created from parsed data */
typedef struct {
        void *dat;
        const void *type;
	size_t data_size;
	size_t len;
} Sar_token;

/* If the parser is hard coded or made of smaller parsers. */
enum sar_parser_type {
	SAR_PRIMATIVE,
	SAR_MODDED,
	SAR_COMPOSITE
};

/* The actual parser. Useful both in being hard coded or generated. */
typedef struct sar_parser Sar_parser;
struct sar_parser {
	void *dat;
	/* Function can be a combinator! */
	int
	(*parse)(Sar_parser *parser,
		 Sar_lexi *info,
		 Sar_token *token);
	const char *str_rep;

	/* Stuff combinators and mods should not touch! */
	/* type determines if we can cast to struct sar_comb safely. */
	enum sar_parser_type type;
	int to_free;
};

/* A convience function so you dont have to write parser->parse(parser, ...) */
static inline int
sar_parse(Sar_parser *parser, Sar_lexi *info, Sar_token *token)
{
	return parser->parse(parser, info, token);
}
