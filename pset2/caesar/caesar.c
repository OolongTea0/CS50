#include  <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{

    if (argc == 1) {  //If no arg is inputted
        printf("Please input a key\n");
        return(1);
    }

    if (argc > 2) { //If too much args are inputted
        printf("This program only needs 1 key\n");
        return(1);
    }


    if (argc == 2) {
        int x = atoi(argv[1]);
        if (x < 0){
            printf("Key must be a non-negative integer\n");
            return (1);
        }

        string s = get_string("plaintext: ");

        for (int i = 0, n = strlen(s); i < n; i++){ //Analyze each letter of string
            if (s[i] >= 'a' && s[i] <= 'z'){
                s[i] = (s[i] + x - 'a')%26 + 'a'; //encrpyts lower case letters
            }

            if (s[i] >= 'A' && s[i] <= 'Z'){ //encrypts upper case chars
                s[i] = (s[i] + x - 'A')%26 + 'A';
            }
        }
        printf("Cryptotext: %s\n", s);
    }

    return (0);
}