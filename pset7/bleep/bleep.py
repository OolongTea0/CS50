from cs50 import get_string
from sys import argv

words = set()

def main():

    if len(argv) == 2:
        file = open(argv[1], "r")
    else:
        print("Usage: python bleep.py dictionary")
        quit()

    #Loading
    for line in file:
        words.add(line.rstrip("\n"))
    file.close()

    #Getting message
    s = get_string("What message would you like to censor?\n")

    #Parse the message into words
    list = s.split(" ")
    for word in list:
        if (word.lower() in words):
            s = "*" * len(word)
            print(s, end=" ")
        else:
            print(word, end= " ")

    print()

if __name__ == "__main__":
    main()
