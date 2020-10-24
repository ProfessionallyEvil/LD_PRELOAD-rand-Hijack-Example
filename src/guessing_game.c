/***********************************************************************
 * 
 * Project: guessing_game
 * 
 * Author: Travis Phillips
 * 
 * Date: 10/24/2020
 * 
 * Project Repo:
 *  https://github.com/ProfessionallyEvil/LD_PRELOAD-rand-Hijack-Example
 * 
 * Purpose: This is code for a simple random number guessing game for
 *          a blog post on using LD_PRELOAD to hijack functions in an
 *          application, in this case, hijacking rand()
 * 
 * Compile: gcc guessing_game.c -o guessing_game
 * 
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/////////////////////////////////
// App Constants
/////////////////////////////////
const char *TITLE = "Number Guessing Game";
const char *VER = "v1.0";

/////////////////////////////////
// Color Constants
/////////////////////////////////
#ifdef NOCOLOR
    const char *RED = "";
    const char *GREEN = "";
    const char *YELLOW = "";
    const char *NC = "";
#else
    const char *RED = "\033[31;1m";
    const char *GREEN = "\033[32;1m";
    const char *YELLOW = "\033[33;1m";
    const char *NC = "\033[0m";
#endif

int main(int argc, char **argv) {
    
    //////////////////////////////////////////////////////////////////
    // Initalize Variables.
    //////////////////////////////////////////////////////////////////
    unsigned int rand_num = 0;
    unsigned int user_guess = 0;
    time_t t = 0;

    //////////////////////////////////////////////////////////////////
    // Print the banner.
    //////////////////////////////////////////////////////////////////
    printf("\n\t%s---===[ %s %s ]===---%s\n\n", YELLOW, TITLE, VER, NC);

    //////////////////////////////////////////////////////////////////
    // Get the user's guess.
    //////////////////////////////////////////////////////////////////
    printf(" [?] Guess a number between 0-31337 > ");
    if (!scanf("%u", &user_guess) || user_guess > 31337) {
        printf(" [%s!%s] %sERROR:%s Invalid input.\n\n", RED, NC, RED, NC);
        return 1;
    }
    

    //////////////////////////////////////////////////////////////////
    // Seed the random number generator with the current time.
    //////////////////////////////////////////////////////////////////
    srand((unsigned int) time(&t));

    //////////////////////////////////////////////////////////////////
    // Now get a random number between 1 and 31337.
    //////////////////////////////////////////////////////////////////
    rand_num = rand() % 31338;
    
    //////////////////////////////////////////////////////////////////
    // Print the variables if this is a debug build.
    //////////////////////////////////////////////////////////////////
    #ifdef DEBUG
        printf(" [DEBUG] user_guess => %d\n", user_guess);
        printf(" [DEBUG]   rand_num => %d\n", rand_num);
    #endif

    //////////////////////////////////////////////////////////////////
    // See if the users number is equal to the number generated. If
    // so, let the user know they won.
    //////////////////////////////////////////////////////////////////
    if (user_guess == rand_num){
        printf(" [%s+%s] %sYou Win! :-)%s\n\n", GREEN, NC, GREEN, NC);
        return 0;
    }
    
    //////////////////////////////////////////////////////////////////
    //      The user guessed wrong, let them know the lost.
    //////////////////////////////////////////////////////////////////
    printf(" [%s-%s] %sYou lose. :-(%s\n\n", RED, NC, RED, NC);
    return 1;
}
