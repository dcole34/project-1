.PHONY: all

all: main test1 test2 test3 test4 test5

main: main.c
	gcc -o main.c main.c -I.

test1: test1.c
	gcc -o test1 test1.c -I.

test2: test2.c
	gcc -o test2 test2.c -I.

test3: test3.c
	gcc -o test3 test3.c -I.

test4: test4.c
	gcc -o test4 test4.c -I.

test5: test5.c
	gcc -o test5 test5.c -I.