.PHONY: all

all: main test1 test2 test3 test4 test5

main: main.c
	gcc main.c -o main -I.

test1: test1.c
	gcc test1.c -o test1 -I. -lm

test2: test2.c
	gcc test2.c -o test2 -I.

test3: test3.c
	gcc test3.c -o test3 -I.

test4: test4.c
	gcc test4.c -o test4 -I.

test5: test5.c
	gcc test5.c -o test5 -I.