# get the input and check if it is a number betwin 1 and 8
n = -2
while n <= 0 or n >= 9:
    try:
        n = int(input('Height: '))
    except:
        n = -1
# starting the loop to print
i = n
while i != 0:
    j = i - 1
    k = i - 1
    while j != 0:
        print(' ', end="")
        j = j - 1
    while k != n:
        print('#', end="")
        k = k + 1
    
    print("  ", end="")
    k = i - 1
    while k != n:
        print('#', end="")
        k = k + 1

    i = i - 1
    print("")
