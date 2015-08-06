NAME = test.out

OBJS = main.o

DATAFILES = background.png o.png x.png quicksand-bold.otf

LIBS = -lsfml-graphics -lsfml-system -lsfml-window
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(LIBS) $(DEBUG)

CXX := g++

#----------

$(NAME): $(OBJS)
	$(CXX) $(LFLAGS) -o $@ $(OBJS)

main.o: main.cpp data.h
	$(CXX) $(CFLAGS) -o $@ main.cpp

data.h: $(DATAFILES)
	echo -n "" > $@
	for file in $(DATAFILES); do xxd -i $$file >> $@; done

#----------

clean:
	\rm *.o $(NAME)

install:
	cp $(NAME) /usr/bin/$(NAME)

uninstall:
	rm -f /usr/bin/$(NAME)
