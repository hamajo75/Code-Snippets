# Object Oriented Programming in Python

## Class attributes vs. Instance attributes
- Class attributes are shared among all instances of a class.
- Instance attributes are unique to each instance of a class.




## Name Mangling
Prevent accidental overwriting of attributes in a class by using double underscore before the attribute name.
It also works for methods.

Done by prefixing the attribute or method name with double underscore.

```python
class A:
    def __init__(self):
        self.__x = 10
```

## When to use classes?
Bundling date and methods (behavior) together.


When to NOT use classes?
- When you only store data. Use `data class` instead.