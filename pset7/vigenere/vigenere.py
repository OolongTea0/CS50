from sys import argv
from cs50 import get_string

key = []
news=[]

if len(argv) != 2:
    print("Usage: python vigenere.py keyword")
    quit()
else:
    k  = argv[1]

#converts letters into numbers
def code(c):
    if c.islower() == True:
        n = ord(c) - ord('a')
    else:
        n = ord(c) - ord('A')
    return(n)

#Creates new string using old string + key
def mod(c,i,key):
    ind = i%len(key)
    c = chr(ord(c) + key[ind])
    return(c)

#key conversion
for c in k:
    key.append(code(c))

s = get_string("plaintext: ")

#Traverses string and makes a new list with applied key
i = 0
for c in s:
    if c.isalpha() == True:
        news.append(mod(c,i,key))
        i+=1
    else:
        news.append(c)

#Prints new string after joining together
print("".join(news))