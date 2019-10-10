from cs50 import get_string
import sys

def code(c,k):
    k = k%26 + ord(c)

    if c.islower() == True:
        if k < ord('a'):
            k = k + 26

        if k > ord('z'):
            k = k - 26

    else:
        if k < ord("A"):
            k = k + 26

        if k > ord("Z"):
            k = k - 26

    c = chr(k)
    return(c)


if len(sys.argv) != 2:
    sys.exit("Usage: python caesar.py k")

k = int(sys.argv[1])

s = get_string("plaintext: ")

print("ciphertext: ", end="")

for c in s:
    if c.isalpha() == True:
        c = code(c,k)
    print(c, end="")

print()