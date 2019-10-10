from cs50 import get_float

x = -1
while x < 0:
    x = get_float("Change owed: ")

coins = x // 0.25
x = round(x % 0.25,2)


coins += x //0.1
x = round(x % 0.1,2)


coins += x//0.05
x = round(x % 0.05,2)

coins += x // 0.01

print(int(coins))
# there's some iffy rounding in the script