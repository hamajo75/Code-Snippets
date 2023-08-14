# Ranges and Views

## Views
Views provide a way to access and manipulate elements of a sequence without actually storing or copying the elements themselves. Views are lazy, meaning that they only perform computation when needed. Views are also composable, meaning that you can combine them to perform complex operations.

* Views do not own or store the elements themselves.
* Operations on views are lazy, meaning that they only perform computation when needed.

Types of views:

1. Transforming Views: These views apply a transformation or operation to the elements of a source range and provide a new view that presents the modified elements.

    Examples:

        std::views::transform
        std::views::filter
        std::views::take

2. Splitting and Joining Views: These views allow you to split a range into subranges or join multiple ranges together.

    Examples:

        std::views::split
        std::views::join
3. Common Views: These views provide common operations like slicing, reversing, and dropping elements from a range.

    Examples:

        std::views::take_while
        std::views::drop
        std::views::reverse

## Ranges
Ranges are sequences of objects that can be iterated over, i.e.
it makes sense to say what is the next and previous element in the range. Ranges are composable, meaning that you can combine them to perform complex operations.