import functools
import operator
'''
multiline comments
'''

# --------------------------------- Control Structures ----------------------------------
n = 0
if n < 0:
	print("true")
else:
	print("false")

for item in range(5):
	print(item)

counter = 0
while counter < 5:
	print("Buh")
	counter = counter + 1
# --------------------------------- Functions --------------------------------------
def fun():
    return 1,2

x,y = fun()
print('x is',x)
print('y is',y)
# --------------------------------- Datastructures --------------------------------------

# --- lists []        - mutable
# creating lists
l = [1, 2, 3, 4, 5]
l = list(range(1, 6))

# O(1)
l.append(6)			# append
l[2]					# index an element
l[2:5]
l.pop()				# pop last element

# O(n)
l.insert(1, 1.5)
l2 = [6, 7]
l3 = l + l2
l.__contains__(5)

# O dont know
l.extend(range(7,9))		# dont use append

# --- tuples ()        - immutable
t = (1, 2, 3, 4)

# --- dictionaries {}
d = {"key1" : "value1", "key2" : "value2", "key3" : "value3"}

# O(1)
d["key1"]

# --- deque
# --- set
s = set([1, 2, 3, 4])

# O(1)
s.add(5)
s.remove(5)

# --- common operations
len(s)
2 in s
s.clear()


# --------------------------------- Lambdas ---------------------------------------------
# default value
l = lambda x, y=5: x*y
print(l(2))

# n parameters
l = lambda *x: functools.reduce(operator.add, x)
print(l(1,2,3,4,5))

# --------------------------------- special Topics --------------------------------------

# measuring time
import timeit

# measure execution time of an operation
l = list(range(10000))
myTimer = timeit.Timer("l.pop(0)", "from __main__ import l")
myTimer2 = timeit.Timer("l.pop()", "from __main__ import l")
print("l.pop(0) takes", myTimer.timeit(number=1000), "ms")
print("l.pop() takes", myTimer2.timeit(number=1000), "ms")

# measure execution time of a function
def myfun():
	l = list(range(100000))
	l.insert(50000, 1)

myTimer = timeit.Timer("myfun()", "from __main__ import myfun")
print("myfun() takes", myTimer.timeit(number=100), "ms")							# number: execute 100 times
