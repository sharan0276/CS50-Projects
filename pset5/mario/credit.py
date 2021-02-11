import re
from sys import exit
from cs50 import get_int


def split(val):
    sum = 0
    while val > 0:
        sum += (val % 10)
        val = val // 10
    return sum


def luhn(credit):
    cred = str(credit)

    max = len(cred)

    max -= 2
    sum = 0
    for i in range(max, -1, -2):
        val = cred[i]
        value = int(val) * 2
        if value > 9:
            sum += split(value)
        else:
            sum += value

    for i in range(max + 1, -1, -2):
        value = int(cred[i])
        sum += value

    if sum % 10 == 0:
        return 1

    return 0


credit = get_int("Number :")
# luhn(credit)

valid = luhn(credit)

if valid == 0:
    print("INVALID")
    exit(1)

credit = str(credit)

if len(credit) == 15:
    if re.search("[34.*| 37.*]", credit):
        print("AMEX")

elif len(credit) == 16:
    if re.search("5[1|2|3|4|5].*", credit):
        print("MASTERCARD")

    elif re.search("4.*", credit):
        print("VISA")

elif len(credit) == 13:
    if re.search("4.*", credit):
        print("VISA")