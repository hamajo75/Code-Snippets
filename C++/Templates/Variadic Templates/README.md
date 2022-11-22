# How to pass n arguments of arbitrary type to a function?

- C-style vargs
- Initializer list with `std::any`
- `std::tuple`
- Variadic Templates

## Parameter pack
T ... pack_name

// ...args   pack
// args...   unpack

When unpacking the compiler will insert the actual parameters and create additional functions
as needed.

Pack expansion is conceptually equivalent to having one copy of the pattern for each element of the parameter pack.