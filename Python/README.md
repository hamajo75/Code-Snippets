# Python

## Hot topics
- [Decorators](Decorators/decorators.py)
- [List Comprehension](Data%20Structures%20and%20Algorithms/list_comprehension.py)

## Memory Model
- https://www.teach.cs.toronto.edu/~csc110y/fall/notes/06-memory-model/04-python-memory-model-1.html

Notes:
- Each object has a type, an id and a value.
- Evaluating an expression produces an object and a reference to the object (id).
- You can get an objects id with the `id()` function.
- Assignment: Evaluation of the right-hand side expression and store the id in the left-hand side variable.
- An instance of a complex data type actually stores references to the underlying objects.

## Virtual Environment
An isolated environment that allows you to manage dependencies for different projects separately. 

Create a Virtual Environment:

    python3 -m venv myenv

This will create a folder `myenv`. 

Activate a Virtual Environment:

    source myenv/bin/activate

Command prompt will change to indicate you are in the new VE. Now you can install packages here.   

Deactivate a Virtual Environment:

    deactivate

## Setuptools
For packaging an application.    
- https://setuptools.readthedocs.io/en/latest/setuptools.html