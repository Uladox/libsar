EXEC := word strlit comb_first meta_test befunge
SRC := word.c strlit.c comb_first.c meta_test.c befunge.c
OBJ := $(SRC:.c=.o)

# Stops make from acting stupid
.SUFFIXES:
.PRECIOUS: %.o
.PHONY: all clean

all: $(EXEC)

%.o: %.c
	@gcc -g -c $<

$(EXEC): %: %.o ../libspar.a ../parsers/libspar_parsers.a
	@gcc -g -o $@ $^ 

../libspar.a:
	@(cd .. && make)

../parsers/libspar_parsers.a:
	@(cd ../parsers && make)

clean:
	@rm -f *.o word strlit comb_first meta_test

