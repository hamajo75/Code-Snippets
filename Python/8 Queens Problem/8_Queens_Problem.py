import numpy

grid =  [[0,0,0,0,0,0,0,0],
         [0,0,0,0,0,0,0,0],
         [0,0,0,0,0,0,0,0],
         [0,0,0,0,0,0,0,0],
         [0,0,0,0,0,0,0,0],
         [0,0,0,0,0,0,0,0],
         [0,0,0,0,0,0,0,0],
         [0,0,0,0,0,0,0,0]]

print(numpy.matrix(grid))

def possible(y,x):
    # check horizontal row
    for i in range(8):
        if grid[y][i] == 1:
            return False

    # check vertical column
    for i in range(8):
        if grid[i][x] == 1:
            return False

    # check diagonals

    return True

def solve():
    for y in range(8):
        for x in range(8):
            if grid[y][x] == 0:
                if possible(y,x):
                    grid[y][x] = 1
                    solve()         # A: if this is the way, we'll make it to print
                    grid[y][x] = 0  # failed -> set back to 0
                return
            
    print('Solution')
    print(numpy.matrix(grid))   # if there are multiple solutions we get here more than once (from A)

solve()