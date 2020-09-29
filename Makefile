CC = gcc -Wall -g
LD = gcc -g

OBJS = main.o display.o player.o role.o monst.o ask.o level.o map.o util.o stats.o attack.o

LIBS = -lncurses -lpanel

lartem: $(OBJS)
	$(LD) $(OBJS) $(LIBS) -o lartem

%.o: %.c *.h
	$(CC) -c $< -o $@

clean:
	rm -f *.o lartem
