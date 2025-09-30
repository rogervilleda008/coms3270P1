CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: mapper

mapper: mapper.o data.o
	$(CC) $(CFLAGS) -o mapper mapper.o data.o

mapper.o: mapper.c data.h
	$(CC) $(CFLAGS) -c mapper.c

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c

clean:
	rm -f *.o mapper

