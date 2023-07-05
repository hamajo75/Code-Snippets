#!/usr/bin/env python3

class Vehicle:
    def __init__(self, brand, color):
        self.brand = brand
        self.color = color

    def drive(self):
        print(f"The {self.color} {self.brand} is driving.")

class Car(Vehicle):
    def __init__(self, brand, color, num_doors):
        super().__init__(brand, color)
        self.num_doors = num_doors

    def honk(self):
        print(f"The {self.color} {self.brand} with {self.num_doors} doors is honking.")

class Motorbike(Vehicle):
    def __init__(self, brand, color):
        super().__init__(brand, color)

    def wheelie(self):
        print(f"The {self.color} {self.brand} is doing a wheelie.")

# Creating instances of derived classes
my_car = Car("Toyota", "blue", 4)
my_motorbike = Motorbike("Honda", "red")

# Accessing methods from the base class
my_car.drive()         # Output: The blue Toyota is driving.
my_motorbike.drive()   # Output: The red Honda is driving.

# Accessing methods specific to derived classes
my_car.honk()          # Output: The blue Toyota with 4 doors is honking.
my_motorbike.wheelie() # Output: The red Honda is doing a wheelie.
