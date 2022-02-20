.PHONY: all

all:
	gcc -O2 -I/opt/netronome/include -L/opt/netronome/lib get_symbol.c -o get_symbol -lnfp -Wall
