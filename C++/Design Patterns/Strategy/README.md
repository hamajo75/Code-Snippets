# Strategy Design Pattern

This repository contains an implementation of the Strategy design pattern in C++.

## Example (ChatGPT):
Sure! Imagine you have a class called "Robot" in your computer program. This class has a method (function) called "Move." Now, instead of putting the specific way the robot moves directly into the "Move" method, you create separate classes for different ways the robot can move. For example, you might have classes like "WalkStrategy," "RollStrategy," and "HopStrategy."

Now, your "Robot" class doesn't decide how to move on its own. Instead, it has a variable that points to one of these strategy classes. So, when you want the robot to move, you just call the "Move" method, and it uses the strategy class it's currently pointing to. If you want the robot to move differently, you can switch the strategy class without changing the Robot class itself. It's like changing the tool your robot uses for moving without changing how the robot is built.

## Class Diagram

![Class Diagram](class_diagram.png)
