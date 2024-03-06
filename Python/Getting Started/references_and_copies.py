#!/usr/bin/python3

def print_address(v):
    print("address in memory:", id(v))

a = [1, 2, 3]
b = a                     # b is a reference to a
print_address(a)
print_address(b)

b[2] = 11

print("list a:", a)
print("list b:", b)

a = [1, 2, 3]

def func(input_list):
    input_list[2] = 13
    return input_list

b = func(a)
print("list a:", a)
print("list b:", b)