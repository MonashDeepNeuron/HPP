# Unions

## Contents

- [Unions](#unions)
  - [Contents](#contents)
  - [Task 4](#task-4)
    - [Task 4.1 : Unions](#task-41--unions)
    - [Task 4.2 : Limitations](#task-42--limitations)
    - [Task 4.3 : Type Safe Algebraic Data Types](#task-43--type-safe-algebraic-data-types)
      - [Task 4.3.1 : Option](#task-431--option)
      - [Task 4.3.2 : Variant](#task-432--variant)
  - [Links](#links)

## Task 4

### Task 4.1 : Unions

Unions are a special kind of type known as an algebraic data type. This means the type of a union object can vary between a small list of possible types. This allows for a single type to be one of many possible types that can change throughout the lifetime of the program. The members of a union occupy the same memory space, thus the size of a union is the size of the largest possible member. Constructing a union object will always need to construct the first variant. Accessing the non-activate member is UB.

```cxx
#include <iostream>

union Sym
{
    int num;
    float float32;
    const char* str;
};

auto main() -> int
{
    Sym sym {8};
    std::cout << sym.num << std::endl;

    sym.float32 = 5.6f;
    std::cout << sym.float32 << std::endl;

    sym.str = "Hello";
    std::cout << sym.str << std::endl;

    return 0;
}
```

[Example 64](https://www.godbolt.org/z/zGeTs8ozn)

[Unions : cppreference](https://en.cppreference.com/w/cpp/language/union)

### Task 4.2 : Limitations

Unions are quite powerful but have a few limitations.

- There is no default mechanism for inspecting the current variant of a union.
- They can have member functions including constructors and destructors but cannot have virtual functions (more in [Part 5](/content/part5/README.md)).
- They cannot have base classes nor can be used as a base class.
- They cannot have non-static members of reference types.
- If any variant types have a non-trivial special member function it is deleted for the union and must be declared explicitly for the union type.

```cxx
#include <iostream>
#include <string>
#include <array>
 
union S
{
    std::string str;
    std::array<int, 5> arr;
    ~S() {}                 ///< Variant `str` has non-trivial destructor 
};
 
int main()
{
    S s = {"Hello, world"};

    std::cout << "s.str = " << s.str << '\n';
    s.str.~basic_string();                      ///< Explicity destroy string

    s.arr = std::array<int, 5>{1, 2, 3, 4, 5};  ///< Explicity create array
    s.arr[1] = 5675;                            ///< Assign 2nd element to 3

    for (auto& v : s.arr)
        std::cout << v << ' ';
    std::cout << std::endl;
    
}
```

[Example 65](https://www.godbolt.org/z/rqPz5hK45)

### Task 4.3 : Type Safe Algebraic Data Types

While unions are powerful, they are very error prone and can lead to hard to diagnose bugs. Instead, in C++17 type-safe algebraic types that more intuitive to use and far safer.

#### Task 4.3.1 : Option

One of the most common uses of algebraic data types is `std::optional` which can represent a type that may _optionally_ contain some value or non at all. `std::optional` is often used as the return type if a function that might expectedly fail. `std::optional` can contain any type or has the type of `std::nullopt`.

```cxx
#include <cmath>
#include <limits>
#include <iostream>
#include <optional>
#include <string>

auto divide(int x, int y)
    -> std::optional<float>
{
    if (y == 0)
        return std::nullopt;
    
    return std::optional<float>{x / static_cast<float>(y)};
}

auto main() -> int
{

    auto opt1 = divide(4, 5);
    std::cout << opt1.value() << std::endl;

    /// Given `opt2` and `opt3` have the value `std::nullopt`
    /// the value passed to `.value_or()` is returned
    auto opt2 = divide(2, 0);
    std::cout << opt2.value_or(std::numeric_limits<float>::quiet_NaN()) << std::endl;

    auto opt3 = divide(4656, 0);
    std::cout << opt3.value_or(0.1f) << std::endl;

    return 0;
}
```

[Example 66](https://www.godbolt.org/z/aGvnrYPzn)

[`std::optional<T>` : cppreference](https://en.cppreference.com/w/cpp/utility/optional)

#### Task 4.3.2 : Variant

The is also a more generic algebraic data type in C++ called `std::variant` which is implemented as a tagged union; that is, you are able to inspect which type is currently active, validate the state of the variant and perform a simply form of pattern matching. Empty variants can be simulated by using the `std::monospace` type variant.

```cxx
#include <iostream>
#include <string>
#include <variant>
#include <vector>

/// Used to perform pattern matching
template<class... Ts> struct match : Ts... { using Ts::operator()...; };

using Sym = std::variant<int, float, std::string, long>;

auto main() -> int
{
    std::vector<Sym> syms = {8, "Hello", 6.8f, 4, "Bye", 857565L};
    for (auto& var : syms)
    {
        std::visit(match{
            [](int i){ std::cout << "Sym: <Integer> = " << i << std::endl; },
            [](float f){ std::cout << "Sym: <Float> = " << f << std::endl; },
            [](std::string s){ std::cout << "Sym: <String> = " << s << std::endl; },
            [](auto&& o){ std::cout << "Sym: <Other> = " << o << std::endl; }
        }, var);
    }

    return 0;
}
```

[Example 67](https://www.godbolt.org/z/fzMKbjWW3)

[`std::variant<Ts..>` : cppreference](https://en.cppreference.com/w/cpp/utility/variant)

[`std::visit()` : cppreference](https://www.godbolt.org/z/aGvnrYPzn)

## Links

- [Previous Page : Enumerations](/content/part4/tasks/enums.md)
- [Next Page : Unions](/content/part4/tasks/structs.md)
- [Content](/content/README.md)
- [HOME](/README.md)
