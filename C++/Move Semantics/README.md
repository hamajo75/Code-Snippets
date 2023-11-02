# Move Semantics

Transfer ownership of resources from one object to another.

## Function Return Value
When a function returns an object it does so by value. In this case a copy of the object is created because the original object goes out of scope when leaving the function. If the object is big we would rather like to move the underlying object instead of copying it.