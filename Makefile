# Our version comes from the GITHUB_REF environmental variable,
# if not set then we're running from "unreleased-git"
VERSION := $(or ${GITHUB_REF},${GITHUB_REF},"unreleased-git")


all: lighthouse game-cpm game-spectrum

# Build the C version
lighthouse: handlers.c  inventory.c  items.c  main.c  world.c util.c
	gcc  -o lighthouse -Os -Wall -Wextra -Werror handlers.c  inventory.c  items.c  main.c  world.c util.c


# Clean our generated output
clean:
	rm -f lighthouse *.com *.tap encrypt || true

# Format our C-code
format:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.c *.h


# version.z80 will contain the last part of the string $VERSION
version:
	echo "DB \"$$(echo ${VERSION} | awk -F/ '{print $$NF}' )\"" >  version.z80

# build the game for CP/M
game-cpm: game.z80 bios.z80 version Makefile
	pasmo --equ ENTRYPOINT=100h --equ ENCRYPT_STRINGS=0 --equ SPECTRUM=0 game.z80 lihouse.com

# build the game for the ZX Spectrum
game-spectrum: game.z80 bios.z80 version Makefile
	pasmo --tapbas --equ ENTRYPOINT=32768 --equ ENCRYPT_STRINGS=0 --equ SPECTRUM=1 game.z80 lihouse.tap

# Build the encryption helper
encrypt: encrypt.c
	gcc -o encrypt -Wall -Werror encrypt.c

# Build the game for release - with strings encrypted
release: game.z80 encrypt version
	pasmo --equ ENTRYPOINT=100h --equ ENCRYPT_STRINGS=1 --equ SPECTRUM=0 game.z80 lihouse.com
	./encrypt
	mv lihouse2.com lihouse.com


# Run for CP/M
run-cpm: game
	~/cpm/cpm lihouse

run-spectrum:
	xspect -quick-load -load-immed -tap *.tap
