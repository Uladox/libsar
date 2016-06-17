/* Include these
 * #include <stdlib.h> or <stddef.h>
 */

#define SPAR_SIZE_UNKNOWN(SIZE)			\
	((SIZE) < 0)
#define SPAR_UNKNOWN_SIZE -1

#define SPAR_PARSER_INIT(NAME, STR_REP, PARSE, DAT)		\
	struct spar_parser NAME = {				\
		.dat.generic = DAT,				\
		.parse = PARSE,					\
		.str_rep = STR_REP,				\
		.type = SPAR_PRIMATIVE,				\
		.to_free = SPAR_DONT_FREE			\
	}

union spar_dat {
	/* Allows you to add new types to avoid cumbersome type casting.
	 * Avoid using types that are not the same size as a pointer!
	 */
#ifdef SPAR_DAT_PTR_TYPES
	SPAR_DAT_PTR_TYPES
#endif
	/* Checks if uint8_t is present (from stdint.h) for unicode (utf8) */
#ifdef UINT8_MAX
	uint8_t *utf8;
#endif
	/* Meta! Useful if the data contains hints as to how to be parsed. */
	struct spar_parser *parser;
	/* My own list implementation for parser combinators. */
	struct spar_parser_batch *batch;
	/* Useful for functions where pointer type does not matter. */
	void *generic;
	/* Same as generic, but more fun to write when setting to NULL. */
	void *stuff;
	/* Standard parser stuff, char array strings. */
	char *text;
};

union spar_lex_cue {
	/* Used for data structures to hold info such as line number. */
#ifdef SPAR_LEX_CUE_PTR_TYPES
        SPAR_LEX_CUE_PTR_TYPES
#endif
	struct spar_text_cue *text;
	void *generic;
};

union spar_memory {
	/* Used to hold memory between parsers. */
#ifdef SPAR_MEMORY_PTR_TYPES
	SPAR_MEMORY_PTR_TYPES
#endif
	void *stuff;
	void *generic;
};

/* Contains the current point in the parsed data and error string. */
struct spar_lexinfo {
	/* What we are reading! */
	union spar_dat dat;
	/* Holds stuff like line numbers & extra useful stuff. */
	union spar_lex_cue cue;
	/* Errors can be not text, especially for representing the mind. */
	union spar_dat error;
	/* What we want to remember, useful for contex-sensitive parsing. */
	union spar_memory mem;
};

/* Contains structure created from parsed data */
struct spar_token {
	union spar_dat dat;
	const char *type;
	size_t data_size;
	size_t len;
};

/* Enums for parser information */
/* If we are successful, are at the end, or have an error. */
enum spar_parsed {
	SPAR_OK,
	SPAR_END,
	SPAR_ERROR
};

/* If the parser is hard coded or made of smaller parsers. */
enum spar_parser_type {
	SPAR_PRIMATIVE,
	SPAR_MODDED,
	SPAR_COMPOSITE
};

/* To free the parser or not. */
enum spar_parser_free {
	SPAR_FREE,
	SPAR_DONT_FREE
};

/* The actual parser. Useful both in being hard coded or generated. */
struct spar_parser {
	union spar_dat dat;
	/* Function can be a combinator! */
	enum spar_parsed (*parse)(struct spar_parser *parser,
				  struct spar_lexinfo *info,
				  struct spar_token *token);
	const char *str_rep;

	/* Stuff combinators and mods should not touch! */
	/* type determines if we can cast to struct spar_comb safely. */
	enum spar_parser_type type;
	/* to_free is used to check if we should free, if should always be
	 * SPAR_DONT_FREE if the parser is not generated at runtime
	 */
	enum spar_parser_free to_free;
};

/* A convience function so you dont have to write parser->parse(parser, ...) */
static inline enum spar_parsed
spar_parse(struct spar_parser *parser,
	   struct spar_lexinfo *info, struct spar_token *token)
{
	return parser->parse(parser, info, token);
}
