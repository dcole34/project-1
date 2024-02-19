```make
CC = gcc
CFLAGS = -Wall

TARGET = main test1 test2 test3 test4 test5
SRCS = main.c test1.c test2.c test3.c test4.c test5.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)