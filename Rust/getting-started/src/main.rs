fn use_vector() {
    let my_vector: Vec<i32> = vec![1, 2, 3, 4, 5];
    for i in my_vector {
        println!("{}", i);
    }
}

#[allow(unused_variables)]  // compiler warning suppression
fn use_variables() {
    let _uninit : i32;      // uninitialized variable: error if used, warning if not used (avoid with "_")
    let x : i32 = 5;        // immutable variable (default), type annotation is optional
    let mut y = 10;         // mutable variable
    assert_eq!(x, 5);

    println!("x = {}, y = {}", x, y);
    y += 15;
    println!("x = {}, y = {}", x, y);

    // shadowing (redefining a variable with the same name and different type)
    let x = "hello";
    println!("x = {}", x);

    println!("Type of x: {}", type_of(&x));
}

#[allow(unused_assignments)]  // compiler warning suppression
fn use_datatypes() {
    let (a, b) = (1, 2);    // tuple destructuring

    let (x, y);
    (x,..) = (3, 4);
    [.., y] = [1, 2];       // array destructuring

    use_vector();
}

// Get the type of given variable, return a string representation of the type  , e.g "i8", "u8", "i32", "u32"
fn type_of<T>(_: &T) -> String {
    format!("{}", std::any::type_name::<T>())
}

fn main() {
    println!("Hello, world!");   // <X>! is a macro (will be expanded to code)
    use_variables();
    use_datatypes();
}
