# get the input
n = -2
while n <= 0:
    try:
        n = int(input('Change owed: '))
    except:
        n = -1
# print(n)
# Luhn’s Algorithm
test = n
i = 0
s = 0
while test != 0:
    if i % 2 == 0:
        s = s + test % 10
    else:
        j = (test % 10) * 2
        if len(str(j)) == 1:
            s = s + j
        else:
            s = s + j % 10 + int(j / 10)
    test = int(test / 10)
    i = i + 1

# print(s % 10)
if s % 10 != 0:
    print('INVALID')
else:
    begin = int(str(n)[0:2])
    if len(str(n)) == 15 and (begin == 34 or begin == 37):
        print("AMEX")
    elif len(str(n)) == 16 and (begin == 51 or begin == 52 or begin == 53 or begin == 54 or begin == 55):
        print('MASTERCARD')
    elif (len(str(n)) == 13 or len(str(n)) == 16) and int(str(n)[0]) == 4:
        print('VISA')
    else:
        print('INVALID')


