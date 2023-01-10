# Slices

## Contents

- [Slices](#slices)
  - [Contents](#contents)
  - [Task 2](#task-2)
    - [Task 2.1 : What is a slice?](#task-21--what-is-a-slice)
    - [Task 2.2 : Syntax](#task-22--syntax)
      - [Task 2.2.1 :  Iteration](#task-221---iteration)
    - [Task 2.3 : Slices vs Pointers](#task-23--slices-vs-pointers)
    - [Task 2.3.1 : String Literals and Character Slices](#task-231--string-literals-and-character-slices)
  - [Links](#links)

## Task 2

### Task 2.1 : What is a slice?

Working with single value objects and variables can be be tedious and doesn't allow for collecting common data efficiently into a single, easy to refer to object. This is were C++ slices come in. Slices are contiguous sequences of values. The length of a slice must be known at compile time and cannot change. Slices can hold any type including primitive types, user-defined types or even pointers.

We have already been using slices in C++ thus far. String literals are actually slices of `char`.

> Note: Technically slices are called 'built-in arrays' in C++ but I'm opting for an alternative naming convention to avoid confusion later and because 'built-in arrays' is annoying to say.

### Task 2.2 : Syntax

The syntax for a slice is strait forward and goes as follows: `T v[N] { ... };`, where

- `T` is the type of the slices elements
- `v` is the variable name
- `N` is the size of the array (at compile time)
- `{ ... }` is the brace-list of literals that will be copied to the array. This list must be of the same size as `N`

> - Note: `N` can be elided if `{ ... }` is a fixed size.
> - Note: `{ ... }` is called an aggregate initialiser

#### Task 2.2.1 :  Iteration

To access the elements of a slice you use the subscript (index) operator `[i]` where `i` is an unsigned integral from `0..N-1`, where `[0]` gets the first element and `[1]` gets the second element etc.

```cxx
#include <iostream>

void print(int arr[], std::size_t s)
{
    std::cout << "[ ";
    for (auto i {0}; i < s; ++i)
        std::cout << arr[i] << ", ";
    std::cout << "]" << std::endl;
}

auto main () -> int
{
    int nums[] { 1, 2, 3, 4, 5 };

    print(nums, 5);

    return 0;
}
```

[Example](https://www.godbolt.org/z/eGs9PTvfb)

### Task 2.3 : Slices vs Pointers

In C++, slices can; and often will, decay into a pointer. This is because, under the hood, slices are just pointers to a sequence of elements that are contiguous in memory. This makes it efficient to refer to arrays as you can pass around the pointer to its first element. Using the same example as above, if we change `print()` to take an integer pointer `int* arr` instead of `int arr[]` we get the exact some behavior. This is because C++ efficiently packs data together so the exist next to each other in memory.

```cxx
#include <iostream>

void print(int* arr, std::size_t s)
{
    std::cout << "[ ";
    for (auto i {0}; i < s; ++i)
        std::cout << arr[i] << ", ";
    std::cout << "]" << std::endl;
}

auto main () -> int
{
    int nums[] { 1, 2, 3, 4, 5 };

    print(nums, 5);

    return 0;
}
```

[Example](https://www.godbolt.org/z/r7or3x7Tj)

### Task 2.3.1 : String Literals and Character Slices

In C++, the string literal is a `char _[]` or can (usually) decay into a `const char*`. This make them efficient to create and refer to but can have some unfortunate caveats. The biggest issue is that slices are not very user friendly. This is mostly due to them being inherited from C which is; in contrast to C++, a much simpler language that could not afford; at the time of its creation, the more user friendly abstractions C++ has available to it.

## Links

- [Previous Page : Pointers](/content/part3/tasks/pointers.md)
- [Next Page : Dynamic Memory](/content/part3/tasks/memory.md)
- [Content](/content/README.md)
- [HOME](/README.md)
