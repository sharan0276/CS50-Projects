from cs50 import get_int

while True:
    rows = get_int("Height :")
    if rows > 0 and rows < 9:
        break

space = rows - 1

for i in range(rows):
    print(" " * space, end="")
    for j in range(i + 1):
        print("#", end="")
    print()
    space -= 1

