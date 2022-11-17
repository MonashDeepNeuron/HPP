# Functions

## Contents

- [Functions](#functions)
  - [Contents](#contents)
  - [Task 4](#task-4)
    - [Task 4.1 : What is a functions?](#task-41--what-is-a-functions)
    - [Task 4.2 : Function Syntax](#task-42--function-syntax)
      - [Task 4.2.3 : Void Functions](#task-423--void-functions)
  - [Links](#links)

## Task 4

### Task 4.1 : What is a functions?

A function is the most basic form of abstraction in programming. They allow software to be broken down into more simple pieces of code and compose and reuse them as we please.

Much like functions in mathematics, functions in C++ (an every programming language) take in some input parameters (aka arguments or points) and return a single output value. This creates a transformation or mapping between input values and types to output values and types.

### Task 4.2 : Function Syntax

Functions in C++ consist of a declaration and definition. A declaration is the functions signature which consists of the functions name, its points and its return type. The definition is a code block with at least on `return` expression.

```cxx
T f(A1 a1, A2 a2)
{ 
    /* code */ 
    
    return ...;
}
```

- `T` is the return type
- `A1` is the type of argument one stored in parameter `a1`
- `A2` is the type of argument one stored in parameter `a2`
- `return ...;` is the return expression

Functions have to be invoked to be used. This involves using the invocation operator `()` on the functions name. You can pass literals and variables to functions. You can also initialise and assign variables from the return of a function.

```cxx
#include <iostream>

int add(int x, int y)
{ return x + y; }

auto main () -> int
{
    auto a {4};
    auto b {7};
    auto c {-3};

    int d = add(5, 7);

    std::cout << add(a, b) << std::endl;
    std::cout << add(a, c) << std::endl;
    std::cout << add(a, d) << std::endl;
    std::cout << add(b, c) << std::endl;
    std::cout << add(b, d) << std::endl;
    std::cout << add(c, d) << std::endl;

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/Gx4P9jTej)

Functions allow us to abstract any common pattern into reusable code.

```cxx
#include <iostream>

int sum(int s, int f)
{
    auto acc {0};
    for (auto i {s}; i < f; ++i)
        acc += i;
    return acc;
}

auto main () -> int
{

    std::cout << sum(0, 5) << std::endl;
    std::cout << sum(-3, 8) << std::endl;
    std::cout << sum(-11, -5) << std::endl;
    std::cout << sum(4, 19) << std::endl;

    return 0;
}
```

#### Task 4.2.3 : Void Functions

[Godbolt](https://www.godbolt.org/z/radjo93bx)

## Links

- [Previous Page : Loops](/content/week2/tasks/loops.md)
- [Back to Week 2](/content/week2/README.md)
- [Content](/content/README.md)
- [HOME](/README.md)
