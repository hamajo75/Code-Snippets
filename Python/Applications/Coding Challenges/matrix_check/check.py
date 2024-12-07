#!/usr/bin/env python3

# Challenge
# Return true if all rows and all columns contain all integers
# from 1 to n, where n is the number of rows or columns.
# Otherwise, return false.

def is_valid_matrix(matrix):
    n = len(matrix)

    # Check rows
    for row in matrix:
        vector = list(range(1, n + 1))
        row.sort()
        if row != vector:
            return False

    return True

# Example usage:
matrix1 = [[1, 2, 3], [3, 1, 2], [2, 3, 1]]
print(is_valid_matrix(matrix1))  # Output: True

matrix2 = [[1, 1, 1], [1, 2, 3], [1, 2, 3]]
print(is_valid_matrix(matrix2))  # Output: False
