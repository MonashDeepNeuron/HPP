# Advanced Functions

## Contents

- [Advanced Functions](#advanced-functions)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : Advanced Functions Specification](#task-11--advanced-functions-specification)
      - [Task 1.1.1 : No exception optimization](#task-111--no-exception-optimization)
      - [Task 1.1.2 : Attributes](#task-112--attributes)
      - [Task 1.1.3 : Auto Function](#task-113--auto-function)
    - [Task 1.2 : Function Overloading](#task-12--function-overloading)
      - [Task 1.2.1 : Operator Overloading](#task-121--operator-overloading)
    - [Task 1.3 : Function Utilities](#task-13--function-utilities)
      - [Task 1.3.1 : Perfect Forwarding](#task-131--perfect-forwarding)
      - [Task 1.3.2 : Value and Type Helpers](#task-132--value-and-type-helpers)
    - [Task 1.4 : Function Types](#task-14--function-types)
      - [Task 1.4.1 : Function as a Type](#task-141--function-as-a-type)
  - [Links](#links)

## Task 1

### Task 1.1 : Advanced Functions Specification

We saw in [part 2](/content/part2/README.md) how to create functions to abstract usable pieces of code into smaller and more modular components. This is the bare-bones of functions of C++. Functions come in a lot of forms in C++ and have to make different guarantees about how they operate. This is done with various specifiers and labels that indicate to the compiler what a function is expected to do. Some of these we have seen including parameter and return value types along with these types various there CV-qualifications however, there are a few that have not been covered yet. Throughout this page we will build up a function signature from the blueprint below by adding new specifiers to showcase the syntax.

```cxx
int f(int n)
{ return n; }
```

#### Task 1.1.1 : No exception optimization

WE won't be covering exceptions in this course as they are quite an advanced topic that is hard to use and costly to get wrong. We may cover exceptions at a later date. In C++ some functions may throw exceptions when ill-formed behavior occurs and but it can be handled so the system can remain operational. However, some functions we can make guarantees at compile time that they will not throw an exception. This allows the compiler to optimise the execution path knowing that it will not need to recover the stack. To do this, we mark a function `noexcept` keyword. If a `noexcept` functions does throw, the program calls `std::terminate`.

```cxx
int f(int n) noexcept
{ return n; }
```

[`noexcept` : cppreference](https://en.cppreference.com/w/cpp/language/noexcept_spec)

#### Task 1.1.2 : Attributes

Attributes are a declarator that indicates a condition of a function. Attributes are prefixed before the return type of the function using the double square-bracket notation `[[attribute-name]]`. C++ only has a few standard attributes so far but compilers often introduce their own for optimisation of the compiler.

- `[[noreturn]]` - Indicates a function doesn't return
- `[[maybe_unused]]` - Indicates an entity maybe unused and suppresses relevant compiler warnings.
- `[[deprecated]]` & `[[deprecated("reason")]]` - Indicated that the use of the marked entity is allowed but discouraged.
- `[[nodiscard]]` & `[[nodiscard("reason")]]` - Indicated that the return value of a function should not be discarded and generates a compiler warning if it is.

```cxx
[[nodiscard]]
int f(int n) noexcept
{ return n; }
```

[**_attributes_** : cppreference](https://en.cppreference.com/w/cpp/language/attributes)

#### Task 1.1.3 : Auto Function

Sometimes the return value of a function is a complicated type or depends on the type of the parameters of the function. This can be solved using an `auto` declared function with a trailing-return-type.

```cxx
[[nodiscard]]
auto f(int n) noexcept
    -> int
{ return n; }
```

[**_Function Declarations_** : cppreference](https://en.cppreference.com/w/cpp/language/function)

> Note: The styling used above is my own personal syntax styling. You are free to use your own.

### Task 1.2 : Function Overloading

One difficulty in many programing languages is that you cannot have function symbols with the same name. This creates clashes and ambiguity meaning the compiler doesn't know which function to use. In C++ however, you can have functions with the same symbol (name) as long as there parameters are different. This is called function overloading. This is is achieved due to what is called name mangling. Function names are not simply just the name, say `f` from above but are mangled to include the type of the parameters the function takes. Thus `int f(int n)` is a different function to `float f(float n)`. This powerful feature allows us to create multiple functions that perform the same action but for multiple different types and move type resolution to compile time.

#### Task 1.2.1 : Operator Overloading

Function overloading opens the opportunity to create user defined operators. This means you can overload the `+` or `<<` operators to work for custom types or introduce new functionality. This is how the `<<` and `>>` works for stream in C++. The `<<` and `>>` are overloaded to work differently for stream objects.

```cxx
#include <iostream>
#include <string>

using namespace std::literals;

/// Comment out to see old behaviour
auto operator+ (std::string x, std::string y) -> int
{ return std::stoi(x) + std::stoi(y); }

auto main() -> int
{
    std::cout << "6"s + "5"s << std::endl;

    return 0;
}
```

[Example 51](https://www.godbolt.org/z/jaevh6dna)

### Task 1.3 : Function Utilities

#### Task 1.3.1 : Perfect Forwarding

Often in C++ we want to pass arguments from one function to another without modification. An example of this is passing arguments to a wrapper function that might call some old legacy API. However, there can be issues with value categories, const-ness and reference values of parameters that create undefined behaviour, compiler errors etc. To fix this, C++ introduced perfect forwarding, a way to perfectly pass arguments from on function call to another without losing or changing the value category of the parameters. This is done with `std::forward<T>`. I am glossing over the details of this but if you are interested, this [SO answer](https://stackoverflow.com/a/3582313/13429386) gives a great explanation of the problem, attempted solutions and the solution in C++ now.

[`std::forward<T>` : cppreference](https://en.cppreference.com/w/cpp/utility/forward)

#### Task 1.3.2 : Value and Type Helpers

Sometimes it is useful to work with the type of an object, not the value. To obtain the type of an object the `decltype` keyword. This declares the type of the entity or expression passed to the keyword in a function call style. This is useful for deducing the type of an expression once it has been evaluated.

```cxx
#include <type_traits>

auto add(int x, float y) -> decltype(x + y)
{ return x + y; }

auto main() -> int
{
    static_assert(std::is_same_v<decltype(add(9, 0.345)), float>, "Result is not a float");
    static_assert(std::is_same_v<decltype(add(9, 0.345)), int>, "Result is not a int");

    return 0;
}
```

[Example 52](https://www.godbolt.org/z/6Gco6zsvs)

[`<type_traits>` : cppreference](https://en.cppreference.com/w/cpp/header/type_traits)

[`decltype` : cppreference](https://en.cppreference.com/w/cpp/language/decltype)

Sometimes though, it is impossible to find the return type of objects method calls as it requires constructing an actual value. To overcome this, C++ has a neat function called `std::declval`. This is able to construct an rvalue (temporary) in order to access object methods.

```cxx
#include <type_traits>

auto main() -> int
{
    static_assert(std::is_same_v<decltype(std::declval<int>()), int&&>, "Result is not rvalue");
    static_assert(std::is_same_v<decltype(std::declval<int>()), int>, "Result is rvalue");

    return 0;
}
```

[Example 53](https://www.godbolt.org/z/sfaq6c9Yf)

[`std::declval<T>` : cppreference](https://en.cppreference.com/w/cpp/utility/declval)

### Task 1.4 : Function Types

#### Task 1.4.1 : Function as a Type

Functions; like variables, have a type. This makes it possible to use functions are variables that can be passed to other functions. But what is the type of a function? In general the type of a function is composed of its return type and the type of its arguments, ie. `R(P1, P2, P3, ...)`. In C functions are passed as function pointers. It is a powerful utility but can be error prone due to the nature of pointers. Instead, C++ has `std::function<R(Args...)>` which is able to bind to a function to a variable that can be easily passed around to other functions, copied and moved.

```cxx
#include <functional>
#include <iostream>

auto print_num(double i)
    -> void
{ std::cout << i << '\n'; }

auto add(int x, float y)
    -> double
{ return x + y; }

auto mult_print(int x, float y, std::function<void(double)> f)
    -> void
{ f(x * y); }

auto main() -> int
{
    std::function<void(double)> print_f {print_num};
    std::function<double(int, float)> add_f {add};

    print_f(add_f(4, 6.6));
    mult_print(3, 0.056, print_f);

    return 0;
}
```

[Example 54](https://www.godbolt.org/z/TjrWfM5Th)

[`std::function<R(Args...)>` : cppreference](https://en.cppreference.com/w/cpp/utility/functional/function)

## Links

- [Previous Page : Part 4](/content/part4/README.md)
- [Next Page : Functional Programming](/content/part4/tasks/functional.md)
- [Content](/content/README.md)
- [HOME](/README.md)
