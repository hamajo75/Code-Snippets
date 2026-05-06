# Rust

## Set up Rust
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

    rustup update

## Cargo
Build system and package manager for Rust.
- Packages are called crates.
- build
- download dependencies
- build dependencies

- [crates.io](https://crates.io/) registry for Rust packages.

### Build and run an application

Create new project folder
    cargo new my_project

Inside project folder
    cargo run

## Macros
Macros allow you to do things that you couldn't do with functions:
- Generate or manipulate code (e.g. create a getter, serializing structs, etc.).
- Variadic arguments (e.g. println!()).
- Done at compile time (not runtime reflection).
- Create new syntax (domain-specific languages).

## Attributes
Attributes provide metadata about the code.

```rust
    #[test]  // This is an attribute, skip this function during normal compilation
    fn adds_two_numbers() {
        assert_eq!(2 + 2, 4);
    }
```

## Ownership
### Ownership Rules
1. Each value in Rust has a variable that’s called its owner.
2. There can only be one owner at a time.
3. When the owner goes out of scope, the value will be dropped.

### References and Borrowing
- A variable can borrow the ownership of a value.

### Resources
- [The Rust Programming Language](https://doc.rust-lang.org/book/)
- [Rust by Example](https://doc.rust-lang.org/rust-by-example/)
- [Rust by Practice](https://practice.course.rs/)