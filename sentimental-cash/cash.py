# get the input
n = -2
while n <= 0:
    try:
        n = float(input('Change owed: '))
    except:
        n = -1

# available cins 25 10 5 1
n = n * 100
count = 0
for i in [25, 10, 5, 1]:
    count = count + int(n / i)
    n = n - i * int(n / i)

print(count)
