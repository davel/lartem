CC = gcc -Wall -g
LD = gcc -lpanel -lncurses -lefence -g

OBJS = main.o display.o player.o role.o monst.o ask.o level.o map.o util.o

lartem: $(OBJS)
	$(LD) $(OBJS) -o lartem

%.o: %.c *.h
	$(CC) -c $< -o $@

clean:
	rm -f *.o lartem
