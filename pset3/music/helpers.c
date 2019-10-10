// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int num = fraction[0] - '0'; //ASCII symbol before 0
    int den = fraction[2] - '0';

    int dur = num * 8/den; // Converts fractions into eights

    return(dur);
    // TODO
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int freq, oct, key, accent = 0;

    if (note[0] == 'A' || note[0] == 'B')
    {
        key = note[0] + 'H' - 'A'; //converts A and B to H and I in ASCII for simpler math
    }
    else
        key = note[0];

    if (key >= 'F')  //influence of the note on the frequency
    {
        key = (key - 'C') * 2 - 1;
    }
    else
        key = (key - 'C') * 2;

    if (strlen(note) == 2)
    {
        oct = (note[1] - '4') * 12; //octave influence
    }

    if (strlen(note) == 3)
    {
        if (note[1] == 'b') //flat influence
        {
            accent = -1;
        }
        else
            if(note[1] == '#') //sharp influence
            {
                accent = 1;
            }
        oct = (note[2] - '4') * 12; //octave influence for acc
    }

    double n = (key-9) + oct + accent;

    freq = round(pow(2,n/12) * 440); //If C is 0, A is 9


    return(freq);
    // TODO
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0')
        return(1);
    else
        return(0);
    // TODO
}
