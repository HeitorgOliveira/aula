all:
	gcc karatsuba.c operacoes.c -o karatsuba -lm

run:
	./karatsuba

operacoes.o:
	gcc -c operacoes.c operacoes.o