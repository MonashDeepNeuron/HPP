# References

## Contents

- [References](#references)
  - [Contents](#contents)
  - [Task 4](#task-4)
    - [Task 2.1 : What is a reference?](#task-21--what-is-a-reference)
    - [Task 4.1.1 : Pointers vs References](#task-411--pointers-vs-references)
    - [Task 4.2 : Syntax](#task-42--syntax)
    - [Task 4.3 : const qualifications](#task-43--const-qualifications)
    - [Task 4.4 : Move Semantics](#task-44--move-semantics)
  - [Links](#links)

## Task 4

### Task 2.1 : What is a reference?

So far we have learnt about pointers and how they are useful in distributing access to a memory resource that is expensive to copy as well as create contiguous sequences of values or slices. We have also seen how to get larger memory resources from the OS using `new` and `delete` expressions. However, we have also seen that pointers have caveats. They can lead to memory leaks and other various issues about ownership and lifetime of objects.

In C++ there is another facility that allows for you to refer to data in different scopes that do not feature the same pitfalls of pointers. These are called references. References are; as the the name suggests a reference to an existing object or in other words an alias for an existing object. Operations done on a reference are truly done on the original object. This helps to avoid the cumbersome and error prone nature of pointers.

### Task 4.1.1 : Pointers vs References

|             Pitfall            | Pointers | References |                                                            Meaning                                                           |
|:------------------------------:|:--------:|:----------:|:----------------------------------------------------------------------------------------------------------------------------:|
|            Nullable            |     ✅    |      ❌     |                                       Pointers can point to nothing, references cannot                                       |
|         Dereferencable         |     ✅    |      ❌     |                                              You cannot dereference a reference                                              |
|           Rebindable           |     ✅    |      ❌     | A reference cannot be rebound to a new value. Operations done on the reference affect the underlying value, even assignment. |
| Multiple levels of indirection |     ✅    |      ❌     |                                          You cannot have a reference of a reference.                                         |
|       Pointer arithmetic       |     ✅    |      ❌     |                                    You cannot increment (etc.) a reference like a pointer                                    |

### Task 4.2 : Syntax

References are declared as `T&`. References must also have an initialiser.

```cxx
#include <iostream>

auto main () -> int
{
    int i {7};
    int& ir {i};

    std::cout << "i = " << i << std::endl;
    std::cout << "ir = " << ir << std::endl;

    ir += 6;
    std::cout << "i = " << i << std::endl;

    i -= 4;
    std::cout << "ir = " << ir << std::endl;

    return 0;
}
```

[Example 41 (Godbolt)](https://www.godbolt.org/z/7TWjK5rKe)

### Task 4.3 : const qualifications

Because references cannot be rebound to reference a new object `const` qualifications are must simpler than pointers. References themselves are alway constant, that is always point to the same thing however, you can specify that the object itself is constant with `const T&`. This means that the the object the reference refers to cannot be modified.

```cxx
#include <iostream>

auto main () -> int
{
    int i {7};
    int& ir {i};
    const int& cir {i};

    std::cout << "i = " << i << std::endl;
    std::cout << "ir = " << ir << std::endl;
    std::cout << "cir = " << cir << std::endl;

    ir += 6;
    std::cout << "i = " << i << std::endl;

    i -= 4;
    std::cout << "ir = " << ir << std::endl;

    cir += 7;   ///< Fails, `cir` is read-only
    std::cout << "i = " << i << std::endl;

    return 0;
}
```

[Example 42 (Godbolt)](https://www.godbolt.org/z/as3rTWavj)

> Note: You can substitute just the type `T` of a reference for `auto` ie. `T& -> auto&` and `const T& -> const auto&`

### Task 4.4 : Move Semantics

References are also used to denote move semantics in functions. So far we have only seen value, pointer and reference semantics. Move semantics allow for a function to take ownership of a object from a variable. Move semantics are denoted using the `T&&` type signature, this is also called a rvalue. This allows us to rip out the guts of an object and use it how we please. To create a rvalue from an existing object we use the `std::move()` function from the `<utility>` header.

The difficulty of move semantics is it only applies to objects that can move ie. types with move constructors and move assignments. Without these constructors `T&&` just becomes a regular reference. This is the case for primitive types in C++. We will cover more on moves in [Week 5](/content/week5/README.md).

## Links

- [Previous Page : Dynamic Memory](/content/week3/tasks/memory.md)
- [Next Page : Introduction to the Standard Library](/content/week3/tasks/stdlib.md)
- [Content](/content/README.md)
- [HOME](/README.md)
