// This is a comment, these are ignored by the compiler

/// Preprocessor statement using `#` symbol
/// The preprocessor runs at compile time before the code is compiled
/// `#include` copies the header `iostream` into the current file
#include <iostream>

/// Main function
/// Entry point of the executable.
/// Takes no arguments and returns an `int`.
auto main () -> int
{
    /// From the namespace `std`.
    /// Use `cout` (character out).
    /// Put (<<) the string literal to stream.
    /// From `std` put a `endl` specifier. 
    std::cout << "Hello World!" << std::endl;

    /// Return 0 on successful termination.
    return 0;
}
