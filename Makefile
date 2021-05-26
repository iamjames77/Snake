CC = g++
CCFLAGS = -g

Snake: main.o Game.o
	$(CC) $(CCFLAGS) -o Snake main.o Game.o -lncursesw

clean:
	rm -f *.o

%.o : %.cpp %.h
	$(CC) $(CCFLAGS) -c $<

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $<

% : %.cpp
	$(CC) $(CCFLAGS) -o $@ $<
