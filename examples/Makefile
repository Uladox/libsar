all: word strlit comb_first meta_test

word: word.o ../libspar.a
	gcc -g -o word word.o ../libspar.a

word.o: word.c
	gcc -g -c word.c

strlit: strlit.o ../libspar.a
	gcc -g -o strlit strlit.o ../libspar.a

strlit.o: strlit.c
	gcc -g -c strlit.c

comb_first: comb_first.o ../libspar.a
	gcc -g -o comb_first comb_first.o ../libspar.a

comb_first.o: comb_first.c
	gcc -g -c comb_first.c

meta_test: meta_test.o ../libspar.a
	gcc -g -o meta_test meta_test.o ../libspar.a

meta_test.o: meta_test.c
	gcc -g -c meta_test.c

../libspar.a:
	(cd .. && make)
clean:
	rm -f *.o word strlit comb_first meta_test
