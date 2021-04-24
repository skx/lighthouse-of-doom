
all: lighthouse

lighthouse: handlers.c  inventory.c  items.c  main.c  world.c
	gcc -o lighthouse -Wall -Werror handlers.c  inventory.c  items.c  main.c  world.c

clean:
	rm lighthouse
