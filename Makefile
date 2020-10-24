CC = gcc
CFLAGS = -Wall -O3

all: game hijack

game:
	$(CC) $(CFLAGS) -s src/guessing_game.c -o guessing_game

game_debug:
	$(CC) $(CFLAGS) -DDEBUG src/guessing_game.c -o guessing_game

game_nocolor:
	$(CC) $(CFLAGS) -s -DNOCOLOR src/guessing_game.c -o guessing_game

game_debug_nocolor:
	$(CC) $(CFLAGS) -DNOCOLOR -DDEBUG src/guessing_game.c -o guessing_game

hijack:
	$(CC) $(CFLAGS) -FPIC -shared src/rand_hijack.c -o rand_hijack.so

clean:
	rm -f guessing_game rand_hijack.so

help:
	@echo "Default Target:"
	@echo "\t all => Build the default guessing game & hijack shared object."
	@echo "\nGame Targets:"
	@echo "\t game => Build the default guessing game."
	@echo "\t game_debug => Builds a debug version of guessing game."
	@echo "\t game_nocolor => Build a non-colorized guessing game."
	@echo "\t game_debug_nocolor => Build a non-colorized debug guessing game."
	@echo "\nHijack Targets:"
	@echo "\t hijack => Build standard LD_PRELOAD hijack shared object."
	@echo "\nMaintance Targets:"
	@echo "\t clean => delete the binaries."
