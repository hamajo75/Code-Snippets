#!/usr/bin/env python3


class Executor:
    print("this statement will be executed at instantiation")
    name = "static variable, all objects"

    def __init__(self, realpart, imagpart):  # ctor
        self.r = realpart
        self.i = imagpart

    def __del__(self):
        print("destructor called when garbage collected")

    def __call__(self, cmd):
        print("calling " + cmd)

    def myfun(self, text):
        print(text)


# Instantiation
x = Executor(1, 2)

x("cmd")

print("r:", x.r, ", i:", x.i)
x.myfun("hello")
