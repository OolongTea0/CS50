from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    c = []

    a = a.split("\n")
    b = b.split("\n")

    for x in a:
        for y in b:
            if x == y: #Checks to see if item in both lists matches
                if not x in c: #Removes duplicates
                    c.append(x) #Adds to new list
    return (c)


def sentences(a, b):
    """Return sentences in both a and b"""
    c = [] #Declare list

    a = sent_tokenize(a)
    b = sent_tokenize(b)

    for x in a:
        for y in b:
            if x == y:
                if not x in c:
                    c.append(x)
    return (c)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    c = []
    suba = []
    subb = []

    for i in range(len(a)):
        if i+n <= len(a):
            suba.append(a[i:i+n])

    for i in range(len(b)):
        if i+n <= len(b):
            subb.append(b[i:i+n])

    for x in suba:
        for y in subb:
            if x == y:
                if not x in c:
                    c.append(x)
    return (c)
