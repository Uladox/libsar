#define SPAR_DIGIT_CASES			\
	case '0':				\
	case '1':				\
	case '2':				\
	case '3':				\
	case '4':				\
	case '5':				\
	case '6':				\
	case '7':				\
	case '8':				\
	case '9'

#define SPAR_WSPACE_CASES			\
	case '\n':				\
	case ' ':				\
	case '\t':				\
	case '\v':				\
	case '\f':				\
	case '\r'

#define SPAR_SEP_CASES				\
	SPAR_WSPACE_CASES:			\
	case ';'
