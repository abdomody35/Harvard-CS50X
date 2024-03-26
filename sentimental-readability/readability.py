from cs50 import get_string
from string import punctuation


def main():
    txt = get_string("Text: ")
    grade = round(get_grade(txt))
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def get_grade(txt):
    length = len(txt)
    L = S = W = 0
    for i in range(0, length):
        if txt[i].isalnum():
            L += 1
        elif txt[i] in punctuation:
            if txt[i] == '.' or txt[i] == '?' or txt[i] == '!':
                S += 1
        elif txt[i].isspace():
            W += 1
    W += 1
    L = L / W * 100
    S = S / W * 100
    return 0.0588 * L - 0.296 * S - 15.8


main()
