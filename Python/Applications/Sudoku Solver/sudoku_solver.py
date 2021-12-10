import numpy

#grid = [[5,3,0,0,7,0,0,0,0],
#        [6,0,0,1,9,5,0,0,0],
#        [0,9,8,0,0,0,0,6,0],
#        [8,0,0,0,6,0,0,0,3],
#        [4,0,0,8,0,3,0,0,1],
#        [7,0,0,0,2,0,0,0,6],
#        [0,6,0,0,0,0,2,8,0],
#        [0,0,0,4,1,9,0,0,5],
#        [0,0,0,0,8,0,0,7,9]]

grid = [[0,0,0,0,7,0,0,0,0],
         [6,0,0,1,9,5,0,0,0],
         [0,9,8,0,0,0,0,6,0],
         [8,0,0,0,6,0,0,0,3],
         [4,0,0,8,0,3,0,0,1],
         [7,0,0,0,2,0,0,0,6],
         [0,6,0,0,0,0,2,8,0],
         [0,0,0,4,1,9,0,0,5],
         [0,0,0,0,8,0,0,7,9]]

print(numpy.matrix(grid))

def possible(y,x,n):
        # check horizontal row
        for i in range(9):
                if grid[y][i] == n :
                        return False
        # check vertical column
        for i in range(9):
                if grid[i][x] == n :
                        return False
        # check box with coordinates (x0, y0)
        x0 = (x // 3) * 3
        y0 = (y // 3) * 3
        for i in range(3):
                for j in range(3):
                        if grid[y0 + i][x0 + j] == n:
                                return False
        return True

def solve():
        for y in range(9):
                for x in range(9):
                        if grid[y][x] == 0:
                                for n in range(1,10):
                                        if possible(y,x,n):
                                                grid[y][x] = n
                                                solve()         # A: if this is the way, we'll make it to print
                                                grid[y][x] = 0  # failed -> set back to 0
                                return
        print('Solution')
        print(numpy.matrix(grid))   # if there are multiple solutions we get here more than once (from A)

solve()