CFLAGS:= -Wall -std=c++17
CC:=g++

all: main

%.o: %.cpp
	$(CC) $(CFLAGS)  -o $@ -c $<

memory: memory.o
	$(CC) $(CFLAGS) -o test/$@ test/$@.cpp $<

riscv: riscv.o memory.o hart.o log_service.o
	$(CC) $(CFLAGS) -o test/$@ test/$@.cpp $^

decoder: decoder.o riscv.o memory.o hart.o log_service.o
	$(CC) $(CFLAGS) -o test/$@ test/$@.cpp $^

simulator: decoder.o riscv.o hart.o memory.o log_service.o
	$(CC) $(CFLAGS) -o test/$@ test/$@.cpp $^

mte: riscv.o memory.o decoder.o simulator.o log_service.o hart.o
	$(CC) $(CFLAGS) -o test/$@ test/$@.cpp $^

test: memory riscv decoder simulator

main: riscv.o memory.o decoder.o simulator.o main.o log_service.o hart.o
	$(CC) $(CFLAGS) -o main $^ # -lelf

clean:
	rm -rf *.o *.exe log_file test/*.exe
