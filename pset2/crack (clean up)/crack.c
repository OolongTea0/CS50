#include <stdio.h> //standard output library
#include <cs50.h>
#include <string.h>
#define salt "50"

//#define _XOPEN_SOURCE //used for crypt function
//#include <unistd.h>


//could be better

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


    while (x != 0 || i != 6) {

        if (x == 0){
            printf("pw: %s\n", pw);
            return(0);
        }

        pw[0] = pw[0] + 1;



        if (pw[0] == 'Z' + 1) { //convert Z to a
            pw[0] = 'a';
        }

        if (pw[0] == 'z' + 1) { //changes z to A and adds 1 to next element
            pw[0] = 'A';
            if (pw[1] == '\0'){
                pw[1] = 'A';
            }
            else
                pw[1] = pw[1] + 1;
         if (pw[1] == 'Z' + 1){
             pw[1] = 'a';
         }
        }

        if (pw[1] == 'z' + 1) { //changes z to A and adds 1 to next element
            pw[1] = 'A';
            if (pw[2] == '\0'){
                pw[2] = 'A';
            }
            else
                pw[2] = pw[2] + 1;
         if (pw[2] == 'Z' + 1){
             pw[2] = 'a';
         }
        }

        if (pw[2] == 'z' + 1) { //changes z to A and adds 1 to next element
            pw[2] = 'A';
            if (pw[3] == '\0'){
                pw[3] = 'A';
            }
            else
                pw[3] = pw[3] + 1;
         if (pw[3] == 'Z' + 1){
             pw[3] = 'a';
         }
        }

        if (pw[3] == 'z' + 1) { //changes z to A and adds 1 to next element
            pw[3] = 'A';
            if (pw[4] == '\0'){
                pw[4] = 'A';
            }
            else
                pw[4] = pw[4] + 1;
         if (pw[4] == 'Z' + 1){
             pw[4] = 'a';
         }
        }

        if (pw[4] == 'z' + 1) {
            break;
        }

        s = crypt(pw, salt);
        x = strcmp(s,argv[1]);

    }
        printf("s: %s\n", s);
        printf("argv: %s\n", argv[1]);

    return(0);
}