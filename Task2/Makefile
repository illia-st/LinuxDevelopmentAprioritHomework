CXX = g++
CC = $(CXX)

DEBUG_LEVEL     = -g
EXTRA_CCFLAGS   = -Wall
CXXFLAGS        = $(DEBUG_LEVEL) $(EXTRA_CCFLAGS)
CCFLAGS         = $(CXXFLAGS)


PipeUsing: main.o
	g++ -o PipeUsing main.cpp
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o