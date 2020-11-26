import cs50

x = 0

while x < 1 or x > 8:
    x = cs50.get_int("Height: ")

# print j height (rows)
j = 1

while j <= x:
    # print x - j spaces
    for i in range(0, x - j):
        print(" ", end="")
    # print j bricks
    for g in range(0, j):
        print("#", end="")

    # print spacing between bricks
    print("  ", end="")

    # print j bricks
    for m in range(0, j):
        print("#", end="")

    # print for new row
    print("")

    # increment j
    j += 1