CC = g++
SRCS = main.cpp \
	./SubBytes_Code/SubBytes.cpp \
	./Shift_Rows_Code/shift_Rows.cpp \
	./Code_Mix_Columns/mix_columns.cpp \
	./AddRoundKey/ARK.cpp \
	./Key_Expansion/KeyExpansion.cpp

all: main

main: $(SRCS)
	$(CC) -I. -o main $(SRCS)
	./main

clean:
	rm -rf main

.PHONY: all clean main