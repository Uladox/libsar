# See LICENSE file for copyright and license details.

include ../config.mk

SRC = word_parser.c strlit_parser.c num_parser.c

INC = word_parser.h strlit_parser.h num_parser.h

OBJ = $(SRC:.c=.o)

LIB = libspar_parsers.a

all: $(LIB)

$(LIB): $(OBJ)
	@$(AR) -rcs $@ $(OBJ)

.c.o:
	@$(CC) $(CFLAGS) -c $<

install: $(LIB) $(INC)
	@echo @ install spar_parsers to $(DESTDIR)$(PREFIX)
	@mkdir -p $(DESTDIR)$(PREFIX)/lib
	@cp $(LIB) $(DESTDIR)$(PREFIX)/lib/$(LIB)
	@mkdir -p $(DESTDIR)$(PREFIX)/include/spar/parsers
	@cp $(INC) $(DESTDIR)$(PREFIX)/include/spar/parsers

uninstall:
	@echo @ uninstall spar_parsers from $(DESTDIR)$(PREFIX)
	@rm -f $(DESTDIR)$(PREFIX)/lib/$(LIB)
	@rm -rf $(DESTDIR)$(PREFIX)/include/spar/parsers

clean:
	@rm -f $(LIB) $(OBJ)
