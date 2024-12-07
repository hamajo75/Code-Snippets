from dataclasses import dataclass, field
from typing import List

@dataclass
class Address:
    street: str
    city: str
    zip_code: str

@dataclass
class Employee:
    name: str
    age: int
    id: int = field(metadata={"help": "The unique identifier for an employee"})
    address: Address = field(default_factory=lambda: Address("Unknown", "Unknown", "00000"))
    skills: List[str] = field(default_factory=list)

address = Address("123 Main St", "Anytown", "12345")
employee = Employee(name="Jane Doe", age=28, id=1, address=address, skills=["Python", "Data Analysis"])
print(employee)

# Output:
# Employee(name='Jane Doe', age=28, id=1, address=Address(street='123 Main St', city='Anytown', zip_code='12345'), skills=['Python', 'Data Analysis'])


"""
Key Features
- Automatic __init__ Method:            Data classes automatically generate an __init__ method based on the class attributes.
- Automatic __repr__ Method:            A __repr__ method is automatically generated, providing a readable string representation of the class.
- Comparison Methods:                   Data classes automatically generate __eq__, __lt__, __le__, __gt__, and __ge__ methods for comparing instances.
- Mutable and Immutable Data Classes:   By default, data classes are mutable, but you can make them immutable by setting frozen=True.
- Default Values:                       You can provide default values for fields, including using dataclasses.field for more advanced options.
"""