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


# Build the encryption helper
encrypt: encrypt.c
	gcc -o encrypt -Wall -Werror encrypt.c


# Format our C-code
format:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.c *.h


# version.z80 will contain the last part of the string $VERSION
version:
	echo "DB \"$$(echo ${VERSION} | awk -F/ '{print $$NF}' )\"" >  version.z80



# build the game for CP/M
game-cpm: game.z80 bios.z80 version Makefile
	pasmo --equ ENTRYPOINT=100h --equ ENCRYPT_STRINGS=0 --equ SPECTRUM=0 game.z80 lihouse.com

# build the game for CP/M with encrypted strings/code
game-cpm-encrypted: game.z80 bios.z80 version Makefile encrypt
	pasmo --equ ENTRYPOINT=100h --equ ENCRYPT_STRINGS=1 --equ SPECTRUM=0 game.z80 lihouse.com
	./encrypt lihouse.com lihousex.com
	rm lihouse.com



# build the game for the ZX Spectrum
game-spectrum: game.z80 bios.z80 version Makefile
	pasmo --tapbas --equ ENTRYPOINT=32768 --equ ENCRYPT_STRINGS=0 --equ SPECTRUM=1 game.z80 lihouse.tap

# build the game for the ZX Spectrum with encrypted strings
game-spectrum-encrypted: game.z80 bios.z80 version Makefile encrypt
	pasmo --tapbas --equ ENTRYPOINT=32768 --equ ENCRYPT_STRINGS=1 --equ SPECTRUM=1 game.z80 lihouse.tap
	./encrypt -crc lihouse.tap lihousex.tap
	rm lihouse.tap


# Build the game for release - with strings encrypted
release: version
	make game-cpm-encrypted
	make game-cpm
	make game-spectrum-encrypted
	make game-spectrum


# Run the CP/M version via runcpm
run-cpm: game-cpm
	~/cpm/cpm lihouse

# Run the CP/M version via runcpm, with the encrypted version of the code
run-cpm-encrypted: game-cpm-encrypted
	~/cpm/cpm lihouseX

# Run the spectrum version
run-spectrum: game-spectrum
	xspect -quick-load -load-immed -tap lihouse.tap

# Run the spectrum version, with strings encrypted
run-spectrum-encrypted: game-spectrum-encrypted
	xspect -quick-load -load-immed -tap lihousex.tap
