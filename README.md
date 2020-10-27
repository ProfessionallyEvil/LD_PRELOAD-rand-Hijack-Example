# LD_PRELOAD-rand-Hijack-Example
Code samples to go along with the blog post on using LD_PRELOAD to hijack rand() in a number guessing game.

## Links to Tutorials
Blog: TODO - FILL IN WHEN READY

YouTube: https://youtu.be/pZCMxm1X7QU

## Overview
This repo is used to provide some code samples to go along side a tutorial in Secure Ideas blogs and videos. This code repo will provide you with the code for:

 * The number guessing game
 * The LD_PRELOAD hijack code
 * A make file to build it easily in a Kali VM.
 
The goal of this tutorial is to show how to use LD_PRELOAD to hijack imported functions in a binary. In this case we have a random number guessing game as a tutorial and will be using LD_PRELOAD to cheat in it by hijacking ```rand()``` and making it return a static value of 42, making the random number guessing game not-so-random and a lot easier to win.

## Building The Code Using Make.
Once you clone the repo, simply change into the directory and run ```make``` or ```make all``` to build both the game and the LD_PRELOAD hijack shared object. The make file also includes a help option to show all of the build targets:

```
kali@kali:~$ make help
Default Target:
         all => Build the default guessing game & hijack shared object.

Game Targets:
         game => Build the default guessing game.
         game_debug => Builds a debug version of guessing game.
         game_nocolor => Build a non-colorized guessing game.
         game_debug_nocolor => Build a non-colorized debug guessing game.

Hijack Targets:
         hijack => Build standard LD_PRELOAD hijack shared object.

Maintance Targets:
         clean => delete the binaries.
kali@kali:~$
```

## Basic Game Usage
Standard guessing game build and usage:
```
kali@kali:~$ make game
gcc -Wall -O3 -s src/guessing_game.c -o guessing_game
kali@kali:~$ ./guessing_game 

        ---===[ Number Guessing Game v1.0 ]===---

 [?] Guess a number between 0-31337 > 4444
 [-] You lose. :-(

kali@kali:~$
```

Building the debug build and usage:
```
kali@kali:~$ make game_debug
gcc -Wall -O3 -DDEBUG src/guessing_game.c -o guessing_game
kali@kali:~$ ./guessing_game 

        ---===[ Number Guessing Game v1.0 ]===---

 [?] Guess a number between 0-31337 > 4444
 [DEBUG] user_guess => 4444
 [DEBUG]   rand_num => 26148
 [-] You lose. :-(

kali@kali:~$
```

## Cheating By Hijacking Random with Our LD_PRELOAD
Using the LD_PRELOAD method to inject our shared object into the game to hijack rand() and always make it return 42:
```
kali@kali:~$ make
gcc -Wall -O3 -s src/guessing_game.c -o guessing_game
gcc -Wall -O3 -FPIC -shared src/rand_hijack.c -o rand_hijack.so
kali@kali:~$ ./guessing_game

        ---===[ Number Guessing Game v1.0 ]===---

 [?] Guess a number between 0-31337 > 42
 [-] You lose. :-(

kali@kali:~$ LD_PRELOAD=./rand_hijack.so ./guessing_game

        ---===[ Number Guessing Game v1.0 ]===---

 [?] Guess a number between 0-31337 > 42
 [+] You Win! :-)

kali@kali:~$ LD_PRELOAD=./rand_hijack.so ./guessing_game

        ---===[ Number Guessing Game v1.0 ]===---

 [?] Guess a number between 0-31337 > 42
 [+] You Win! :-)

kali@kali:~$ LD_PRELOAD=./rand_hijack.so ./guessing_game

        ---===[ Number Guessing Game v1.0 ]===---

 [?] Guess a number between 0-31337 > 42
 [+] You Win! :-)

kali@kali:~$
```
