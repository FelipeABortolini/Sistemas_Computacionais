use std::sync::{Arc, Mutex};
use std::thread;

fn inc_x(x_ptr: Arc<Mutex<i32>>) {
    let mut x = x_ptr.lock().unwrap();
    while *x < 100 {
        *x += 1;
    }
    drop(x); // Release the lock explicitly
    println!("x increment finished");
}

fn main() {
    let x = Arc::new(Mutex::new(0));
    let mut y = 0;

    println!("x: {}, y: {}", *x.lock().unwrap(), y);

    let x_clone = Arc::clone(&x);
    let inc_x_thread = thread::spawn(move || {
        inc_x(x_clone);
    });

    while y < 100 {
        y += 1;
    }

    println!("y increment finished");

    inc_x_thread.join().expect("Error joining thread");

    println!("x: {}, y: {}", *x.lock().unwrap(), y);
}