# Rust

## Cargo
Build system and package manager for Rust.
- Packages are called crates.
- build
- download dependencies
- build dependencies


### Build and run an application
    cargo new my_project
    cargo run main.rs


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