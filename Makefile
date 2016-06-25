# See LICENSE file for copyright and license details.

include config.mk

SRC = text_utils.c meta.c comb.c cusstrlit.c

OBJ = $(SRC:.c=.o)

LIB = libspar.a

INC = core.h cases.h meta.h comb.h loop.h text_utils.h token_print.h \
      cusword.h cusstrlit.h cusnum.h

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
