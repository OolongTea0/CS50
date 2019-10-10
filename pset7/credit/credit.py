from cs50 import get_int

#num is untouched version of input, sum is for algorithm and count is digit counter
num = sum = count = 0
while num <= 0:
    num = get_int("Number: ")

n = num

while n != 0:

    x = n%10 #takes right most digit
    if count%2 == 1: #if 0 implies 1st,3rd,5th... digit
        x = x*2
    if x >= 10:
        x = x%10 + x//10

    sum += x

    n = n//10
    count += 1


if sum%10 == 0: #passes the algorithm
    if count == 13:
        y = num//(10**(count-1))
        if y == 4:
            print("VISA")
        else:
            print("INVALID")

    elif count == 15:
        y = num//(10**(count-2))
        if y==34 or y==37:
            print("AMEX")
        else:
            print("INVALID")

    elif count == 16:
        y = num//(10**(count-2))
        if y >= 51 and y <= 55:
            print("MASTERCARD")
        elif y//10 == 4:
            print("VISA")
        else:
            print("INVALID")

    else:
        print("INVALID")
else:
    print("INVALID") #if num doesn't pass Luhn's algorithm