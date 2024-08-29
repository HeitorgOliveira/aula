all:
	gcc karatsuba.c operacoes.c -o karatsuba -std=c99 -lm

run:
	./karatsuba

operacoes.o:
	gcc -c operacoes.c operacoes.o