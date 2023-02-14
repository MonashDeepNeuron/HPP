# Structures

Structures (structs) are fundamental to developing with C++. They allow for creating custom types that can have member variables, and member functions (methods). They allow for packing any amalgamation of data into a single type. Structures are created using the `struct` keyword. To access the members and methods of a struct the member access operator `.` is used. For pointers to struct types, the pointer member access operator `->` is used.

> Note: The definition of a structure must have an `;` after the last brace.

```cxx
#include <iostream>
#include <memory>

struct PairInt
{
    int first;
    int second;

    /// Adds members of two `PairInt`
    constexpr auto
    add(const PairInt& o)
        const noexcept
        -> PairInt
    { return PairInt{first + o.first, second + o.second}; }

    /// Overload `+~ cleaner `PairInt::add` call
    friend constexpr auto
    operator+ (const PairInt& x, const PairInt& y)
        noexcept
        -> PairInt
    { return x.add(y); }

    /// Overload `<<` for printing
    friend auto
    operator<< (std::ostream& os, const PairInt& v)
        -> std::ostream&
    {
        os << "(.first: " << v.first << ", .second: " << v.second << ")";
        return os;
    }
};

auto main() -> int
{
    auto a = PairInt{5, 7};
    auto b = PairInt{.first = 2, .second = 9};  ///< Named aggregate initialisation
    auto p = std::addressof(b);                 ///< Pointer to struct type

    std::cout << "a = " << a << std::endl;      ///< `PairInt` works with `std::cout`
    std::cout << "b = " << b << std::endl;

    std::cout << "a + b = " << a + b << std::endl;      ///< Call to overloaded `+`
    std::cout << "a + c = " << a + *p << std::endl;     ///< Pointer to structs works like regular pointers

    std::cout << "a.add(b) = " << a.add(b) << std::endl;    ///< Method access
    std::cout << "p->add(a) = " << p->add(a) << std::endl;  ///< Pointer member access 

    return 0;
}
```

[Example](https://www.godbolt.org/z/6MbYMGGMz)

> Note: Ignore the `friend` keyword for now.
