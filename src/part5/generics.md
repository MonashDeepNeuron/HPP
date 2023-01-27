# Generics

## Contents

- [Generics](#generics)
  - [Contents](#contents)
  - [Task 3](#task-3)
    - [Task 3.1 : Generic Programming](#task-31--generic-programming)
    - [Task 3.2 : Parameter Packs](#task-32--parameter-packs)
      - [Task 3.2.1 : Parameter pack size](#task-321--parameter-pack-size)
      - [Task 3.2.2 : Fold Expressions](#task-322--fold-expressions)
    - [Task 3.3 : Tuples](#task-33--tuples)
      - [Task 3.3.1 : Pairs](#task-331--pairs)
      - [Task 3.3.2 : Destructuring](#task-332--destructuring)
  - [Links](#links)

## Task 3

### Task 3.1 : Generic Programming

Generic programming is a style of programming that involves defining algorithms and data structures in terms of generic types. This allows the behaviour of the program to be adapted according to the types, which can be resolved at compile or pre-process time as opposed to through runtime resolution. It also allows for programs to work in a more adaptive way so that, regardless of the type that used at instantiation time, the program will adapt and work accordingly.

### Task 3.2 : Parameter Packs

Part of C++ generic programming facilities that go hand-in-hand with templates is template parameter packs. These are heterogenous objects that can contain an arbitrary number of elements that gets instantiated at compile time. Parameter packs allows for C++ to generalize the idea passing an around an arbitrary number of different typed arguments. This can be utilised by template functions and classes alike. Parameter packs can also have a single type which indicates an arbitrary number of values with the same type. Parameter packs are denoted by an ellipsis `Ts...` where `Ts` is either a parameter pack template type parameter from the template declaration of the form `template<typename... Ts>`, or the single type of a value parameter pack with the function signature of the form `f(int... ints)`. We can combine these two notations to create functions of variadic type arguments `f(Ts... ts)` where `Ts` is a template type parameter pack and `ts` is a template value parameter pack.

```cxx
#include <iostream>
 
auto tprintf(const char* format) -> void  ///< Base function
{ std::cout << format; }
 
template<typename T, typename... Args>
auto tprintf(const char* format, T value, Args&&... args) -> void  ///< recursive variadic function
{
    for (; *format != '\0'; format++)
    {
        if (*format == '%')
        {
            std::cout << value;
            tprintf(format + 1, std::forward<Args>(args)...);  ///< recursive call, `std::forward` is called on the expanded pack
            return;
        }
        std::cout << *format;
    }
}
 
auto main() -> int
{
    tprintf("% world% % - %\n", "Hello", '!', 123, -0.3575);

    return 0;
}
```

[Example](https://www.godbolt.org/z/sMxWcd1fM)

[Parameter Packs : cppreference](https://en.cppreference.com/w/cpp/language/parameter_pack)

#### Task 3.2.1 : Parameter pack size

The size of a pack can be obtained by using the `sizeof...` operator. This will return a `std::size_t` with the number of either types or values in the parameter pack.

```cxx
#include <iostream>
 
template<typename... Args>
auto print_size(Args&&... args) -> void
{ std::cout << sizeof...(args) << std::endl; }
 
auto main() -> int
{
    print_size(2, 0.6, 0.5313f, "Hello");

    return 0;
}
```

[Example](https://www.godbolt.org/z/nhnj3Ehne)

[`sizeof...` : cppreference](https://en.cppreference.com/w/cpp/language/sizeof...)

#### Task 3.2.2 : Fold Expressions

Fold expressions allow for unary and binary operations to be performed on packs of elements. This allows us to 'loop' through a pack and perform compile type computation such as sums, printing and more. Fold expressions can operate just on the pack ot can have an initialiser that is separate from the pack.

```cxx
#include <iostream>
 
template<typename... Args>
auto sum(Args&&... args) -> std::common_type<Args...>::type
{ return (... + args); }

template<typename T, typename... Args>
auto product(T init, Args&&... args) -> std::common_type<T, Args...>::type
{ return (init * ... * args); }
 
auto main() -> int
{
    std::cout << sum(2, 0.6, 0.5313f) << std::endl;
    std::cout << product(0, 6, 1.356, 90.5313f) << std::endl;
    std::cout << product(6, 1.356, 90.5313f) << std::endl;

    return 0;
}
```

[Example](https://www.godbolt.org/z/zh97vevo3)

[Fold expressions : cppreference](https://en.cppreference.com/w/cpp/language/fold)

### Task 3.3 : Tuples

Because of the introduction of parameter packs in C++11, C++ was finally able to have a tuple data structure called `std::tuple`. Tuples are a formalisation of parameter packs, tieing a heterogeneous pack of types to a heterogeneously types pack of values. Tuples are incredibly powerful in programming as they formalise the idea of being able to cluster together elements of any type where the types might not be immediately be known at definition. This is; normally, incredibly difficult to do in a typed language like C++ with the solution before being to create aggregate classes to store the required data together. Tuples make this far easier and can be used anywhere. ANother benefit is any tuple has a common interface allowing anyone to manipulate them as they need. `std::tuple` structure is immutable however, its elements can be modified in place making them extremely versatile. `std::tuple` comes with a host of powerful helper functions and classes that allow for compile time inspection of a tuples size, element type and value access, creation of `std::tuple` and destructuring.

```cxx
#include <iostream>
#include <tuple>
#include <utility>

template<typename Tup, std::size_t... I>
auto print(const Tup& t, std::index_sequence<I...>) -> void
{
    std::cout << "( ";

    (..., (std::cout << (I == 0 ? "" : ", ") << std::get<I>(t)) );

    std::cout << " )" << std::endl;
}


template<typename... Ts, std::size_t... I>
auto print(const std::tuple<Ts...>& t) -> void
{ print(t, std::make_index_sequence<sizeof...(Ts)>()); }


auto main() -> int
{
    auto t1 = std::tuple<int, double>{ 2, 0.6 };        ///< Types explicitly declared
    auto t2 = std::tuple{ 15.2f, "Hello" };             ///< With type deduction
    auto t3 = std::make_tuple("Bye", 15, 78, 343.546);  ///< With type deducing maker

    print(t1);
    print(t2);
    print(t3);

    return 0;
}
```

[Example](https://www.godbolt.org/z/v5sP6TjYs)

[`std::tuple` : cppreference](https://en.cppreference.com/w/cpp/utility/tuple)

#### Task 3.3.1 : Pairs

It is often common place to just need to return a two values of possibly different types and not have to go through the hassle of uses `std::tuple` generic (yet admittedly cumbersome) access methods. This is where `std::pair` comes in. `std::pair` is a specific use case of a `std::tuple`. Accessing the elements of a pair can be done directly using class dot access of the members name.

```cxx
#include <iostream>
#include <utility>

template<typename F, typename S>
auto print(const std::pair<F, S>& p) -> void
{
    std::cout << "( " << p.first << ", " << p.second << " )" << std::endl;
}

auto main() -> int
{
    auto p1 = std::pair<int, double>{ 2, 0.6 };     ///< Types explicitly declared
    auto p2 = std::pair{ 15.2f, "Hello" };          ///< With type deduction
    auto p3 = std::make_pair(78, 343.546);          ///< With type deducing maker

    print(p1);
    print(p2);
    print(p3);

    return 0;
}
```

[Example](https://www.godbolt.org/z/ax688eds3)

[`std::pair` : cppreference](https://en.cppreference.com/w/cpp/utility/pair)

#### Task 3.3.2 : Destructuring

Since C++17, `std::pair` and `std::tuple` can be accessed using structured bindings. This can make it easier to manipulate the data of a pair, tuple, arrays, slices and even aggregate classes. Structured bindings are declared by an `auto` specifier (which can have reference, storage and cv qualifiers) followed by square brackets containing comma separated variable names that will bind to the sequence of values ie. `/*cv-qual (optional) */auto/*& or && (optional)*/ [/* names */] = /* tuple-like */`.

```cxx
#include <iostream>
#include <tuple>

auto main() -> int
{
   
    auto t = std::make_tuple(78, 343.546, "Hello");
    auto& [i1, f1, s1] = t;

    std::cout << "( " << i1 << ", " << f1 << ", " << s1 << " )" << std::endl;

    i1 = 576876;

    const auto& [i2, f2, s2] = t;
    std::cout << "( " << i2 << ", " << f2 << ", " << s2 << " )" << std::endl;

    return 0;
}
```

[Example](https://www.godbolt.org/z/5v8zb998o)

[Structured bindings : cppreference](https://en.cppreference.com/w/cpp/language/structured_binding)

## Links

- [Previous Page : Templates](/content/part5/tasks/templates.md)
- [Next Page : Concepts](/content/part5/tasks/concepts.md)
- [Content](/content/README.md)
- [HOME](/README.md)
