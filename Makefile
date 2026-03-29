CC = g++
SRCS	= main.cpp ./SubBytes_Code/SubBytes.cpp ./Shift_Rows_Code/shift_Rows.cpp 
all: main
main: $(SRCS)
	$(CC) -I. -o main $(SRCS)
	./main

clean:
	rm -rf main
.PHONY: all clean