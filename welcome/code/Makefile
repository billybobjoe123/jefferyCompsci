OBJS	= olleh.o
SOURCE	= olleh.cpp
HEADER	= 
OUT	= olleh
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

olleh.o: olleh.cpp
	$(CC) $(FLAGS) olleh.cpp 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
