# Enumerations

## Section 3

### Section 3.1 : Enumerations

Enumerations (enums) are a distinct types whose value is one of a restricted range of named integral constants called enumerators. Enums allow for specify a type that may have a value of one of many possible named values. Enums have an underlying integral type where each enumerator is of the underlying type. Enums allow for the restriction of the possible values a type can hold. The value of the enumerators of an enum have begin at 0 and increment.

```cxx
#include <iostream>

enum Colour { Red, Green, Blue};

auto print_colour_name(Colour c)
    -> void
{
    switch (c)
    {
        case Red:
            std::cout << "Red\n";
            break;
        case Green:
            std::cout << "Green\n";
            break;
        case Blue:
            std::cout << "Blue\n";
            break;
        default:
            std::cout << "Not a colour\n";
            break;
    }
}

auto main() -> int
{
    Colour c1 {Red};            ///< Unscoped Initialisation
    Colour c2 {Colour::Green};  ///< Scoped Initialisation
    auto c3 {Colour::Blue};     ///< `auto` type deduction
    auto c4 {4};                ///< Non `Colour`

    print_colour_name(c1);
    print_colour_name(c2);
    print_colour_name(c3);
    print_colour_name(static_cast<Colour>(c4));

    return 0;
}
```

[Example](https://www.godbolt.org/z/8PMbxxehb)

[Enumerations : cppreference](https://en.cppreference.com/w/cpp/language/enum)

#### Section 3.1.2 : Underlying Types and Values

In C++ you can specify the underlying type and and value of an enum. To specify the type, the enum's identifier can be followed by a colon with a integral type. To specify the values an enums enumerators are aliasing for, the enumerator name can be followed by a assignment operator and the integral value.

- > Note: Not all enumerators have to have an explicit value if one or more other enumerators do.
- > Note: If an enumerator has an explicit value and the proceeding one is not specified, the proceeding one will assume the next value after the explicit enumerator.
- > Note: Enumerators can have the same underlying value.

```cxx
#include <iostream>

/// Enum `Colour` whose underlying type is `short`
enum Colour : short
{ Red, Green = 57, Blue};

auto print_colour_name(Colour c)
    -> void
{
    switch (c)
    {
        case Red:
            std::cout << "Red = ";
            break;
        case Green:
            std::cout << "Green = ";
            break;
        case Blue:
            std::cout << "Blue = ";
            break;
        default:
            std::cout << "Not a colour\n";
            return;
    }

    std::cout << static_cast<short>(c) << std::endl;
}

auto main() -> int
{
    Colour c1 {Red};            ///< Unscoped Initialisation
    Colour c2 {Colour::Green};  ///< Scoped Initialisation
    auto c3 {Colour::Blue};     ///< `auto` type deduction
    auto c4 {4};                ///< Non `Colour`

    print_colour_name(c1);
    print_colour_name(c2);
    print_colour_name(c3);
    print_colour_name(static_cast<Colour>(c4));

    return 0;
}
```

[Example](https://www.godbolt.org/z/c6E1vjzoK)

### Section 3.2 : Enum Class

Unscoped enums, which is all we have seen thus far can be implicitly converted into there underlying type. This can cause unwanted conversions. To accommodate for this C++ has _scoped enums_ which are declared as `enum class` (or `struct`). They cannot be implicitly converted there underlying type, they have `int` as there underlying type by default and can only be accessed using the names scope resolution operator (`::`) with the name being the name of the enum class.

```cxx
#include <iostream>

/// Enum class `Colour` whose underlying type is `short`
enum class Colour : short
{ Red, Green = 57, Blue};

auto print_colour_name(Colour c)
    -> void
{
    switch (c)
    {
        case Colour::Red:
            std::cout << "Red = ";
            break;
        case Colour::Green:
            std::cout << "Green = ";
            break;
        case Colour::Blue:
            std::cout << "Blue = ";
            break;
        default:
            std::cout << "Not a colour\n";
            return;
    }

    std::cout << static_cast<short>(c) << std::endl;
}

auto main() -> int
{
    // Colour c1 {Red};         ///< Unscoped Initialisation (error for `enum class`)
    Colour c2 {Colour::Green};  ///< Scoped Initialisation
    auto c3 {Colour::Blue};     ///< `auto` type deduction
    auto c4 {4};                ///< Non `Colour`

    // print_colour_name(c1);
    print_colour_name(c2);
    print_colour_name(c3);
    print_colour_name(static_cast<Colour>(c4));

    return 0;
}
```

[Example](https://www.godbolt.org/z/Kqs6rvvMr)
