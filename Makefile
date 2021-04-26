
all: lighthouse

lighthouse: handlers.c  inventory.c  items.c  main.c  world.c util.c
	gcc -o lighthouse -Os -Wall -Werror handlers.c  inventory.c  items.c  main.c  world.c util.c

clean:
	rm -f lighthouse game.com crypt || true

format:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.c *.h


# build the game
game: game.z80
	pasmo --equ ENCRYPT_STRINGS=0 game.z80 lihouse.com

# Build the encryption helper
encrypt: encrypt.c
	gcc -o encrypt -Wall -Werror encrypt.c

# Build the game for release - with strings encrypted
release: game.z80 encrypt
	pasmo --equ ENCRYPT_STRINGS=1 game.z80 lihouse.com
	./encrypt
	mv lihouse2.com lihouse.com

run-game: game
	~/cpm/cpm lihouse
