# Constructor and Destructor Order

Quick reference for the examples in this folder.

## Basics

Folder: `basics`

- Local objects are constructed in declaration order.
- Local objects are destroyed in reverse declaration order.
- For a single class, the constructor body runs before the object can be used.
- The destructor runs automatically when the object leaves scope.

## Inheritance

Folder: `Inheritance`

- Virtual base classes are constructed first.
- Then non-virtual base classes are constructed in the order written in the derived class declaration.
- Then member objects are constructed.
- Finally the derived class constructor body runs.
- Destruction is the exact reverse order.


## Composition

Folder: `Composition`

- Member objects are constructed before the containing object's constructor body.
- Members are constructed in declaration order.
- The initializer list does not change the construction order.
- Members are destroyed in reverse declaration order after the containing object's destructor body starts.


## Rules to Remember

- Construction goes from the most basic building blocks to the most derived object.
- Destruction always goes in reverse.
- For composition, declaration order controls member construction order.
- For inheritance, the base-specifier list controls base construction order.
