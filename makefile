all: main test1 test2 test3 test4 test5

main: main.o
	gcc main.o -o main -I.

test1: test1.o
	gcc test1.o -o test1 -I. -lm

test2: test2.o
	gcc test2.o -o test2 -I. -lm

test3: test3.o
	gcc test3.o -o test3 -I. -lm

test4: test4.o
	gcc test4.o -o test4 -I. -lm

test5: test5.o
	gcc test5.o -o test5 -I. -lm