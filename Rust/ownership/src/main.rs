
fn main() {
    println!("=== Rust Ownership Examples ===\n");

    // Example 1: Ownership Transfer (Move)
    println!("1. Ownership Transfer:");
    let s1 = String::from("hello");
    let s2 = s1; // s1 is moved to s2, s1 is no longer valid
    // println!("{}", s1); // This would cause a compile error!
    println!("s2 = {}", s2);
    println!();

    // Example 2: Borrowing (Immutable Reference)
    println!("2. Borrowing (Immutable Reference):");
    let s3 = String::from("world");
    let len = calculate_length(&s3); // We borrow s3, ownership stays with s3
    println!("The length of '{}' is {}.", s3, len); // s3 is still valid!
    println!();

    // Example 3: Mutable Borrowing
    println!("3. Mutable Borrowing:");
    let mut s4 = String::from("hello");
    change_string(&mut s4); // Mutable borrow
    println!("s4 after change: {}", s4);
    println!();

    // Example 4: Stack vs Heap
    println!("4. Stack vs Heap (Copy vs Move):");
    let x = 5;
    let y = x; // Copy (because i32 implements Copy trait)
    println!("x = {}, y = {}", x, y); // Both are valid!
    
    let s5 = String::from("hello");
    let s6 = s5; // Move (String doesn't implement Copy)
    // println!("{}", s5); // Error! s5 was moved
    println!("s6 = {}", s6);
    println!();

    // Example 5: Multiple Immutable References
    println!("5. Multiple Immutable References:");
    let s7 = String::from("hello");
    let r1 = &s7;
    let r2 = &s7; // Multiple immutable references are OK
    println!("r1 = {}, r2 = {}", r1, r2);
    println!();

    // Example 6: Mutable Reference Rules
    println!("6. Mutable Reference Rules:");
    let mut s8 = String::from("hello");
    let r1 = &mut s8;
    // let r2 = &mut s8; // Error! Can't have two mutable references
    // let r3 = &s8; // Error! Can't have mutable and immutable references
    println!("r1 = {}", r1);
    println!();
}

// Borrowing: takes a reference, doesn't take ownership
fn calculate_length(s: &String) -> usize {
    s.len()
} // s goes out of scope, but nothing is dropped because we only had a reference

// Mutable borrowing: can modify the value through the reference
fn change_string(s: &mut String) {
    s.push_str(", world");
}
