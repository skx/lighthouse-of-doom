# Our version comes from the GITHUB_REF environmental variable,
# if not set then we're running from "unreleased-git"
VERSION := $(or ${GITHUB_REF},${GITHUB_REF},"unreleased-git")


all: lighthouse

lighthouse: handlers.c  inventory.c  items.c  main.c  world.c util.c
	gcc -Wall -Wextra -o lighthouse -Os -Wall -Werror handlers.c  inventory.c  items.c  main.c  world.c util.c

clean:
	rm -f lighthouse game.com lihouse.com lihouse2.com encrypt || true

format:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.c *.h


# version.z80 will contain the last part of the string $VERSION
version:
	echo "DB \"$$(echo ${VERSION} | awk -F/ '{print $$NF}' )\"" >  version.z80

# build the game
game: game.z80 version
	pasmo --equ ENCRYPT_STRINGS=0 game.z80 lihouse.com

# Build the encryption helper
encrypt: encrypt.c
	gcc -o encrypt -Wall -Werror encrypt.c

# Build the game for release - with strings encrypted
release: game.z80 encrypt version
	pasmo --equ ENCRYPT_STRINGS=1 game.z80 lihouse.com
	./encrypt
	mv lihouse2.com lihouse.com

run-game: game
	~/cpm/cpm lihouse
