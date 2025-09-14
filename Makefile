CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -O2
TARGET = assignment1

all: $(TARGET)

$(TARGET): convert.o main.o
	$(CC) $(CFLAGS) -o $(TARGET) convert.o main.o

convert.o: convert.c
	$(CC) $(CFLAGS) -c convert.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(TARGET) *.o
