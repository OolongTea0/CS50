#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[]) {
    if (argc == 1){
        printf("Please input a key\n");
        return(1);
    }

    if (argc > 2) {
        printf("Too many keys inputted\n");
        return(1);
    }


    int x = strlen(argv[1]), y[x]; //x is key length, y is key converted into dec
    string s = argv[1]; //creating a new string for the key

    for (int i = 0; i < x; i++) { // Analyze key
        if (s[i] >= 'a' && s[i] <= 'z') {
            y[i] = s[i] - 'a';
        }
        else if (s[i] >= 'A' && s[i] <= 'Z') {
            y[i] = s[i] - 'A';
        }
        else {
            printf("Invalid Key\n");
            return(1);
        }
    } //This script is to check if the key is good or not

    string t = get_string("Plaintext: "); //grabs plaintext

    for (int i = 0, j = 0, n = strlen(t); i < n; i++) {

        if (t[i] >= 'a' && t[i] <= 'z') { //lower conversion
            t[i] = (t[i]- 'a' + y[j])%26 + 'a';
            j++; j = j%x;
        }

        if (t[i] >= 'A' && t[i] <= 'Z') { //upper conversion
            t[i] = (t[i]- 'A' + y[j])%26 + 'A';
            j++; j = j%x;
        }

    }
    printf("%s\n", t);

    return(0);
}