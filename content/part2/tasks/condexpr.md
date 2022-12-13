# Conditional Expressions

## Contents

- [Conditional Expressions](#conditional-expressions)
  - [Contents](#contents)
  - [Task 7](#task-7)
    - [Task 7.1 : Scope](#task-71--scope)
    - [Task 7.2 : if-expressions](#task-72--if-expressions)
    - [Task 7.2.1 : else-expression](#task-721--else-expression)
    - [Task 7.3 : Ternary Operator](#task-73--ternary-operator)
    - [Task 7.4 : Switch Statements](#task-74--switch-statements)
      - [Task 7.4.1 : Fallthroughs](#task-741--fallthroughs)
  - [Links](#links)

## Task 7

### Task 7.1 : Scope

One important concept in programming is the idea of scope. In C++, scope is very important as it can have an important impact on the design, performance in the safety of a program. Currently we have been running a program purely in the scope of the `main()` function. What denotes a scope in C++ is a pair of braces `{}`. Anything introduced within the braces is now in a new scope separate from the outside program. Objects from outside the new scope can be captured but anything created in a new scope is dropped at the end of the scope.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {4};

    {
        auto b {6};
        std::cout << a << std::endl;
        std::cout << b << std::endl;
    }

    std::cout << a << std::endl;
    std::cout << b << std::endl;  ///< Will fail here, comment out to run

    return 0;
}
```

[Example 17](https://www.godbolt.org/z/57hne667f)

Scope blocks (or sometimes code blocks) allow us to encapsulate expressions.

### Task 7.2 : if-expressions

Control flow allows for programs to branch and follow non-linear execution patterns. In C++, this is done through structured conditional expressions. The primary one being an `if` expression. `if` expressions are followed by a code block surrounded in `{}`. If the condition is met, then the code block executes.

- `if (/* Boolean condition */) { /* code */ }`

> Note: One-liner execution blocks don't have to be in `{}`.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {1};
    auto b {2};

    if (a < b)
    {
        std::cout << "a is less then b" << std::endl;
    }

    if (a == b)
        std::cout << "a is equal to b" << std::endl;

    if (a > b)
        std::cout << "a is greater then b" << std::endl;

    return 0;
}
```

[Example 18](https://www.godbolt.org/z/4dK3P17ax)

We can also use an `else` clause at the end. This indicates that if and `if` expression fails, the `else` clause will execute instead.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {1};
    auto b {2};

    if (a == b)
        std::cout << "a is equal to b" << std::endl;
    else
        std::cout << "a is not equal to b" << std::endl;

    return 0;
}
```

[Example 19](https://www.godbolt.org/z/31TcjvYrP)

### Task 7.2.1 : else-expression

We can combine the `else` clause with an `if` expression to create and `else if` expression. This allows for you to create multiple branches in a single `if` statement.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {1};
    auto b {2};

    if (a < b)
        std::cout << "a is less then b" << std::endl;
    else if (a == b)
        std::cout << "a is equal to b" << std::endl;
    else if (a > b)
        std::cout << "a is greater then b" << std::endl;
    else
        std::cout << "a is unordered to b" << std::endl;

    return 0;
}
```

[Example 20](https://www.godbolt.org/z/Md3Mfx3MK)

### Task 7.3 : Ternary Operator

`if` statements are the first step to building much more complex programs however, they are quite bulky in syntax for short conditional expressions. Instead we can use the ternary operator `?:` to build short and concise conditional expressions. A ternary expression has the following syntax.

`auto /* result */ = /* Boolean expression */ ? /* expression is true */ : /* expression is false */;`

```cxx
#include <iostream>

auto main () -> int
{
    auto a {1};
    auto b {2};

    auto msg = a < b ? "a is less then b" : "b is less then a";

    std::cout << msg << std::endl;

    return 0;
}
```

[Example 21](https://www.godbolt.org/z/4n4xYh7T8)

### Task 7.4 : Switch Statements

Another useful construct in C++ is a `switch` statement. `switch` statements encapsulate the idea of a jump table however, it is limited to integral types, thus the `switch` condition must be an integral type and have integral case labels.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {1};

    switch (a)
    {
        case 1:
            std::cout << "a + 1 = " << a + 1 << std::endl;
            break;
        case 2:
            std::cout << "a * 2 = " << a * 2 << std::endl;
            break;
        case 3:
            std::cout << "a - 3 = " << a - 3 << std::endl;
            break;
        default:
            std::cout << "a / 5 = " << a / 5 << std::endl;
            break;
    }

    return 0;
}
```

[Example 22](https://www.godbolt.org/z/nz6TYWodK)

#### Task 7.4.1 : Fallthroughs

You will note that at the end of each of the case blocks there are `break` statements. These are used to exit the switch statement entirely. If this weren't there, each case would run in sequence. This is called fallthrough. most compilers will warn you of this.

```cxx
#include <iostream>

auto main () -> int
{
    auto a {1};

    switch (a)
    {
        case 1:
            std::cout << "a + 1 = " << a + 1 << std::endl;
        case 2:
            std::cout << "a * 2 = " << a * 2 << std::endl;
        case 3:
            std::cout << "a - 3 = " << a - 3 << std::endl;
        default:
            std::cout << "a / 5 = " << a / 5 << std::endl;
    }

    return 0;
}
```

[Example 23](https://www.godbolt.org/z/9oEfYrMMq)

## Links

- [Previous Page : Equality, Ordering and Logical Operators](/content/part2/tasks/eqordlogic.md)
- [Next Page : Loops](/content/part2/tasks/loops.md)
- [Content](/content/README.md)
- [HOME](/README.md)
