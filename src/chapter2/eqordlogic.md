# Equality, Ordering and Logical Operators

## Contents

- [Equality, Ordering and Logical Operators](#equality-ordering-and-logical-operators)
  - [Contents](#contents)
  - [Task 6](#task-6)
    - [Task 6.1 : Equality](#task-61--equality)
    - [Task 6.2 : Ordering](#task-62--ordering)
    - [Task 6.3 : Spaceships and Ordering Types](#task-63--spaceships-and-ordering-types)
      - [Task 6.3.1 : Strong Ordering](#task-631--strong-ordering)
      - [Task 6.3.2 : Weak Ordering](#task-632--weak-ordering)
      - [Task 6.3.3 : Chapterial Ordering](#task-633--chapterial-ordering)
    - [Task 6.4 : Logical Operators](#task-64--logical-operators)
  - [Links](#links)

## Task 6

### Task 6.1 : Equality

A common operation in all of programming is to test for equality. In C++ primitive types are compared as arithmetic types, that is the systems ALU (Arithmetic and Logic Unit) will compare the bits of a value and return to the system whether the result is `true` or `false`.

Unlike JavaScript, C++ has a sense of strictly equal, that is two values are either equal or are not. To compare for equality or inequality of two values, C++ has the `==` and `!=` operators respectively.

- `a == b` - `true` if `a` equals `b` otherwise `false`
- `a != b` - `false` if `a` equals `b` otherwise `true`

```cxx
#include <iomanip>
#include <iostream>

auto main () -> int
{
    auto a {1};
    auto b {2};

    std::cout << std::boolalpha;
    std::cout << "a == b => " << (a == b) << std::endl;  ///< false
    std::cout << "a != b => " << (a != b) << std::endl;  ///< true

    std::cout << "a == a => " << (a == a) << std::endl;  ///< true
    std::cout << "a != a => " << (a != a) << std::endl;  ///< false
    std::cout << std::noboolalpha;
    return 0;
}
```

[Example](https://www.godbolt.org/z/EK14h6fhd)

### Task 6.2 : Ordering

Checking for equality is pretty straight forward. Some more interesting operations are the ordering operators. What is ordering? Ordering is a relationship of different values of the same type. Ordering is what gives numbers their sequence (`2 < 3`). Ordering operators allow use to check if some ordering condition is met.

- `<`  - Less than
- `>`  - Greater than
- `<=` - Less than or Equal
- `>=` - Greater than or Equal

```cxx
#include <iomanip>
#include <iostream>

auto main () -> int
{
    auto a {1};
    auto b {2};

    std::cout << std::boolalpha;
    std::cout << "a < b => " << (a < b) << std::endl;       ///< true
    std::cout << "a > b => " << (a > b) << std::endl;       ///< false

    std::cout << "a <= a => " << (a <= a) << std::endl;     ///< true
    std::cout << "a >= a => " << (a >= a) << std::endl;     ///< true

    std::cout << "a <= b => " << (a <= b) << std::endl;     ///< true
    std::cout << "a >= b => " << (a >= b) << std::endl;     ///< false
    std::cout << std::noboolalpha;
    return 0;
}
```

[Example](https://www.godbolt.org/z/v4EYf1n3j)

### Task 6.3 : Spaceships and Ordering Types

As of C++20 there as a new ordering operator introduced called the three-way-comparison operator or, the spaceship operator `<=>`. The spaceship operator different ordering types based on the strictness of the ordering.

- `(a <=> b) < 0` if `a < b`
- `(a <=> b) > 0` if `a > b`
- `(a <=> b) == 0` if `a == b`

`<=>` also returns an ordering category. This indicates the level of strictness for the ordered type.

|         Category        | Equivalent values are.. | Incomparable values are.. |
|:-----------------------:|:-----------------------:|:-------------------------:|
|  `std::strong_ordering` |    indistinguishable    |        not allowed        |
|   `std::weak_ordering`  |     distinguishable     |        not allowed        |
| `std::chapterial_ordering` |     distinguishable     |          allowed          |

- indistinguishable : if `a == b` then `f(a) == f(b)`
- distinguishable : if `a == b` then `f(a) != f(b)`
- `std::chapterial_ordering` can return `std::chapterial_ordering::unordered` eg. `/* anything */ <=> NaN == std::chapterial_ordering::unordered`.

> Note: floating point comparisons return `std::chapterial_ordering`

#### Task 6.3.1 : Strong Ordering

`std::strong_ordering` can have the values:

- `std::strong_ordering::less`
- `std::strong_ordering::equivalent`
- `std::strong_ordering::equal`
- `std::strong_ordering::greater`

and can be implicitly converted into `std::chapterial_ordering` or `std::weak_ordering`.

#### Task 6.3.2 : Weak Ordering

`std::weak_ordering` can have the values:

- `std::weak_ordering::less`
- `std::weak_ordering::equivalent`
- `std::weak_ordering::greater`

and can be implicitly converted into `std::chapterial_ordering`.

#### Task 6.3.3 : Chapterial Ordering

`std::chapterial_ordering` can have the values:

- `std::strong_ordering::less`
- `std::strong_ordering::equivalent`
- `std::strong_ordering::greater`
- `std::strong_ordering::unordered`

```cxx
#include <compare>
#include <iomanip>
#include <iostream>

auto main () -> int
{
    auto a {1};
    auto b {2};

    auto aa = a <=> a;
    auto ab = a <=> b;

    std::cout << std::boolalpha;
    std::cout << "((a <=> a) < 0) => " << ((a <=> a) < 0) << std::endl;      ///< false
    std::cout << "((a <=> a) == 0) => " << ((a <=> a) == 0) << std::endl;    ///< true
    std::cout << "((a <=> a) > 0) => " << ((a <=> a) > 0) << std::endl;      ///< false

    std::cout << "((a <=> b) < 0) => " << ((a <=> b) < 0) << std::endl;      ///< true
    std::cout << "((a <=> b) == 0) => " << ((a <=> b) == 0) << std::endl;    ///< false
    std::cout << "((a <=> b) > 0) => " << ((a <=> b) > 0) << std::endl;      ///< false

    return 0;
}
```

[Example](https://www.godbolt.org/z/asKsxKc1W)

### Task 6.4 : Logical Operators

In programming, it is useful to be able to check a multitude of Boolean expression. This allows programs to have more complex conditional logic structures.

- `!`  - Logical Not
- `&&` - Logical And
- `||` = Logical Or

Logical And and Or have special short circuiting properties. This means that the outcome of a Boolean expressions can be evaluated early. For And, if one Boolean point is `false`, it doesn't matter what the second point evaluates to as the expression's condition has already failed, thus whole expression would `false`. Inversely for Or, if one Boolean point is `true` the whole expression is true

> Note: There is no logical Xor. This is because Xor cannot short circuited as the result depends on the result of both points. However, we have already seen the logical Xor, it is the `!=`. If the two points of `!=` are either both `true` or both `false`, the inequality condition is not met and thus achieving the exclusivity properties of Xor. In C++ because `bool` can be implicitly converted to other integral types, it is best that logicalXor is used as: `!(a) != !(b)`.

```cxx
#include <iomanip>
#include <iostream>

auto main () -> int
{
    auto a {1};
    auto b {2};
    auto c {3};

    std::cout << std::boolalpha;

    /// if `a` is less than `b` and if `a` is less than `c`
    std::cout << "((a < b) && (a < c)) => " << ((a < b) && (a < c)) << std::endl;       ///< true

    /// if `c` is greater than `b` or if `a` is greater than `c`
    std::cout << "((c > b) || (a > c)) => " << ((c > b) || (a > c)) << std::endl;       ///< true

    /// if `a` is not greater than `b` or if `a` is equal to `c`
    std::cout << "(!(a > b) || (a == c)) => " << (!(a > b) || (a == c)) << std::endl;   ///< true
    /// if `a` is not greater than `b` is not equal to if `a` is not greater than `c`
    /// if `a` is not greater than `b` xor if `a` is not greater than `c`
    std::cout << "(!(a > b) != !(a < c)) => " << (!(a > b) != !(a > c)) << std::endl;   ///< false

    std::cout << std::noboolalpha;

    return 0;
}
```

[Example](https://www.godbolt.org/z/xqx3o4hW6)

## Links

- [Previous Page : IO](/content/chapter2/tasks/io.md)
- [Next Page : Conditional Expressions](/content/chapter2/tasks/condexpr.md)
- [Content](/content/README.md)
- [HOME](/README.md)