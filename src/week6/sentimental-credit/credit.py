# TODO
import sys

num = input("Number: ")


temp, sum, length = 0, 0, len(str(num))

if length != 13 and length != 15 and length != 16:
    print("INVALID")
    sys.exit()

isEvenPlace = True if length % 2 == 0 else False

for i in range(length):
    if isEvenPlace:
        temp = int(num[i])*2
        sum += (temp - 9) if temp >= 10 else temp
        isEvenPlace = False
    else:
        sum += int(num[i])
        isEvenPlace = True

answer = int(num[0])*10+int(num[1])

if sum % 10 == 0:
    if answer == 34 or answer == 37:
        print("AMEX")
    elif 51 <= answer <= 55:
        print("MASTERCARD")
    elif int(num[0]) == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
