EXEC := word strlit comb_first meta_test
SRC := word.c strlit.c comb_first.c meta_test.c
OBJ := $(SRC:.c=.o)

# Stops make from acting stupid
.SUFFIXES:
.PRECIOUS: %.o
.PHONY: all clean

all: word strlit comb_first meta_test

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

