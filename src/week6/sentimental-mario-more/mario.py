# TODO

height =0
while True:
    try:
        height = int(input("Height: "))
        if 1<=height<=8:
            break
    except ValueError:
        print("Please type in an integer")

for i in range(1,height+1):
    for j in range(height+1-i,1,-1):
        print(" ",end="")
    for j in range(i):
        print("#",end="")
    print("  ",end="")
    for j in range(i):
        print("#",end="")
    print("")

