# Advanced Functions

## Contents

- [Advanced Functions](#advanced-functions)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : Function Structure](#task-11--function-structure)
      - [Task 1.1.1 : No exception optimization](#task-111--no-exception-optimization)
      - [Task 1.1.2 : Exceptions](#task-112--exceptions)
      - [Task 1.1.3 : Attributes](#task-113--attributes)
      - [Task 1.1.4 : Trailing Return Signature](#task-114--trailing-return-signature)
    - [Task 1.2 : Function Overloading](#task-12--function-overloading)
    - [Task 1.3 : Function Types](#task-13--function-types)
      - [Task 1.3.1 : Function Pointers](#task-131--function-pointers)
    - [Task 1.4 : Function Utilities](#task-14--function-utilities)
  - [Links](#links)

## Task 1

### Task 1.1 : Function Structure

We saw in [part 2](/content/part2/README.md) how to create functions to abstract usable pieces of code into smaller and more modular components. This is the bare-bones of functions of C++. Functions come in a lot of forms in C++ and have to make different guarantees about how they operate. This is done with various specifiers and labels that indicate to the compiler what a function is expected to do. Some of these we have seen including parameter and return value types along with these types various there CV-qualifications.

However, there are a few that have not been covered.

#### Task 1.1.1 : No exception optimization

In C++ there is a keyword dubbed `noexcept`. This is placed at the end of a function signature and indicated to the compiler that the function should not throw and exception. This can help optimizers in a compiler to not store meta-data about how to clean up a function call if an exception is thrown. The `noexcept` specifier can also take in a nested `noexcept` expression indicating that a function doesn't throw an exception if the `noexcept` expression doesn't throw an exception. This useful when the `noexcept` specification of the function depends on the information from the functions signature. If a function marked `noexcept` does throw an exception, `std::terminate()` is called immediately crashing the program. The effects of `noexcept` are not obvious unless we cover exceptions.

#### Task 1.1.2 : Exceptions

Exceptions in C++ are very similar to exceptions in many other programming languages. Exceptions indicate that an error has occurred while a program has been running and it isn't able to handle the error on its own. Using `try-catch` blocks, we can define how exceptions are handled if we suspect one might be thrown. We won't be using exceptions much throughout this course as they are expensive and are used for operations that are expected to maybe throw like resource allocation (web requests, memory allocation).

`try-catch` blocks allow use to run code that may throw in the `try` phase and catch the exception in the `catch` phase and take the appropriate actions to unwind the stack and continue through the program.

```cxx
#include <exception>
#include <iomanip>
#include <iostream>

void foo()
{ throw std::runtime_error{"foo() error"}; }

void bar() noexcept
{ throw std::runtime_error{"bar() error"}; }

auto main () -> int
{    
    try
    {
        foo();
    } 
    catch(const std::exception& e)  ///< Caught as `foo()` is not `noexcept`
    {
        std::cout << "Exception thrown with what(): " << e.what() << std::endl;
    }

    try
    {
        bar();  ///< Fails and calls `std::terminate()`
    } 
    catch(...)  ///< Won't catch
    {
        std::cout << "Exception thrown" << std::endl;
    }

    return 0;
}
```

[Example 51 (Godbolt)](https://www.godbolt.org/z/8e3nYeM5z)
[`noexcept` specifier : cppreference](https://en.cppreference.com/w/cpp/language/noexcept_spec)

#### Task 1.1.3 : Attributes



#### Task 1.1.4 : Trailing Return Signature

### Task 1.2 : Function Overloading

### Task 1.3 : Function Types

#### Task 1.3.1 : Function Pointers

### Task 1.4 : Function Utilities

`std::forward`
`std::declval`
`decltype`

## Links

- [Previous Page : Week 2](/content/weekn/README.md)
- [Next Page : Primitive Data Types](/content/weekn/tasks/.md)
- [Content](/content/README.md)
- [HOME](/README.md)
