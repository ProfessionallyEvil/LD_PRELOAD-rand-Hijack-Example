/***********************************************************************
 * 
 * Project: rand_hijack.so
 * 
 * Author: Travis Phillips
 * 
 * Date: 10/24/2020
 * 
 * Project Repo:
 *  https://github.com/ProfessionallyEvil/LD_PRELOAD-rand-Hijack-Example
 * 
 * Purpose: This is simple code for a LD_PRELOAD shared object that
 *          will make the call to rand() always return a static value
 *          of 42. We will use this to cheat in the number guessing
 *          game by making it not-so-random anymore.
 * 
 * Compile: gcc -FPIC -shared rand_hijack.c -o rand_hijack.so
 * 
***********************************************************************/
#include <stdio.h>

// Our version of rand() to hijack random number generation with.
int rand(void) {
    return 42; // The answer is always 42. It's always 42...
}
