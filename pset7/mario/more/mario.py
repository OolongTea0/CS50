from cs50 import get_int

x = 0
while x < 1 or x > 8:
    x = get_int("Height: ")

for i in range(x):

    #Makes beginning spaces
    for j in range(x-(i+1)):
        print(" ", end="")

    #Creates first pyramid
    for j in range(i+1):
        print("#", end="")

    #Makes the space in the middle
    print(" ", end="")

    #Creates the second pyramid
    for j in range(i+1):
        print("#", end="")

    print("")