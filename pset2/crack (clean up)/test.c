#include <stdio.h> //standard output library
#include <cs50.h>
#include <string.h>
#define salt "50"

//#define _XOPEN_SOURCE //used for crypt function
//#include <unistd.h>

#define _GNU_SOURCE
#include <crypt.h>

int main (int argc, string argv[]) { //Arguement is pw for testing purposes



    if (argc == 1) {
        printf("Please enter arguement\n");
        return(1);
    }

    if (argc > 2) {
        printf ("Too many inputs\n");
        return(1);
    }

    string s = crypt(argv[1], salt);
    printf("s: %s\n", s);./



    return(0);
}