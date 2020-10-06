CC = $(CXX)
CXXFLAGS = -std=c++2a -Ofast
LDLIBS = -lbenchmark
APP = main

all: clean $(APP)

main.cpp: PPP.hpp

clean:
	$(RM) main *.o
