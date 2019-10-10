#include <stdio.h> //standard output library
#include <cs50.h>
#include <string.h>
#define salt "50"

//#define _XOPEN_SOURCE //used for crypt function
//#include <unistd.h>

#define _GNU_SOURCE
#include <crypt.h>

int main (int argc, string argv[]) { //Arguement is pw for testing purposes

    char pw[6]; pw[0] = 'A'; pw[5] = '\0';
    int i = 1;

    if (argc == 1) {
        printf("Please enter arguement\n");
        return(1);
    }

    if (argc > 2) {
        printf ("Too many inputs\n");
        return(1);
    }

    string s = crypt(pw, salt);
    int x = strcmp(s, argv[1]);
    int count = 0;
    int y1 = 0; y2 = 0; y3 = 0; y4 = 0; y5 = 0;

    while (x != 0 || i != 6) {

        if (x == 0){
            printf("pw: %s\n", pw);
            return(0);
        }

        y1 = count%52;
        y2 = count%(52*52);
        y3 = count%(52*52*52);
        y4 = count%(52*52*52*52);
        y5 = count%(52*52*52*52*52);
        count++;



        s = crypt(pw, salt);
        x = strcmp(s,argv[1]);

    }
        printf("s: %s\n", s);
        printf("argv: %s\n", argv[1]);

    return(0);
}