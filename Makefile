CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: mapper

clean:
	rm -f *.o mapper testgraph
# --- Part A ---
mapper: mapper.o data.o
	$(CC) $(CFLAGS) -o mapper mapper.o data.o

mapper.o: mapper.c data.h
	$(CC) $(CFLAGS) -c mapper.c

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c

# --- Part B ---
testgraph: testgraph.o graph.o
	$(CC) $(CFLAGS) -o testgraph testgraph.o graph.o

testgraph.o: testgraph.c testgraph.h graph.h
	$(CC) $(CFLAGS) -c testgraph.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

