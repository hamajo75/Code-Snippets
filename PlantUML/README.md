# Plant UML

Play around online: [www.plantuml](www.plantuml)

## VS Code
Use the Rich PlantUML Extension.

Dependencies:
- Java
- GraphViz

      apt install default-jdk graphviz

## Class Diagram

By default an element is a class.

Other elements are:

- Interface: `interface MyInterface`
- Abstract: `MyAbstractClass`
- Entity: `entity MyEntity`

Relationships between classes:

- Inheritance: `--|>`
- Composition: `--*`
- Aggregation: `--o`

## Comments
    ' This is also a single-line comment

    /' This is a
    multi-line
    comment '/

## Themes

Just add: `!theme spacelab`

- spacelab
- blueprint