# Namespaces

## Contents

- [Namespaces](#namespaces)
  - [Contents](#contents)
  - [Task 2](#task-2)
    - [Task 2.1 : Namespaces](#task-21--namespaces)
    - [Task 2.2 : Duplicate Namespaces](#task-22--duplicate-namespaces)
    - [Task 2.3 : Nested Namespaces](#task-23--nested-namespaces)
  - [Links](#links)

## Task 2

### Task 2.1 : Namespaces

Namespaces create separation of symbols and names in C++. This allows for types, functions and variables to have the same name without causing collisions and ambiguity. We have already been using a namespace throughout this series, this being the `std` namespace. Namespaces a named scopes whose members can be accessed using the scope resolution operator `::`. To create a namespace you use the `namespace` keyword followed by the namespace name and a new scope. To use a namespace without having to go through scope resolution you can declare a namespaces use by `using namespace /* name */`.

> Note: Using `::` with no name looks in the global namespace eg. `::a`.

```cxx
#include <iostream>

namespace A
{
    auto f(int n)
        -> void
    { std::cout << n << '\n'; }
}

auto f(int n)
    -> void
{ std::cout << "3 + n:(" << n << ") = " << 3 + n << '\n'; }

auto main() -> int
{
    // using namespace A;  ///< Error: overload is ambiguous (redefinition)
    f(8);
    A::f(8);

    return 0;
}
```

[Example](https://www.godbolt.org/z/9oon3r944)

[Namespaces : cppreference](https://en.cppreference.com/w/cpp/language/namespace)

### Task 2.2 : Duplicate Namespaces

Two namespaces with the same name will logically be merged, members and symbols from both can be looked up using the same namespace name given both headers containing the namespace symbols is available to be searched. This is how the `std` namespace can have all its components across different headers but be looked up using `std::`.

```cxx
#include <iostream>

namespace A
{
    auto f(int n)
        -> void
    { std::cout << n << '\n'; }
}

namespace A
{
    auto g(int n)
        -> void
    { std::cout << "3 + n:(" << n << ") = " << 3 + n << '\n'; }
}

auto main() -> int
{
    A::f(8);
    A::g(8);

    return 0;
}
```

[Example](https://www.godbolt.org/z/r9PPxbYh5)

### Task 2.3 : Nested Namespaces

Namespaces can also be declared to be nested. We saw this in the previous set of tasks with the `std::placeholders` namespace. To access a nested namespace you use a double scope resolution operator `::`.

```cxx
#include <iostream>

namespace A
{
    auto f(int n)
        -> void
    { std::cout << n << '\n'; }

    namespace B
    {
        auto f(int n)
            -> void
        { std::cout << "3 + n:(" << n << ") = " << 3 + n << '\n'; }
    }
}

auto main() -> int
{
    A::f(8);
    A::B::f(8);

    return 0;
}
```

[Example](https://www.godbolt.org/z/afj6eEYe7)

## Links

- [Previous Page : Advanced Functions](/content/part4/tasks/advfunc.md)
- [Next Page : Enumerations](/content/part4/tasks/enums.md)
- [Content](/content/README.md)
- [HOME](/README.md)
