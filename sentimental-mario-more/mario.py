from cs50 import get_int

while True:
    num = get_int("Height: ")
    if num > 0 and num < 9:
        break

for i in range(1, num + 1):
    j = num - i
    for k in range(0, num):
        if k >= j:
            print("#", end="")
            if k == num - 1:
                print("  ", end="")
                print("#" * i)
        else:
            print(" ", end="")
