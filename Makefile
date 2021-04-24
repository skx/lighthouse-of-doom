
all: lighthouse

lighthouse: handlers.c  inventory.c  items.c  main.c  world.c util.c
	gcc -o lighthouse -Os -Wall -Werror handlers.c  inventory.c  items.c  main.c  world.c util.c

clean:
	rm lighthouse

format:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.c *.h

game: game.z80
	pasmo  game.z80 game.com

run-game: game
	~/cpm/cpm game
