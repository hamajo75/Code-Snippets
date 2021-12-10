class MyClass:
  print("this statement will be executed at instantiation")
  name = "static variable, all objects"

  def __init__(self, realpart, imagpart):                   # constructur
    self.r = realpart
    self.i = imagpart

  def myfun(self, text):
    print(text)

# Instatiation
x = MyClass(1, 2)
print("r:", x.r, ", i:", x.i)
x.myfun("hello")

