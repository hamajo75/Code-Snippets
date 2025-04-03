# Syntax:
# lambda arg1, arg2: expression

get_pi = lambda: 3.14159
print(get_pi()) # Output: 3.14159

add = lambda x, y: x + y
print(add(3, 4)) # Output: 7

max_val = lambda a, b: a if a > b else b
print(max_val(10, 5)) # Output: 10
print(max_val(2, 8))  # Output: 8

# Using lambda with a list of tuples

# Using lambda with map()
numbers = [1, 2, 3, 4, 5]
squared_numbers = list(map(lambda x: x**2, numbers))
print(squared_numbers) # Output: [1, 4, 9, 16, 25]

# Using lambda with filter()
even_numbers = list(filter(lambda x: x % 2 == 0, numbers))
print(even_numbers) # Output: [2, 4]

# Using lambda with sorted() for a custom key
points = [(1, 5), (3, 2), (5, 8), (2, 1)]
# Sort points based on the second element (y-coordinate)
sorted_points = sorted(points, key=lambda point: point[1])
print(sorted_points) # Output: [(2, 1), (3, 2), (1, 5), (5, 8)]
