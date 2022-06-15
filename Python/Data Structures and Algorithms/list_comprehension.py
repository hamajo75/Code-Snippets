# list - sortable
print('- list')
# - list comprehension (cleverly create lists)
#   put a loop and some conditions inside []
x = [m for m in range(8)]
x = [z**2 for z in range(10) if z%2]  # 1, 3, 5, 7, 9 will be squared
print(x)