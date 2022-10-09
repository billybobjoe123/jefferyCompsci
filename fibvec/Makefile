OBJS	= test.o FibVec.o
SOURCE	= test.cpp FibVec.cpp
HEADER	= FibVec.h
OUT	= FibVec
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

test.o: test.cpp
	$(CC) $(FLAGS) test.cpp -std=c17

FibVec.o: FibVec.cpp
	$(CC) $(FLAGS) FibVec.cpp -std=c17


clean:
	rm -f $(OBJS) $(OUT)