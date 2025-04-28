all: a.out

a.tab.c a.tab.h: a.y
	bison -d a.y

lex.yy.c: a.l a.tab.h
	flex a.l

a.out: lex.yy.c a.tab.c a.c
	gcc lex.yy.c a.tab.c a.c -lfl -o a.out

run: a.out
	./a.out

clean:
	rm -f lex.yy.c a.tab.c a.tab.h a.out