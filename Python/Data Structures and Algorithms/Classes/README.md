# Object Oriented Programming in Python

## Name Mangling
Prevent accidental overwriting of attributes in a class by using double underscore before the attribute name.
It also works for methods.

Done by prefixing the attribute or method name with double underscore.

```python
class A:
    def __init__(self):
        self.__x = 10

