
all: lighthouse

lighthouse: handlers.c  inventory.c  items.c  main.c  world.c util.c
	gcc -o lighthouse -Wall -Werror handlers.c  inventory.c  items.c  main.c  world.c util.c

clean:
	rm lighthouse

format:
	astyle --style=allman -A1 --indent=spaces=4   --break-blocks --pad-oper --pad-header --unpad-paren --max-code-length=200 *.c *.h
