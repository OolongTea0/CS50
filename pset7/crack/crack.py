import sys
import crypt
from cs50 import get_string

def lowup(y):
    if y <= 25:
        c = chr(ord("a") + y)
    else:
        c = chr(ord("A") + y - 26)
    return(c)

def numtostr(count, i):

    y1 = count%52
    c1 = lowup(y1)

    #calculates letters
    if i >= 2:
        y2 = (count//52)%52
        c2 = lowup(y2)
    if i >=3:
        y3 = (count//(52**2))%52
        c3 = lowup(y3)
    if i>=4:
        y4 = (count//(52**3))%52
        c4 = lowup(y4)
    if i>=5:
        y5 = (count//(52**4))%52
        c5 = lowup(y5)

    #Joins characters into str, switch
    if i == 1:
        pw = c1
    if i == 2:
        pw = c2+c1
    if i == 3:
        pw = c3+c2+c1
    if i == 4:
        pw = c4+c3+c2+c1
    if i == 5:
        pw = c5+c4+c3+c2+c1

    return(pw)

def digit(count,i):
    i = count//(52**i) + i
    return (i)


if len(sys.argv) != 2:
    sys.exit("Usage: python crack.py hash")

hash = sys.argv[1]

count = 0
i = 1 #number of "digits"

pw = numtostr(count,i)
salt = hash[0] + hash[1]

#print(crypt.crypt("LOL", salt))
while (crypt.crypt(pw, salt) != hash):

    #print(pw)
    count += 1
    i = digit(count,i)
    pw = numtostr(count,i)

    if i == 6:
        sys.exit("INVALID")
print(pw)