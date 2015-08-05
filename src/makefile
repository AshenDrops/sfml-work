OBJS = main.o

VPATH = ./src

LIBS = -lsfml-graphics -lsfml-system -lsfml-window
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(LIBS) $(DEBUG)

CXX := g++

#----------

test: $(OBJS)
	$(CXX) $(LFLAGS) -o $@ $(OBJS)

main.o: main.cpp main.h
	$(CXX) $(CFLAGS) -o $@ main.cpp

#----------

clean:
	\rm *.o test

install:
	cp test /usr/bin/test

uninstall:
	rm -f /usr/bin/test
