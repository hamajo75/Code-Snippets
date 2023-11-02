#!/bin/python3

def is_valid(board, row, col, num):
    # Check if the number is not in the same row or column
    for i in range(9):
        if board[row][i] == num or board[i][col] == num:
            return False

    # Check if the number is not in the same 3x3 subgrid
    start_row, start_col = 3 * (row // 3), 3 * (col // 3)
    for i in range(start_row, start_row + 3):
        for j in range(start_col, start_col + 3):
            if board[i][j] == num:
                return False

    return True

def solve_sudoku(board):
    for row in range(9):
        for col in range(9):
            if board[row][col] == 0:
                for num in range(1, 10):
                    if is_valid(board, row, col, num):
                        board[row][col] = num
                        if solve_sudoku(board):
                            return True
                        board[row][col] = 0
                return False
    return True

def print_board(board):
    for row in board:
        print(" ".join(map(str, row)))

if __name__ == "__main__":
    # Example Sudoku puzzle (0 represents empty cells)
    puzzle = [
        [0, 0, 6, 0, 0, 1, 0, 0, 7],
        [3, 0, 5, 7, 6, 0, 0, 0, 0],
        [2, 0, 8, 0, 5, 0, 0, 0, 0],
        [6, 0, 9, 0, 0, 0, 0, 7, 0],
        [0, 0, 0, 0, 0, 3, 0, 0, 9],
        [7, 0, 0, 2, 0, 8, 5, 0, 1],
        [0, 0, 0, 5, 1, 7, 0, 0, 0],
        [1, 0, 0, 0, 0, 6, 7, 0, 5],
        [0, 3, 0, 0, 2, 0, 0, 9, 0]
    ]

    if solve_sudoku(puzzle):
        print("Sudoku solution:")
        print_board(puzzle)
    else:
        print("No solution exists for the given Sudoku puzzle.")


