CXX = g++
CC = $(CXX)

DEBUG_LEVEL     = -g
EXTRA_CCFLAGS   = -Wall
CXXFLAGS        = $(DEBUG_LEVEL) $(EXTRA_CCFLAGS)
CCFLAGS         = $(CXXFLAGS)

CopyFile: main.o libCopyFile.a
	g++ -o CopyFile main.o -L. libCopyFile.a
main.o: main.cpp CopyFile.h
	g++ -c main.cpp

libCopyFile.a: CopyFile.o
	ar rcs libCopyFile.a CopyFile.o

CopyFile.o: CopyFile.h CopyFile.cpp
	g++ -c CopyFile.cpp
clean:
	rm *.o
	rm *.a