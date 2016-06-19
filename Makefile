# See LICENSE file for copyright and license details.

include config.mk

SRC = word_parser.c strlit_parser.c num_parser.c text_utils.c meta.c comb.c
OBJ = $(SRC:.c=.o)

LIB = libspar.a
#comb.h  core.h  loop.h  strlit_parser.h  text_utils.h  token_print.h  word_parser.h

INC = core.h text_utils.h token_print.h word_parser.h strlit_parser.h meta.h \
      comb.h loop.h num_parser.h

all: $(LIB)

$(LIB): $(OBJ)
	@$(AR) -rcs $@ $(OBJ)

.c.o:
	@$(CC) $(CFLAGS) -c $<

install: $(LIB) $(INC)
	@echo @ install spar to $(DESTDIR)$(PREFIX)
	@mkdir -p $(DESTDIR)$(PREFIX)/lib
	@cp $(LIB) $(DESTDIR)$(PREFIX)/lib/$(LIB)
	@mkdir -p $(DESTDIR)$(PREFIX)/include/spar
	@cp $(INC) $(DESTDIR)$(PREFIX)/include/spar/

uninstall:
	@echo @ uninstall spar from $(DESTDIR)$(PREFIX)
	@rm -f $(DESTDIR)$(PREFIX)/lib/$(LIB)
	@rm -rf $(DESTDIR)$(PREFIX)/include/spar/

clean:
	@rm -f $(LIB) $(OBJ)
