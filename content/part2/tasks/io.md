# Streams

## Contents

- [Streams](#streams)
  - [Contents](#contents)
  - [Task 5](#task-5)
    - [Task 5.1 : What is a stream?](#task-51--what-is-a-stream)
    - [Task 5.2 : C Standard Streams](#task-52--c-standard-streams)
      - [Task 5.2.1 : Input](#task-521--input)
    - [Task 5.3 : IO Manipulators](#task-53--io-manipulators)
  - [Links](#links)

## Task 5

### Task 5.1 : What is a stream?

What is a stream. A stream is a sequence of an indeterminate amount of data connecting a source to a destination. In C++, streams are used to connect a perform a variety of IO operations. You have already used on of these streams in C++, this is of course `std::cout`.

### Task 5.2 : C Standard Streams

In C++ there are a few pre-defined stream objects. This are mounted to the the C languages `stdout`, `stdin` and `stderr`. These output devices are how C (and these stream objects) connect to the terminal screen and keyboard of your device.

- `std::cin`  - Output stream to C's `stdin`
- `std::cout` - Output stream to C's `stdout`
- `std::cerr` - Output stream to C's `stderr`
- `std::clog` - Output stream to C's `stderr` (not dependent on `stdout`)

These are pre-existing objects of the type `std::istream` and `std::ostream` respectively. The use of streams allows for C++ developer to have a uniform way of addressing different IO devices. In particular the `<<` operator is available to all streams types allowing for similar usage of streams that may be mounted to alternative IO devices, eg. files, graphics card, cameras etc.

All stream objects and types are found in the `<iostream>` header.

[IO Library](https://en.cppreference.com/w/cpp/io)

#### Task 5.2.1 : Input

We have seen how to print stuff to the console but how do we get input? There are two ways. One uses the stream directly with the `>>` operator while the other defers using a function call. We will only look at the direct usage for now.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {0};
    auto b {0};

    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;

    return 0;
}
```

[Example 11 (Godbolt)](https://www.godbolt.org/z/3zoz1517r)

### Task 5.3 : IO Manipulators

Because streams are used for IO operations in C++, they are naturally composable, allowing for the streams manipulation mid-stream. The C++ standard library has a variety of manipulators that allow you to change a streams format. Manipulators are found in the `<iomanip>` header.

```cxx
#include <iomanip>
#include <iostream>

auto main () -> int
{
    auto a {255};
    auto b {0.01};

    std::cout << "a: oct = " << std::oct << a << std::endl;  ///< 377
    std::cout << "a: hex = " << std::hex << a << std::endl;  ///< ff
    std::cout << "a: dec = " << std::dec << a << std::endl;  ///< 255

    std::cout << std::fixed << b << std::endl;          ///< 0.010000
    std::cout << std::scientific << b << std::endl;     ///< 1.000000e-02
    std::cout << std::hexfloat << b << std::endl;       ///< 0x1.47ae147ae147bp-7
    std::cout << std::defaultfloat << b << std::endl;   ///< 0.01

    return 0;
}
```

[Example 12 (Godbolt)](https://www.godbolt.org/z/s8rGc4heM)

## Links

- [Previous Page : Operators](/content/part2/tasks/operators.md)
- [Next Page : Equality, Ordering & Logical Operators](/content/part2/tasks/eqordlogic.md)
- [Content](/content/README.md)
- [HOME](/README.md)
