# general: can mix datatypes
x = list(['a', 25, 8.43, [1, 2, 3]])

# sequence types
print('- sequence types: string, list, tuple')
# - slicing
s = 'Computer'
print(s[0:3])
print(s[3:])
print(s[:3])
print(s[-1])
print(s[0:6:2]) # step = 2
# - check membership
print('m' in s)
print('m' not in s)
# - index & item
print('index of p: ' + str(s.index('p')))

for index, item in enumerate(s):
   print(index, item)

print('Length: ' + str(len(s)))

# - unpacking
x = ['pig', 'cow', 'horse']
a, b, c = x

# list - sortable
print('- list')
# - list comprehension (cleverly create lists)
#   put a loop and some conditions inside []
x = [m for m in range(8)]
x = [z**2 for z in range(10) if z%2]  # 1, 3, 5, 7, 9 will be squared
print(x)

x.insert(1, ['a', 'm'])  # position 1
print(x.pop(1))

# tuple
print('- tuple: immutable')
x = (1, 2, 3) # also 1, 2, 3 without () is possible

# set
print('- set: unique elements, unordered')
set1 = {1, 2, 3, 4}

# - set comprehension
set2 = {3*n for n in range(4) if n>0}
print(set2)

print(set1 & set2)  # intersection AND
print(set1 | set2)  # union OR
print(set1 ^ set2)  # symmetric difference XOR
print(set1 - set2)  # difference
print(set1 <= set2) # is subset?
print(set1 >= set2) # is superset?

# hashmaps aka dictionary - unordered
print('- dictionary')

x = {'pork': 20.5, 'beef': 33.8, 'chicken': 15.7}

print(x['pork'])
print(x.keys())
print(x.values())
print(x.items())