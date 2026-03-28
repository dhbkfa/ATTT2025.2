CC = g++
all: main
main: main.cpp
	$(CC) -o main main.cpp
	./main

clean:
	rm -rf main
.PHONY: all clean