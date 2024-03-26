from cs50 import get_float

pen = 0

while True:
    num = get_float("Change owed: ") * 100
    if num >= 0:
        break

while True:
    if num <= 0:
        break
    if num >= 25:
        num -= 25
        pen += 1
    elif num >= 10:
        num -= 10
        pen += 1
    elif num >= 5:
        num -= 5
        pen += 1
    elif num >= 1:
        num -= 1
        pen += 1

print(pen)
