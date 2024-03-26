from cs50 import get_int


def main():
    num = get_int("Number: ")

    if is_valid(num):
        if checksum(num):
            print(card_type(num))
        else:
            print("INVALID")
    else:
        print("INVALID")


def is_valid(num):
    if ((num > 340000000000000 and num < 350000000000000) or (num > 370000000000000 and num < 380000000000000) or
        (num > 4000000000000 and num < 5000000000000) or (num > 4000000000000000 and num < 5000000000000000) or
            (num > 5100000000000000 and num < 5600000000000000)):
        return True
    else:
        return False


def checksum(num):
    sum1 = sum2 = 0
    while True:
        if num <= 0:
            break
        sum2 += num % 10
        num //= 10
        if num % 10 * 2 > 9:
            temp = num % 10 * 2
            sum1 += temp % 10
            temp //= 10
            sum1 += temp % 10
        else:
            sum1 += num % 10 * 2
        num //= 10
    return (sum1 + sum2) % 10 == 0


def card_type(num):
    if (num > 340000000000000 and num < 350000000000000) or (num > 370000000000000 and num < 380000000000000):
        return "AMEX"
    if (num > 4000000000000 and num < 5000000000000) or (num > 4000000000000000 and num < 5000000000000000):
        return "VISA"
    if num > 5100000000000000 and num < 5600000000000000:
        return "MASTERCARD"
    return "INVALID"


main()
