# Operators

## Contents

- [Operators](#operators)
  - [Contents](#contents)
  - [Task 4](#task-4)
    - [4.1 : Basic Arithmetic](#41--basic-arithmetic)
    - [4.2 : Bitwise Operations](#42--bitwise-operations)
      - [4.2.1 : A bit about shift operations](#421--a-bit-about-shift-operations)
    - [4.3 : Arithmetic Assignment](#43--arithmetic-assignment)
  - [Links](#links)

## Task 4

### 4.1 : Basic Arithmetic

So enough about types and values. Lets write some code that does something. In C++ there are a lot, and I mean a lot of operators but we will only cover the arithmetic based one this week. The first ones we will look at are the basic arithmetic operators. These include your standard:

- `+` - Addition
- `-` - Subtraction
- `*` - Multiplication
- `/` - Division
- `%` - Modulo

For the meanwhile we will only look at operations on integers and floating point types. For these types the operators do what you would expect. Try out the following operations.

```cxx
#include <iostream>

auto main () -> int
{
    auto a{10};
    auto b{3};

    std::cout << "a + b = " << a + b << std::endl;  ///< a + b = 13
    std::cout << "a - b = " << a - b << std::endl;  ///< a - b = 7
    std::cout << "a * b = " << a * b << std::endl;  ///< a * b = 30
    std::cout << "a / b = " << a / b << std::endl;  ///< a / b = 3??
    std::cout << "a % b = " << a % b << std::endl;  ///< a % b = 1

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/xKMooTb4s)

> Note: for those unaware, `%` returns the remained of the division of $\frac{a}{b}$

But hold up, why does `a / b` return `3`, should it not be `3.33...`? This correct.. sorta. In C++ when two integers divide it performs integer division, thus throwing away any remainder after the maximum even divisions. This is the same as Pythons `//` operator. To perform floating point division, either the numerator or denominator needs to be of a floating point type. This is so the alternate one (if it is an integer type) can be promoted to a floating point type to perform the floating point division.

```cxx
#include <iostream>

auto main () -> int
{
    auto a{10};
    auto b{3};
    auto c{3.};
    auto d{10.};

    std::cout << "a / c = " << a / c << std::endl;  ///< a / c = 3.33333
    std::cout << "d / b = " << d / b << std::endl;  ///< d / b = 3.33333

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/eeYqPbcaT)

> Note: The modulo operator does not work for floating point types as this illogical (can't return remainder of a floating point division as it is near impossible to regain the information).

You can also use `+` and `-` to change/force the sign of a integer or floating point type.

```cxx
#include <iostream>

auto main () -> int
{
    auto e{-5.43};
    auto f{0.71};

    std::cout << "e + f = " << e + f << std::endl;          ///< e + f = -4.72
    std::cout << "-e + f = " << -e + f << std::endl;        ///< -e + f = 6.14
    std::cout << "e - -f = " << e - f << std::endl;         ///< e - f = -6.14
    std::cout << "e - -f = " << e - -f << std::endl;        ///< e - -f = -4.72

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/o9afoszjP)

There are also in-place operators `++` and `--`. These allow you to increment/decrement integer types in place. There are two variations, prefix and postfix. Prefix will increment/decrement the value and then provide a lvalue of the new variables value to whatever is reading it (if any). Postfix will provide an lvalue to copy of the old value and then increment/decrement the value.

```cxx
#include <iostream>

auto main () -> int
{
    auto g{1};
    auto h{5};

    std::cout << "g++ = " << g++ << std::endl;      ///< g++ = 1
    std::cout << "g = " << g << std::endl;          ///< g = 2
    std::cout << "++g = " << ++g << std::endl;      ///< ++g = 3
    std::cout << "g = " << g << std::endl;          ///< g = 3

    std::cout << "h-- = " << h-- << std::endl;      ///< h-- = 5
    std::cout << "h = " << h << std::endl;          ///< h = 4
    std::cout << "--h = " << --h << std::endl;      ///< --h = 3
    std::cout << "h = " << h << std::endl;          ///< h = 3

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/5Ps5ezhaT)

### 4.2 : Bitwise Operations

In C++ there is another category of operators called bitwise operators. These operators only apply to integer types but allow for you to individually control the bits of an integer.

- `&` - Bitwise And
- `|` - Bitwise Or
- `^` - Bitwise Xor
- `<<` - Bitwise Left Shift (Left Rotate)
- `>>` - Bitwise Right Shift (Right Rotate)

> Note: We've seen `<<` before with `std::cout`. In the case of `std::cout` `<<` means 'put (to)'. It is simply an overloaded operator used for ease of use. It doesn't correlate to the bitwise meaning.

Each of the bitwise operators perform their respective logical operations on each of the bits the the two values or points and returns the new value.

```cxx
#include <bitset>
#include <iostream>

auto main () -> int
{
    auto i{5};
    auto j{4};

    std::cout << "i & j = " << (i & j) << std::endl;                            ///< i & j = 4
    std::cout << "  " << std::bitset<8>{i} << std::endl;
    std::cout << "& " << std::bitset<8>{j} << std::endl;
    std::cout << "----------" << std:: endl;
    std::cout << "  " << std::bitset<8>{i & j} << std::endl;                    ///< i & j =  00000100

    std::cout << "i | j = " << (i | j) << std::endl;                            ///< i | j = 4
    std::cout << "  " << std::bitset<8>{i} << std::endl;
    std::cout << "| " << std::bitset<8>{j} << std::endl;
    std::cout << "----------" << std:: endl;
    std::cout << "  " << std::bitset<8>{i | j} << std::endl;                    ///< i | j =  00000101

    std::cout << "i ^ j = " << (i ^ j) << std::endl;                            ///< i ^ j = 4
    std::cout << "  " << std::bitset<8>{i} << std::endl;
    std::cout << "^ " << std::bitset<8>{j} << std::endl;
    std::cout << "----------" << std:: endl;
    std::cout << "  " << std::bitset<8>{i ^ j} << std::endl;                    ///< i ^ j =  00000001

    std::cout << "i << j = " << (i << j) << std::endl;                          ///< i << j = 4
    std::cout << "   " << std::bitset<8>{i} << std::endl;
    std::cout << "<< " << std::bitset<8>{j} << std::endl;
    std::cout << "-----------" << std:: endl;
    std::cout << "   " << std::bitset<8>{i << j} << std::endl;                  ///< i << j =  01010000

    std::cout << "i >> j = " << (i >> j) << std::endl;                          ///< i >> j = 4
    std::cout << "   " << std::bitset<8>{i} << std::endl;
    std::cout << ">> " << std::bitset<8>{j} << std::endl;
    std::cout << "-----------" << std:: endl;
    std::cout << "   " << std::bitset<8>{i >> j} << std::endl;                  ///< i >> j =  00000000

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/37b58aTjf)

#### 4.2.1 : A bit about shift operations

For the shift operations, the general pattern is as follows `<shifted> <shift-op> <additive>`. This means the value that is being shifted is always on the left-hand-side and is always shifted by the number indicated on the right-hand-side. For left-shifts, the bit pattern is moved `N` spot to the left, pushing zeros at the end of the right side and popping any bit off the left end. For right shifts, the opposite occurs. The bit pattern is move right by `N` spots, popping any bit off the right end and push the same bit as the sign bit of the number being shifted (1's if negative and 0's if positive).

### 4.3 : Arithmetic Assignment

There is one final set of arithmetic operators in C++. These are the arithmetic assignment operators. These will perform the operation between two points and assign the result to the left point.

- `+=` - Add assign - `a = a + b == a += b`
- `-=` - Subtract assign - `a = a - b == a -= b`
- `*=` - Multiply assign - `a = a * b == a *= b`
- `/=` - Divide assign - `a = a / b == a /= b`
- `%=` - Modulo assign - `a = a % b == a %= b`
- `&=` - And assign - `a = a & b == a &= b`
- `|=` - Or assign - `a = a | b == a |= b`
- `^=` - Xor assign - `a = a ^ b == a ^= b`
- `<<=` - Left-shift assign - `a = a << b == a <<= b`
- `>>=` - Right-shift assign - `a = a >> b == a >>= b`

```cxx
#include <iostream>

auto main () -> int
{
    auto k{5};
    auto l{2};

    k += l;
    std::cout << "k += l -> k = " << k << std::endl;    ///< k = 7

    k *= l;
    std::cout << "k *= l -> k = " << k << std::endl;    ///< k = 14

    l |= k;
    std::cout << "l |= k -> l = " << l << std::endl;    ///< l = 14

    k <<= l;
    std::cout << "k <<= l -> k = " << k << std::endl;   ///< k = 229376

    l ^= k;
    std::cout << "l ^= k -> l = " << l << std::endl;    ///< l = 229390

    k &= l;
    std::cout << "k &= l -> k = " << k << std::endl;    ///< k = 229376

    l -= k;
    std::cout << "l -= k -> l = " << l << std::endl;    ///< l = 14

    return 0;
}
```

[Godbolt](https://www.godbolt.org/z/33hP5o4v7)

Have a play with these operators and try and perform some computations that you might do in another languages.

## Links

- [Previous Page : Variables](/content/week1/tasks/variables.md)
- [Back to Week 0](/content/week1/README.md)
- [Content](/content/README.md)
- [HOME](/README.md)
