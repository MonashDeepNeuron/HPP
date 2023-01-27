# Concepts

## Contents

- [Concepts](#concepts)
  - [Contents](#contents)
  - [Task 4](#task-4)
    - [Task 4.1 : Limitations to templates](#task-41--limitations-to-templates)
    - [Task 4.2 : What is a Concept?](#task-42--what-is-a-concept)
    - [Task 4.3 : Constrained templates](#task-43--constrained-templates)
    - [Task 4.4 : Requires expressions](#task-44--requires-expressions)
      - [Task 4.4.1 : Requires expression](#task-441--requires-expression)
      - [Task 4.4.2 : Compound requirements](#task-442--compound-requirements)
    - [Task 4.5 : Constrained variables](#task-45--constrained-variables)
  - [Assignment 2](#assignment-2)
    - [Requirements](#requirements)
    - [Bonus](#bonus)
    - [Submitting](#submitting)
  - [Links](#links)

## Task 4

### Task 4.1 : Limitations to templates

Templates are extremely powerful allow us to create reusable and extendible code however there is a caveat to this. Take for example our `Point` class from Tasks 1-2. `Point` just takes a single type `T`. This can be absolutely any type. This can become a problem though later for the user. Say we have a `Point<std::string>`. This will cause an error for the user of our `Point` class if they try to take two `Point<std::string>` because `-` is not supported by `std::string`. This can be a major problem as the error produced can be ambiguous to the user and require looking at the source code in depth to diagnose.

```cxx
/// ... Point implementation

using namespace std::literals;

auto main() -> int
{
   auto p1 = Point{ "Hello"s, "Hi"s };
   auto p2 = Point{ "Goobye"s, "Bye"s };

   auto p3 = p1 - p2;

   std::cout << p3 << std::endl;

    return 0;
}
```

The error output (by GCC). As we can see it is verbose and delves into many of the attempts to make it work, and this is for a simple class.

```sh
<source>: In instantiation of 'constexpr Point<typename std::common_type<T, U>::type> Point<T>::operator-(const Point<U>&) [with U = std::__cxx11::basic_string<char>; T = std::__cxx11::basic_string<char>; typename std::common_type<T, U>::type = std::__cxx11::basic_string<char>]':
<source>:96:19:   required from here
<source>:61:62: error: no match for 'operator-' (operand types are 'std::__cxx11::basic_string<char>' and 'const std::__cxx11::basic_string<char>')
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                            ~~^~~~~
In file included from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/string:47,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/locale_classes.h:40,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/ios_base.h:41,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/ios:42,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/ostream:38,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/iostream:39,
                 from <source>:1:
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:621:5: note: candidate: 'template<class _IteratorL, class _IteratorR> constexpr decltype ((__y.base() - __x.base())) std::operator-(const reverse_iterator<_IteratorL>&, const reverse_iterator<_IteratorR>&)'
  621 |     operator-(const reverse_iterator<_IteratorL>& __x,
      |     ^~~~~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:621:5: note:   template argument deduction/substitution failed:
<source>:61:62: note:   'std::__cxx11::basic_string<char>' is not derived from 'const std::reverse_iterator<_IteratorL>'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                            ~~^~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:1778:5: note: candidate: 'template<class _IteratorL, class _IteratorR> constexpr decltype ((__x.base() - __y.base())) std::operator-(const move_iterator<_IteratorL>&, const move_iterator<_IteratorR>&)'
 1778 |     operator-(const move_iterator<_IteratorL>& __x,
      |     ^~~~~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:1778:5: note:   template argument deduction/substitution failed:
<source>:61:62: note:   'std::__cxx11::basic_string<char>' is not derived from 'const std::move_iterator<_IteratorL>'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                            ~~^~~~~
<source>:61:71: error: no match for 'operator-' (operand types are 'std::__cxx11::basic_string<char>' and 'const std::__cxx11::basic_string<char>')
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                                     ~~^~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:621:5: note: candidate: 'template<class _IteratorL, class _IteratorR> constexpr decltype ((__y.base() - __x.base())) std::operator-(const reverse_iterator<_IteratorL>&, const reverse_iterator<_IteratorR>&)'
  621 |     operator-(const reverse_iterator<_IteratorL>& __x,
      |     ^~~~~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:621:5: note:   template argument deduction/substitution failed:
<source>:61:71: note:   'std::__cxx11::basic_string<char>' is not derived from 'const std::reverse_iterator<_IteratorL>'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                                     ~~^~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:1778:5: note: candidate: 'template<class _IteratorL, class _IteratorR> constexpr decltype ((__x.base() - __y.base())) std::operator-(const move_iterator<_IteratorL>&, const move_iterator<_IteratorR>&)'
 1778 |     operator-(const move_iterator<_IteratorL>& __x,
      |     ^~~~~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:1778:5: note:   template argument deduction/substitution failed:
<source>:61:71: note:   'std::__cxx11::basic_string<char>' is not derived from 'const std::move_iterator<_IteratorL>'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                                     ~~^~~~~
<source>:61:77: error: no matching function for call to 'Point<std::__cxx11::basic_string<char> >::Point(<brace-enclosed initializer list>)'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                                             ^
<source>:20:15: note: candidate: 'constexpr Point<T>::Point(Point<T>&&) [with T = std::__cxx11::basic_string<char>]'
   20 |     constexpr Point(Point&& p) noexcept
      |               ^~~~~
<source>:20:15: note:   candidate expects 1 argument, 2 provided
<source>:16:15: note: candidate: 'constexpr Point<T>::Point(const Point<T>&) [with T = std::__cxx11::basic_string<char>]'
   16 |     constexpr Point(const Point& p) noexcept
      |               ^~~~~
<source>:16:15: note:   candidate expects 1 argument, 2 provided
<source>:12:5: note: candidate: 'constexpr Point<T>::Point(T, T) [with T = std::__cxx11::basic_string<char>]'
   12 |     Point(T x, T y) noexcept
      |     ^~~~~
<source>:12:5: note:   conversion of argument 1 would be ill-formed:
<source>:9:15: note: candidate: 'constexpr Point<T>::Point() [with T = std::__cxx11::basic_string<char>]'
    9 |     constexpr Point() = default;
      |               ^~~~~
<source>:9:15: note:   candidate expects 0 arguments, 2 provided
ASM generation compiler returned: 1
<source>: In instantiation of 'constexpr Point<typename std::common_type<T, U>::type> Point<T>::operator-(const Point<U>&) [with U = std::__cxx11::basic_string<char>; T = std::__cxx11::basic_string<char>; typename std::common_type<T, U>::type = std::__cxx11::basic_string<char>]':
<source>:96:19:   required from here
<source>:61:62: error: no match for 'operator-' (operand types are 'std::__cxx11::basic_string<char>' and 'const std::__cxx11::basic_string<char>')
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                            ~~^~~~~
In file included from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/string:47,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/locale_classes.h:40,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/ios_base.h:41,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/ios:42,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/ostream:38,
                 from /opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/iostream:39,
                 from <source>:1:
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:621:5: note: candidate: 'template<class _IteratorL, class _IteratorR> constexpr decltype ((__y.base() - __x.base())) std::operator-(const reverse_iterator<_IteratorL>&, const reverse_iterator<_IteratorR>&)'
  621 |     operator-(const reverse_iterator<_IteratorL>& __x,
      |     ^~~~~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:621:5: note:   template argument deduction/substitution failed:
<source>:61:62: note:   'std::__cxx11::basic_string<char>' is not derived from 'const std::reverse_iterator<_IteratorL>'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                            ~~^~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:1778:5: note: candidate: 'template<class _IteratorL, class _IteratorR> constexpr decltype ((__x.base() - __y.base())) std::operator-(const move_iterator<_IteratorL>&, const move_iterator<_IteratorR>&)'
 1778 |     operator-(const move_iterator<_IteratorL>& __x,
      |     ^~~~~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:1778:5: note:   template argument deduction/substitution failed:
<source>:61:62: note:   'std::__cxx11::basic_string<char>' is not derived from 'const std::move_iterator<_IteratorL>'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                            ~~^~~~~
<source>:61:71: error: no match for 'operator-' (operand types are 'std::__cxx11::basic_string<char>' and 'const std::__cxx11::basic_string<char>')
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                                     ~~^~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:621:5: note: candidate: 'template<class _IteratorL, class _IteratorR> constexpr decltype ((__y.base() - __x.base())) std::operator-(const reverse_iterator<_IteratorL>&, const reverse_iterator<_IteratorR>&)'
  621 |     operator-(const reverse_iterator<_IteratorL>& __x,
      |     ^~~~~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:621:5: note:   template argument deduction/substitution failed:
<source>:61:71: note:   'std::__cxx11::basic_string<char>' is not derived from 'const std::reverse_iterator<_IteratorL>'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                                     ~~^~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:1778:5: note: candidate: 'template<class _IteratorL, class _IteratorR> constexpr decltype ((__x.base() - __y.base())) std::operator-(const move_iterator<_IteratorL>&, const move_iterator<_IteratorR>&)'
 1778 |     operator-(const move_iterator<_IteratorL>& __x,
      |     ^~~~~~~~
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/bits/stl_iterator.h:1778:5: note:   template argument deduction/substitution failed:
<source>:61:71: note:   'std::__cxx11::basic_string<char>' is not derived from 'const std::move_iterator<_IteratorL>'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                                     ~~^~~~~
<source>:61:77: error: no matching function for call to 'Point<std::__cxx11::basic_string<char> >::Point(<brace-enclosed initializer list>)'
   61 |     { return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }
      |                                                                             ^
<source>:20:15: note: candidate: 'constexpr Point<T>::Point(Point<T>&&) [with T = std::__cxx11::basic_string<char>]'
   20 |     constexpr Point(Point&& p) noexcept
      |               ^~~~~
<source>:20:15: note:   candidate expects 1 argument, 2 provided
<source>:16:15: note: candidate: 'constexpr Point<T>::Point(const Point<T>&) [with T = std::__cxx11::basic_string<char>]'
   16 |     constexpr Point(const Point& p) noexcept
      |               ^~~~~
<source>:16:15: note:   candidate expects 1 argument, 2 provided
<source>:12:5: note: candidate: 'constexpr Point<T>::Point(T, T) [with T = std::__cxx11::basic_string<char>]'
   12 |     Point(T x, T y) noexcept
      |     ^~~~~
<source>:12:5: note:   conversion of argument 1 would be ill-formed:
<source>:9:15: note: candidate: 'constexpr Point<T>::Point() [with T = std::__cxx11::basic_string<char>]'
    9 |     constexpr Point() = default;
      |               ^~~~~
<source>:9:15: note:   candidate expects 0 arguments, 2 provided
Execution build compiler returned: 1
```

[Example](https://www.godbolt.org/z/P9b3EMGdY)

To address this C++20 introduced concepts. A mechanism for imposing constraints on types.

### Task 4.2 : What is a Concept?

A concepts is a set of conditions and requirements imposed on a type that is checked at compile time and evaluates as a Boolean. Before C++20, template metaprogramming and SFINAE where used to statically impose constraints on types but they had limitations and were highly verbose. Concepts allow us to define syntactic constraints on a template type and then impose those constraints on other types. Concepts are introduced using a template declaration followed by a concept declaration (similar to a class declaration but replace the keyword `class` with `concept`). Concepts can be composed of other concepts using `||` and `&&` (holding similar semantics to there Boolean equivalents). It is difficult to create meaningful concepts as one, they are very new to both C++ but also programming in general, instead try and use the concepts defined by the standard library; from the `<concepts>` header, first and impose them on a case by case basis using the techniques we are going to learn below.

```cxx
#include <concepts>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

/// Concept defining a type that can be hashed using `std::hash`
template<typename H>
concept Hashable = requires (H a)
{
    { std::hash<H>{}(a) } -> std::convertible_to<std::size_t>;
};

struct NotHashable {};

using namespace std::literals;

auto main() -> int
{
   std::cout << std::boolalpha;
   std::cout << "Is Hashable<int>:          " << Hashable<int> << "  : std::hash<int>{}(69)               = " << std::hash<int>{}(69) << std::endl;
   std::cout << "Is Hashable<float>:        " << Hashable<float> << "  : std::hash<float>{}(4.5756f)        = " << std::hash<float>{}(4.5756f) << std::endl;
   std::cout << "Is Hashable<double>:       " << Hashable<double> << "  : std::hash<double>{}(-0.0036565764) = " << std::hash<double>{}(-0.0036565764) << std::endl;
   std::cout << "Is Hashable<std::string>:  " << Hashable<std::string> << "  : std::hash<std::string>{}()         = " << std::hash<std::string>{}(""s) << std::endl;
   std::cout << "Is Hashable<NotHashable>:  " << Hashable<NotHashable> << std::endl;

    return 0;
}
```

[Example](https://www.godbolt.org/z/Px75v8ssf)

- [`<concepts>` : cppreference](https://en.cppreference.com/w/cpp/concepts)
- [Constraints and concepts : cppreference](https://en.cppreference.com/w/cpp/language/constraints)

### Task 4.3 : Constrained templates

Concepts are easiest to use when constraining templates type parameters. Instead of the using the keyword `typename` when can instead use a concept. This will impose the rules on the template type at the point of instantiation. We can see this best with our `Point` class. Being that a 'point' is a numerical value in a field; say coordinates on a cartesian plane we might want to restrict the type parameter `T` of `Point` to a number type. C++'s concepts library already has a concept for this called `std::integral`. Lets impose this new template type parameter constraint on `T`.

```cxx
template<std::integral T>
class Point
{
    /// ... implementation
};

using namespace std::literals;

auto main() -> int
{
   auto p1 = Point{ "Hello"s, "Hi"s };

    return 0;
}
```

While C++ error messages aren't the most readable as the compiler tries many different things, amongst the errors is one stating 'template constraint failed ...'. This indicates to use that `std::string` is not an appropriate type for `Point` without needed to try and subtract two `Point<std::string>` or any other operation on it. The instantiation failed at construction.

```sh
# ... other error info

<source>: In substitution of 'template<class T> Point(T, T)-> Point<T> [with T = std::__cxx11::basic_string<char>]':
<source>:94:37:   required from here
<source>:13:5: error: template constraint failure for 'template<class T>  requires  integral<T> class Point'
<source>:13:5: note: constraints not satisfied
In file included from <source>:1:
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/concepts: In substitution of 'template<class T>  requires  integral<T> class Point [with T = std::__cxx11::basic_string<char>]':
<source>:13:5:   required by substitution of 'template<class T> Point(T, T)-> Point<T> [with T = std::__cxx11::basic_string<char>]'
<source>:94:37:   required from here
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/concepts:100:13:   required for the satisfaction of 'integral<T>' [with T = std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >]
/opt/compiler-explorer/gcc-12.2.0/include/c++/12.2.0/concepts:100:24: note: the expression 'is_integral_v<_Tp> [with _Tp = std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >]' evaluated to 'false'
  100 |     concept integral = is_integral_v<_Tp>;

# ... Other error info
```

[Example](https://www.godbolt.org/z/1f1x8MTer)

[`std::integral` : cppreference](https://en.cppreference.com/w/cpp/concepts/integral)

### Task 4.4 : Requires expressions

The is a slight problem with our reformed `Point` class. It no longer can accept floating point types as they are not considered integrals in C++. Instead we need to constraint `Point` to a type `T` by creating a conjunction (`&&`) or disjunction (`||`) of multiple concepts. To do this we use a requires clause. Requires clause are introduced just after (often syntactically below) a template declaration and consist of a list of requirements in the form of a Boolean concept expression. We can create a disjunction of the `std::integral` and `std::floating_point` allowing floating point types and integral types to be valid `T` for `Point`.

```cxx
template<typename T>
    requires std::integral<T> || std::floating_point<T>
class Point
{
    /// ... implementation
};

auto main() -> int
{
   auto p1 = Point{ 0.567, 45.657 };
   auto p2 = Point{ 1, 9 };

   std::cout << p1 + p2 << std::endl;
   std::cout << p1 - p2 << std::endl;

    return 0;
}
```

> Note: We could specify a more desirable constraint using the `std::is_arithmetic_v` type trait as a concept combines the two ideas better semantically but fine tuning `Point` can be an exercise for you.

[Example](https://www.godbolt.org/z/55dhT6W6j)

- [`std::floating_point` : cppreference](https://en.cppreference.com/w/cpp/concepts/floating_point)
- [`requires` clause : cppreference](https://en.cppreference.com/w/cpp/language/constraints#:~:text=on%20constraint%20normalization.-,Requires%20clauses,-The%20keyword)

#### Task 4.4.1 : Requires expression

Sometimes more complicated requirements need to be specified in order to fine the allowed behaviour of the program. Require expressions allow for mock values of template types to bne created and specify patterns that a value of the type parameter must provide. In the case of our `Point` class, we may want to also allow other types that support `+` and `-` binary operator overloads. Because this check depends on the type parameter of another `Point` we can't declare it at the requires clause at the template declaration of `Point`. Instead we need to create a requires clause at the operator overloads template declaration. We then declare our requires expression, enforcing the semantic and syntactic rules on the type. We can declare as many of these rules in a requires expression as we like. For `Point` we will ensure that for a value of type `T` called `a` and for a value of type `U` of name `b`, `a + b` and `a - b` is valid.

```cxx
/// ... Point details

template<typename U>
    requires requires (T a, U b)
    {
        a + b;
    }
constexpr auto
operator+ (const Point<U>& p) 
    noexcept -> Point<typename std::common_type<T, U>::type>
{ return Point<typename std::common_type<T, U>::type>{ x + p.x, y + p.y }; }

template<typename U>
    requires requires (T a, U b)
    {
        a - b;
    }
constexpr auto
operator- (const Point<U>& p) 
    noexcept -> Point<typename std::common_type<T, U>::type>
{ return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }

/// ... Point details
```

> Note: The double `requires requires` notation is called an ad-hoc constraint. The first `requires` introduces a requires clause which can have concepts, conjunctions, disjunctions or requires expressions. The second `require` introduces a requires expression which takes a similar syntactic form to functions.

[Example](https://www.godbolt.org/z/763Y6fjjc)

[`requires` expression : cppreference](https://en.cppreference.com/w/cpp/language/requires)

#### Task 4.4.2 : Compound requirements

We can also apply constraints on the expressions within a requires expression, ensuring the types or properties these expressions will have. These are called compound expressions, which we create by wrapping our individual rules from a requires expression in braces and use a `->` followed by a constraint on the return type of the expression.

```cxx
/// ... Point details

template<typename U>
    requires requires (T a, U b)
    {
        { a + b } -> std::same_as<typename std::common_type<T, U>::type>;
    }
constexpr auto
operator+ (const Point<U>& p) 
    noexcept -> Point<typename std::common_type<T, U>::type>
{ return Point<typename std::common_type<T, U>::type>{ x + p.x, y + p.y }; }

template<typename U>
    requires requires (T a, U b)
    {
        { a - b } -> std::same_as<typename std::common_type<T, U>::type>;
    }
constexpr auto
operator- (const Point<U>& p) 
    noexcept -> Point<typename std::common_type<T, U>::type>
{ return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }

/// ... Point details
```

[Example](https://www.godbolt.org/z/nqxoE7466)

[Compound requirements : cppreference](https://en.cppreference.com/w/cpp/language/requires#:~:text=%3B%20%0A%7D%3B-,Compound%20Requirements,-A%20compound%20requirement)

[Version 3 of `Point`](/content/chapter5/tasks/concepts.md)

### Task 4.5 : Constrained variables

We can also use concepts to constrain variables declared with the `auto` specifier. Gives a more robust option for constraining function and method parameters without the need for template declarations or requires clauses.

```cxx
#include <concepts>
#include <iostream>

auto println(const std::integral auto& v) -> void
{ std::cout << v << std::endl; }

auto main() -> int
{
    println(9);
    // println(46.567);  ///< fails

    return 0;
}
```

[Example](https://www.godbolt.org/z/vcGW1qPY9)

> Note: We've applied concepts at the user definition level for classes. These concepts [ideas] can be applied to template functions as well. They are also the basic for defining your own concepts.

## Assignment 2

Having learnt about classes, templates and concepts I want you to reimplement your `Triple` class so that it behaves more like a standard type and has a more sophisticated implementation and interface. Similar to Assignment 1, you will submit using a pull request on GitHub to this repo.

### Requirements

- Must be templated for a single type `T`
- A way to add two points of different `T`
- A way to subtract two points of different `T`
- A way to multiply a point by a scalar of different `T`
- A way to divide a point by a scalar of different `T`
- A way to be print a formatted output using `std::cout`
- Using concepts ensure that `T` satisfies only:
  - `std::integral`
- or
  - `std::floating_point`
- or
  - `T` and `U` support
    - `T + U`
    - `T - U`
    - `U * T`
    - `T / U`
  - and doesn't support
    - `is_pointer`
    - `is_reference`
    - `is_enum` etc.
- and
  - `T` supports `<<` to an `std::ostream`

> Note: Let me know if the concept requirements are confusing

### Bonus

- A way to be created using input from `std::cin`
- Allow three different type parameter; say `T`, `U` and `V` for the member variables while still maintaining the base requirements [hard]

### Submitting

You can use Godbolt or bpt to build and test your struct. Once you have created your implementation:

- clone this repo using `git clone https://github.com/MonashDeepNeuron/HPP.git`.
- create a new branch using `git checkout -b triple/<your-name>`.
- create a folder in the `/content/chapter5` directory called `submissions/<your-name>`.
- Copy your mini project into this directory (bpt setup, cmake scripts etc.) with a `README.md` or comment in the code on how to run the program (verify it still works). There is a sample header file in `/templates` that you can use.
- Go to <https://github.com/MonashDeepNeuron/HPP/pulls> and click 'New pull request'.
- Change the branches in the drop down so that your branch is going into `main` and `Create new pull request.
- Give the pull request a title and briefly describe what you were able to implement and any struggles you had.
- On the right side-panel, under the 'Assignees' section, click the cog and assign me.
- Click 'Create pull request' and I'll take it from there.

> Note: If you created a GodBolt instance, put the link in a comment at the top of the file (under your copy comments). This is generated by clicking the `share` button in the top-right-most corner of the webpage and clicking the 'short link' option.

This, ideally should be submitted before our meetup on 18/01/2023. Please note that I will be asking each of you a few questions about how you went and your thought processes in throughout the implementation.

## Links

- [Previous Page : Generics](/content/chapter5/tasks/generics.md)
- [Back to Chapter 5](/content/chapter5/README.md)
- [Content](/content/README.md)
- [HOME](/README.md)
