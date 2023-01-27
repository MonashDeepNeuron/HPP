# Templates

## Contents

- [Templates](#templates)
  - [Contents](#contents)
  - [Task 2](#task-2)
    - [Task 2.1 : Why templates?](#task-21--why-templates)
    - [Task 2.2 : What are templates?](#task-22--what-are-templates)
    - [Task 2.3 : Template Parameters](#task-23--template-parameters)
    - [Task 2.4 : Template Functions](#task-24--template-functions)
    - [Task 2.5 : Template Classes](#task-25--template-classes)
    - [Task 2.5.1 : Class Template Methods](#task-251--class-template-methods)
    - [Task 2.6: Template Variables](#task-26-template-variables)
    - [Task 2.7 : Template Metaprogramming Basics](#task-27--template-metaprogramming-basics)
  - [Links](#links)

## Task 2

### Task 2.1 : Why templates?

Everything we have learnt about C++ relies on the fact the type of any object must be known at compile time. This can be quite constricting on the kinds of programs we are able to right. Just think back to Assignment 1 where you were tasked with creating a class called `Triple` with a single underlying type (either `int`, `float` or `double`). Imagine you create `TripleInt` but now had to create a class with the same interface but for the other underlying types (`float` and `double` in this case) that you did not implement (well some of you may have). This can dramatically increase code duplication. One might think to solve this through class inheritance. Somehow define a common abstract interface that derived classes could inherit from and then override the methods in order to implement the interface for each underlying type. However, this requires more work still as anyone that wants to implement `Triple` would have to inherit from it and implement the same interface and logic for there own underlying type. Another caveat is this requires every `Triple` object to have a vtable to there underlying methods resulting in dynamic dispatch of method calling which, is something that has a lot of runtime overhead. The real solution is to have a single interface that can working for any desired type. This is where templates come in.

### Task 2.2 : What are templates?

Templates can be thought of as blueprints for function, variable or class. They allow for defining interfaces in terms of template parameters which can be types or compile-time variables. Templates can then be instantiated for a given set of valid template parameters which results in the function, variable or class being fully defined meaning they can now be instantiated themselves. Templates are created by using a `template<>` declaration above the definition of a function, variable or class with the template parameters being specified within the angle brackets (`<>`).

[Templates : cppreference](https://en.cppreference.com/w/cpp/language/templates)

### Task 2.3 : Template Parameters

There are three categories of template parameters; type, non-type and template-template. We wont cover template-template parameters as they are used for advanced specialisation. Type template parameters are template parameters that accept a type as an argument. These are used to create generic functions, variables and classes that can be defined in terms of many different types. These are the most common use of templates. Type arguments are declared as `template<typename T>` with T being the name of the type argument and will be an alias to the type we later instantiate the template with. Non-type arguments are used to pass values at compile time to a function, variable or class. The type of a non-type template argument must be explicitly declared eg. `template<int N>`, Non-type template arguments are constant and thus cannot be mutated. Here is an example of a template declaration that takes type and non-type template arguments.

```cxx
template<typename T, std::size_t N>
/// ... template entity details
```

This is the template signature of `std::array`.

[Template Arguments : cppreference](https://en.cppreference.com/w/cpp/language/template_parameters)

### Task 2.4 : Template Functions

To begin, we will look at defining template functions. Template functions are defined identically to regular functions except that before the functions signature we use a template declaration. As we can see below, regardless of the type of the array or the its size we can call `print<>()`. Also, thanks to C++17 we don't have to call it with specific template arguments as the can be deduced from the array itself.

```cxx
#include <array>
#include <iostream>
#include <string>

template<typename T, std::size_t N>
auto print(const std::array<T, N>& arr) -> void
{
    std::cout << "[ ";

    for (auto n { N }; const auto& e : arr)
        if (--n > 0)
            std::cout << e << ", ";
        else
            std::cout << e;

    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto a1 = std::to_array<int>({ 1, 2, 3, 4, 5 });
    auto a2 = std::to_array<double>({ 1.576, 0.0002, 3756348.34646, 5e-14, 465.7657, 358.0, 237437.456756 });
    auto a3 = std::to_array<std::string>({ "John", "Anna", "Grace", "Bob" });

    print<int, 5>(a1);  ///< Explicit template argument instantiation
    print(a2);          ///< template argument deduction (same below)
    print(a3);

    return 0;
}
```

[Example](https://www.godbolt.org/z/WxsGsfna4)

[Function template : cppreference](https://en.cppreference.com/w/cpp/language/function_template)

### Task 2.5 : Template Classes

Template classes allow us to define generic types. Almost all of C++ standard library types are template classes, even `std::cout` which is a static instance of the class `std::basic_ostream<char>`. Template classes allow us to create a blueprint of a class and then instantiate the class definition which a chaptericular type. We can see this with out `Point` class from the previous task section. Now we define `Point` in terms of a template type `T` which we will specify later. This allows us to create `Point` objects of `float` and `double` as well while still only defining a single interface.

> Note: For copy and move constructors, the template type parameters can be elided as copy and move semantics must preserve the type. Converting constructors (a type of explicit constructor) are used to convert between template types.

```cxx
#include <iostream>
#include <utility>

template<typename T>
class Point
{
public:
    /// Default Constructor (Compiler Created)
    constexpr Point() = default;

    explicit constexpr
    Point(T x, T y) noexcept
        : x{ x }, y{ y }
    { }

    constexpr Point(const Point& p) noexcept
    : x{ p.x }, y{ p.y }
    { }

    constexpr Point(Point&& p) noexcept
        : x{ std::move(p.x) }
        , y{ std::move(p.y) }
    { p = Point(); }

    constexpr auto
    operator= (const Point& p) noexcept -> Point&
    {
        if (p != *this)
        {
            x = p.x;
            y = p.y;
        }

        return *this;
    }

    constexpr auto
    operator= (Point&& p) noexcept -> Point&
    {
        if (p != *this)
        {
            x = std::move(p.x);
            y = std::move(p.y);
        }

        return *this;
    }

    ~Point() noexcept = default;

    constexpr auto
    operator+ (const Point& p) noexcept -> Point
    { return Point{ x + p.x, y + p.y }; }

    constexpr auto
    operator- (const Point& p) noexcept -> Point
    { return Point{ x - p.x, y - p.y }; }

    constexpr auto
    operator== (const Point& p)
        noexcept -> bool
    { return (x == p.x) && (y == p.y); }

    constexpr auto
    operator!= (const Point& p)
    noexcept -> bool
    { return !(*this == p); }

    friend auto
    operator<< (std::ostream& os, const Point& p)
        noexcept -> std::ostream&
    { 
        os << "( "
        << p.x
        << ", "
        << p.y
        << " )";

        return os;
    }

private:
    T x;
    T y;
};


auto main() -> int
{
    auto p1 = Point<int>{ 2, 5 };
    auto p2 = Point{ 6, 7 };
    auto p3 = p1 + p2;
    auto p4 = Point<double>{ 5.6 , -0.007 };
    auto p5 = Point{ 4.576 , 24.012 };
    auto p6 = p4 - p5;

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << p4 << std::endl;
    std::cout << p5 << std::endl;
    std::cout << p6 << std::endl;

    return 0;
}
```

> Note: We could define `Point::x` and `Point::y` to be different types but this is unnecessary for now.

[Example](https://www.godbolt.org/z/nhbsbnE9b)

[Class Template : cppreference](https://en.cppreference.com/w/cpp/language/class_template)

### Task 2.5.1 : Class Template Methods

Just like how free functions can be templated, we can also specify methods of classes to be templated. This allows use to customize classes methods not just in terms of its template types and parameters but also in terms of templates of objects that we may need to pass to the method of a class. This useful for creating overloaded methods that are not just customized by type but also the template signature pattern they have.

You may have noticed that I did not add or subtract two `Point` of different type in the previous example. This is because `+` and `-` are only defined for `Point` of the same template. We can fix this with a templated method. There are a few other details we have to add in order for this to work. First we add the template specification for the other `Point<U>` argument (we can do the same for `==` and `!=`). We then us `std::common_type<T...>` to help deduce the arithmetic (an other) promotions between types. This is for promotions of say `int` to `double`. Finally, because the class `Point<U>` is a different instantiation of `Point` to `this` (ie. `Point<T>`), we have to specify all `Point<U>` of any `U` type as a friend class to `Point<T>`.

```cxx
/// ... Point details

template<typename U>
constexpr auto
operator+ (const Point<U>& p) 
    noexcept -> Point<typename std::common_type<T, U>::type>
{ return Point<typename std::common_type<T, U>::type>{ x + p.x, y + p.y }; }

template<typename U>
constexpr auto
operator- (const Point<U>& p) 
    noexcept -> Point<typename std::common_type<T, U>::type>
{ return Point<typename std::common_type<T, U>::type>{ x - p.x, y - p.y }; }

template<typename U>
constexpr auto
operator== (const Point<U>& p)
    noexcept -> bool
{ return (x == p.x) && (y == p.y); }

template<typename U>
constexpr auto
operator!= (const Point<U>& p)
noexcept -> bool
{ return !(*this == p); }

/// ... Point details

private:

    T x;
    T y;

    template<typename U>
    friend class Point;
```

> Note: The template argument names must be different then the outer template classes template argument names as this name (symbol) is still very much in scope.

[Example](https://www.godbolt.org/z/4WKKrMsqn)

- [Member templates](https://en.cppreference.com/w/cpp/language/member_template)
- [`std::common_type` : cppreference](https://en.cppreference.com/w/cpp/types/common_type)
- [Version 2 of `Point<T>`](/content/chapter5/examples/point-v2.hxx)

### Task 2.6: Template Variables

Is is also possible to define variables as templates. This allows for variables to take on different forms depending on the underlying type. Template variables are typically `static` or `constexpr` free variables or `static` members of a class. A common use of template variables is mathematical constants that have different underlying types. We can see this in use with `e<T>` and `std::numeric_limits<T>` members.

```cxx
#include <iomanip>
#include <iostream>
#include <numeric>

template<typename T>
constexpr T e = T(2.7182818284590452353602874713527);

auto main() -> int
{
    std::cout << std::setprecision(std::numeric_limits<long double>::max_digits10);
    std::cout << "True e            = 2.7182818284590452353602874713527" << std::endl;
    std::cout << "e<long double>    = " << e<long double> << std::endl;
    std::cout << "e<double>         = " << e<double> << std::endl;
    std::cout << "e<float>          = " << e<float> << std::endl;
    std::cout << "e<int>            = " << e<int> << std::endl;
    std::cout << "e<char>           = " << e<char> << std::endl;
    
    return 0;
}
```

> Note: Consequently, this is a good showcase of how quickly `float` and `double` loose precision.

[Example](https://www.godbolt.org/z/4eqKcTT4s)

- [Variable Templates : cppreference](https://en.cppreference.com/w/cpp/language/variable_template)
- [`std::numeric_limits` : cppreference](https://en.cppreference.com/w/cpp/types/numeric_limits)

### Task 2.7 : Template Metaprogramming Basics

We've seen a bit of metaprogramming in C++ already. Metaprogramming is the ability to influence the structure of your code at compile time using the language itself. Templates are a simple form of metaprogramming and allow us to change the behaviour of our code based on the types and values we instantiate our templates with. Using templates, the C++ standard library has many metaprogramming objects that allow us to customize our code even more. Most of the standard  libraries metaprogramming objects are in the form of type analysis from the `<type_traits>` header. These allow us to inspect the properties of any type (template or known) and customize based on the results. There is much more to metaprogramming that is beyond the scope of this course.

- [Metaprogramming Library : cppreference](https://en.cppreference.com/w/cpp/meta)
- [Compile-time rational arithmetic : cppreference](https://en.cppreference.com/w/cpp/numeric/ratio)
- [SFINAE : cppreference](https://en.cppreference.com/w/cpp/language/sfinae)
- [`<type_traits>` : cppreference](https://en.cppreference.com/w/cpp/header/type_traits)
- [`std::integer_sequence` : cppreference](https://en.cppreference.com/w/cpp/utility/integer_sequence)

## Links

- [Previous Page : Classes](/content/chapter5/tasks/classes.md)
- [Next Page : Generics](/content/chapter5/tasks/generics.md)
- [Content](/content/README.md)
- [HOME](/README.md)
