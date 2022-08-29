# A decorator wraps around another function and adds some
# functionality to it.

def print_it(func):
    print(func())

def get_string():
    return "Text"

# 1. step: we want to do something like this:
# print_it(get_string)


# this is what a decorator does:
# get_string = print_it(get_string)
# get_string() # error: get_string is not callable, it's not that easy
# we can make it callable, like this:
def print_it_callable(func):
    def wrapper():
        print("decorated: " + func())
    return wrapper

get_string = print_it_callable(get_string)
get_string()

# with syntactic sugar
@print_it_callable
def get_string_():
  return "Text"

get_string_()
# --------- more complicated----------------------
# decorator function
def do_twice(func):
    def wrapper_do_twice(*args, **kwargs):
        func(*args, **kwargs)
        func(*args, **kwargs)
    return wrapper_do_twice

@do_twice
def greet(name):
    print(f"Hello {name}")

greet("World")
