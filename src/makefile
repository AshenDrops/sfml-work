NAME = test.out

OBJS = main.o binary.o

LIBS = -lsfml-graphics -lsfml-system -lsfml-window
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(LIBS) $(DEBUG)

CXX := g++

#----------

$(NAME): $(OBJS)
	$(CXX) $(LFLAGS) -o $@ $(OBJS)

main.o: main.cpp main.h titlemenu.h
	$(CXX) $(CFLAGS) -o $@ main.cpp

titlemenu.h: titlemenu.png
	xxd -i $< > $@

#----------

clean:
	\rm *.o $(NAME)

install:
	cp $(NAME) /usr/bin/$(NAME)

uninstall:
	rm -f /usr/bin/$(NAME)
