#!/usr/bin/env python3

# Challenge:
# Given two strings of equal length. Return true if at most one
# character swap can make the strings equal, otherwise return false.

def is_swappable(s1 : str, s2 : str) -> bool:
    if s1 == s2:
        return True

    idx_1 = -1
    idx_2 = -1
    count = 0
    for i in range(len(s1)):
        if s1[i] != s2[i]:
            if idx_2 == -1 and idx_1 != -1:
                idx_2 = i
            if idx_1 == -1:
                idx_1 = i
            count = count + 1
    if count != 2:
        return False

    if s1[idx_1] == s2 [idx_2] and s1[idx_2] == s2[idx_1]:
        return True

    return False

print(is_swappable("abc", "abc"))  # Output: True
print(is_swappable("abc", "cba"))  # Output: True
print(is_swappable("abcd", "1234"))  # Output: False
print(is_swappable("night", "tighn"))  # Output: True