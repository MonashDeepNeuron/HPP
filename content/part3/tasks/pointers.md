# Pointers

## Contents

- [Pointers](#pointers)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : What is a pointer?](#task-11--what-is-a-pointer)
    - [Task 1.2 : Syntax](#task-12--syntax)
    - [Task 1.3 : const qualifications](#task-13--const-qualifications)
    - [Task 1.4 : void pointers](#task-14--void-pointers)
    - [Task 1.5 : Pointer Arithmetic](#task-15--pointer-arithmetic)
    - [Task 1.6 : Dereferencing nullptr](#task-16--dereferencing-nullptr)
    - [Task 1.7 : Pointers to Pointers](#task-17--pointers-to-pointers)
  - [Links](#links)

## Task 1

### Task 1.1 : What is a pointer?

Many people seem to struggle with the concept of a pointer. This is mostly due to either, bad teaching or that someone learning C++ (or C or Rust) do not have a concise understanding of memory. Memory can be thought of as a cell that has some value and lives at some address or location in the physical memory. Cells can be as small as a byte and as large a single machine register, typically 8-bytes.

> Note: Registers are the circuit components that hold some value in the CPU that is be operated on.

The following data can be mapped to a memory layout below it.

```cxx
int a {4};
int b {37365};
```

|       Address      |        Value       |
|:------------------:|:------------------:|
| 0x00007fff59ae6e9d |         ...        |
| 0x00007fff59ae6e99 |     0x00000004     |
| 0x00007fff59ae6e94 |     0x000091f5     |
| 0x00007fff59ae6e90 |         ...        |

> - Note: `...` means garbage values.
> - Note: `0x...` is just an indicator that the value is a hexadecimal value
> - Note: We jump backwards because the stack (local memory of your program) starts from the largest address and goes down. This is because the code when stored in memory (as instructions) starts from the lowest value and increases. This prevents overwrites between instructions and data, if managed correctly.
> - Note: The memory addresses here are just random, it differs on every computer and every run of the program, usually.

We can see that the value of `a` is stored at address `0x00007fff59ae6e94` and `b` is stored at address `0x00007fff59ae6e9c`. The reason the memory address jumps by four is because each memory address stores a single byte, thus to store a 32-bit value (`int`) you need for bytes thus the next memory address will be four addresses away, in this case the value for `b`.

But lets say we wanted to refer to the value already stored in `a`. We don't want a copy but we wanted some way to _point_ to the value at that address. Well we could store the address of `a` in another location in memory like so.

|       Address      |        Value       |
|:------------------:|:------------------:|
| 0x00007fff59ae6ea4 |         ...        |
| 0x00007fff59ae6e9d |     0x00000004     |
| 0x00007fff59ae6e99 |     0x000091f5     |
| 0x00007fff59ae6e94 | 0x00007fff59ae6e94 |
| 0x00007fff59ae6e90 |         ...        |

> Notes: We jump 8-bytes in the address space for the stored address as addresses (in the example at least) are 64-bit in size.

As we can see, address `0x00007fff59ae6e9d` stores the value `0x00007fff59ae6e94` which happens to be the number indicating the address where `a` is stored.

This is the premise of a pointer. It is a numerical value that holds some address in memory. This is address of another value in a program.

### Task 1.2 : Syntax

To create a pointer in C++ is super simple. Given some type `T` the type of a pointer to a value of that type is `T*`.

We can store the address in an object like any other value in C++. To obtain the address of an object you can use the unary `&` operator prefixed to an objects name or use the `std::addressof()` function found in the header `<memory>`. Using the function is highly recommended as it is more consistent with more complex types.

To obtain the value pointed to by a pointer, we use the unary indirection operator (often called the dereference operator) `*` prefixed to an object name.

```cxx
#include <iostream>
#include <memory>

auto main () -> int
{
    int a {4};
    int b {37365};
    int* pa {&a};
    int* pb {std::addressof(b)};

    std::cout << "a = " << a << std::endl;
    std::cout << "pa = " << pa << std::endl;
    std::cout << "*pa = " << *pa << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "pb = " << pb << std::endl;
    std::cout << "*pb = " << *pb << std::endl;

    return 0;
}
```

[Example 31 (Godbolt)](https://www.godbolt.org/z/aaf33YEYW)
[`std::addressof` : cppreference](https://en.cppreference.com/w/cpp/memory/addressof)

### Task 1.3 : const qualifications

Because pointers are an independent type, they are able to have to have `const` (among other) qualifications however, the ordering of the qualifications can matter.

- `const T*` - Pointer to constant data. The data cannot be changed but the pointer can point to a new location. (`T const*` is identical)
- `T* const` - Constant pointer to data. The data can be modified but the pointer can only point to the original value (address).

```cxx
#include <iostream>
#include <memory>

auto main () -> int
{
    int a {4};
    int b {37365};
    const int* pa {&a};
    int* const pb {std::addressof(b)};

    std::cout << "*pa = " << *pa << std::endl;
    *pa += 3;  ///< Fails, comment out to run
    pa = std::addressof(b);
    std::cout << "*pa = " << *pa << std::endl;

    std::cout << "*pb = " << *pb << std::endl;
    *pb += 3;
    pb = std::addressof(a);  ///< Fails, comment out to run
    std::cout << "*pb = " << *pb << std::endl;

    return 0;
}
```

[Example 32 (Godbolt)](https://www.godbolt.org/z/sed7Wcf7s)

### Task 1.4 : void pointers

Because of C++'s static type system, the type of a pointer must be declared however you can circumvent the type system using `void`. A pointer can be a `void*`, meaning that the type it points to is unbound. When you need to use the type you can then use `static_cast<>()` to create the type that you need. This is actually how C's `malloc()` function works. It returns a `void*` and it is up to the user to cast it to the desired type.

```cxx
#include <iostream>
#include <memory>

auto main () -> int
{
    int a {4};
    void* pa {std::addressof(a)};

    std::cout << "*pa = " << *static_cast<int*>(pa) << std::endl;
    std::cout << "*pa = " << *pa << std::endl;  ///< This will fail, comment out to run

    return 0;
}
```

[Example 33 (Godbolt)](https://www.godbolt.org/z/n9Ynd7fYq)

[C's `malloc()`](https://en.cppreference.com/w/c/memory/malloc)

### Task 1.5 : Pointer Arithmetic

Because pointers are just numbers (addresses) we can add and subtract from then as if they were integral types. We can use the increment, decrement, addition, subtraction and subscript (index) operators on pointers (`+`, `-`, `++`, `--` and `[]` respectively).

This can used to create and access a sequence or memory. This is how a string literal (`""`) works in C++, they are really sequence of `char` that exist in your program statically. C++ then decays them into the type `const char*` so functions can refer to them such as `std::cout <<`.

However, pointer arithmetic is very error prone. and leads to low readability and maintainability, but is useful to understand and for highly controlled manipulation of data.

```cxx
#include <iostream>

auto main () -> int
{
    auto greeting {"Hello!"};
    const char* response {"Hi!!!"};

    for (auto i {0}; i < 7; ++i)
        std::cout << greeting[i];
    std::cout << std::endl;

    for (auto i {0}; i < 6; ++i)
        std::cout << *(response + i);
    std::cout << std::endl;

    /// These will have the same type
    std::cout << "typeid(greeting).name() = " << typeid(greeting).name() << std::endl;
    std::cout << "typeid(response).name() = " << typeid(response).name() << std::endl;

    for (auto i {0}; i < 6; ++i)
        std::cout << *(response++) << std::endl;

    std::cout << "response = " << response << std::endl;  ///< This now points to whatever is stored after `response`.

    return 0;
}
```

[Example 34 (Godbolt)](https://www.godbolt.org/z/qdx6csE7x)

### Task 1.6 : Dereferencing nullptr

In C++, any assignment and initialisation is is copy by default even when passed to functions. This can be really costly for objects that have a large amount of data stored in them. Pointers make it cheap to pass the data around as you now just have to pass a pointer to it instead of all the data. However, there is a catch to pointers. Pointers can point to nothing, this nothing value is actually the literal `nullptr` we saw in week 0. And you cannot dereference a pointer to `nullptr` as `nullptr` is nothing. This can be really dangerous as this is considered UB which may work, may not compile, may crash the entire program or do something entirely unexpected.

```cxx
#include <iostream>

auto main () -> int
{
    int* p {nullptr};

    std::cout << "p = " << p << std::endl;      ///< p = 0

    /// Compiles (on Godbolt) but throws a runtime error (see return of program is not zero)
    std::cout << "*p = " << *p << std::endl;

    return 0;
}
```

[Example 35 (Godbolt)](https://www.godbolt.org/z/594hMbcz6)

### Task 1.7 : Pointers to Pointers

It is also possible in C++ to have a pointer to a pointer. This mostly a feature inherited from C and remains in for C++ to interoperate with C and for completeness. Pointers to pointers may seem daunting but are straight forward if you apply the concept of a pointer again. The pointer-to-pointer object points to the address of the pointer object that holds the address of some other object. Pointer-to-pointers have the type `T**` and can be dereferenced to the their value, ie. the address the nested pointer points to or again to get the bottom value.

```cxx
#include <iostream>
#include <memory>

auto main () -> int
{
    int a {6};
    int* p {std::addressof(a)};
    int** pp {std::addressof(p)};

    std::cout << "pp = " << pp << std::endl;
    std::cout << "*pp = " << *pp << std::endl;
    std::cout << "**pp = " << **pp << std::endl;

    return 0;
}
```

[Example 36 (Godbolt)](https://www.godbolt.org/z/MPPczrWzd)

> Note: `auto` is able to deduce the type if the right-hand-side is a rvalue however, the `const` qualifications cannot be specified. ie. `T* -> auto` and `T** -> auto`.

## Links

- [Previous Page : Week 3](/content/part3/README.md)
- [Next Page : Slices](/content/part3/tasks/slices.md)
- [Content](/content/README.md)
- [HOME](/README.md)
