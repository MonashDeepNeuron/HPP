# Loops

## Contents

- [Loops](#loops)
  - [Contents](#contents)
  - [Task 3](#task-3)
    - [Task 3.1 : While Loop](#task-31--while-loop)
    - [Task 3.2 : Do-While Loop](#task-32--do-while-loop)
    - [Task 3.3 : For Loop](#task-33--for-loop)
    - [Task 3.4 : Range For](#task-34--range-for)
  - [Links](#links)

## Task 3

Along with conditional expressions another powerful language facility is loops. Loops allow for programs to run in an iterative manner, that is a block will be executed in series. This is powerful feature that enables us to repeat a set of instructions effectively and efficiently.

### Task 3.1 : While Loop

A `while` loop is the most basic kind of loop. `while` loops will repeat its code block as long as its condition is met.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {10};

    while (a > 0)
    {
        std::cout << "a = " << a << std::endl;
        --a;
    }

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/Pxa3G8T4o)

### Task 3.2 : Do-While Loop

There is another kind of `while` loop in C++ called a `do-while` loop. This works the exact same way a regular `while` loop works except that the condition is checked at the end of each loop rather than the start. This means that the code block will be executed at least once.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {0};

    do
    {
        std::cout << "a = " << a << std::endl;
        --a;
    } while (a > 0);

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/od31P37d7)

> Note: You can break out of a `while` or `do-while` loop with `break`.

### Task 3.3 : For Loop

Another common loop in C++ is the `for` loop. `for` loops will generate an initial value, validate it meets a condition and proceed through the sequences.

```cxx
#include <iostream>

auto main () -> int
{
    for (auto i {0}; i < 10; ++i)
        std::cout << "i = " << i << std::endl;

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/KKTrYP5Pe)

As we can see, loops  through the power of conditional checking make programs much smaller and allow us to abstract repeated actions into a single statement.

### Task 3.4 : Range For

There is one other loop in C++. This is the `range-for`. This is a special `for` loop that is able to iterate through a sequence of values, yielding a single value from the sequence each loop. It automatically knows the size of the sequence and when to stop.

```cxx
#include <iostream>

auto main () -> int
{
    std::cout << "[ ";
    for (auto i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
        std::cout << i << ", ";

    std::cout << "]" << std::endl;

    for (auto s : {"It's over Anakin!", "I have the high ground!"})
        std::cout << s << std::endl;

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/P78T9c1Ev)

## Links

- [Previous Page : Conditional Expressions](/content/week2/tasks/condexpr.md)
- [Next Page : Functions](/content/week2/tasks/functions.md)
- [Content](/content/README.md)
- [HOME](/README.md)
