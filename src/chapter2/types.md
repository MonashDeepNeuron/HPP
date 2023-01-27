# Primitive Types

## Contents

- [Primitive Types](#primitive-types)
  - [Contents](#contents)
  - [Task 2](#task-2)
    - [2.1 : Size and Width](#21--size-and-width)
    - [2.2 : Integral Types](#22--integral-types)
      - [2.2.1 : Boolean Type](#221--boolean-type)
      - [2.2.2 : Character Types](#222--character-types)
      - [2.2.3 : Number Types](#223--number-types)
    - [2.3 : Float Point Types](#23--float-point-types)
    - [2.4 : Void](#24--void)
    - [2.5 : Nullptr](#25--nullptr)
    - [2.6 : Other Types](#26--other-types)
    - [2.6 : Auto](#26--auto)
  - [Links](#links)

## Task 2

### 2.1 : Size and Width

In C++, all types have an implicit property called width or size. This refers to how much memory; in bits or bytes, a given type maximally occupies. This leaves enough room for any value of the given type to fit in the allocated spot. The minimum size a type can occupy in C++ is 8-bits or a byte.

### 2.2 : Integral Types

#### 2.2.1 : Boolean Type

The first type we will look at is `bool`. `bool` represents a Boolean value, meaning it is either `true` or `false`. This is a specialization of a unique type-function called a sum type. A sum type is a type that can hold one of its possible variants (also called 'appends' or 'injections'), in this case these are the type constructors `true` and `false`. However, in C++ `bool` is built-in to the language and thus these properties are hidden away.

`bool` occupies a memory space of 8-bits or a byte. It is also worth pointing out that `true` and `false` are literals (as they are built-in keywords) holding there respective values independently. Booleans are used to denote truthiness and logic in a programming language. In C++, `bool` can be implicitly promoted to another integral type such as `int` with `false` becoming `0` and `true` becoming `1`. Other integral types also can be narrowed to a `bool` with `0` becoming `false` and anything else becoming `true`.

#### 2.2.2 : Character Types

The next type we will look is the `char`. This is C++ standard character type. These are values such as `'a'` or even escape characters like `'\n'`. It holds only a single byte (same as `bool`) allowing it to represent $2^8 = 256$ different values. Depending on the system is is either `signed` or `unsigned`, meaning either the leading bit is dedicated to the sign of the value or is another number point. Depending on the representation, `char` can have a value between `0..255` (unsigned) or `-127..128` (signed). Character literals exclusively use single quotes in C++.

There is another character type in C++ called `wchar_t`. This is a 'wide character' which can hold more bits than the `char` type. On Windows systems it is 16-bits (2-bytes) while on Unix based systems (Linux, macOS etc.) this is typically 32-bits (4-bytes). This allows for `wchar_t` to be to store many more different codepoints. A wide character literal also uses single quotes however, the quote pair is prefixed with a 'L' eg. 'a' as a `wchar_t` literal looks like `L'a'`.

Like `bool`, `char` and `wchar_t` are integral types, this means that they are really numbers however, the system will treat them differently, eg. for IO.

#### 2.2.3 : Number Types

There is only one primary number type in C++ called `int`. This represents a (typically) 32-bit (4-byte), signed number. It can store $2^{32} = 4,294,967,296$ values has a value range of `-2'147'483'647..2'147'483'648`. `int` is probably the most basic type in terms of bit layout in C++ with every bit storing data from the number with only the first bit indicating the sign of the number.

### 2.3 : Float Point Types

C++ has two distinct floating point number types. These are `float` and `double`. `float` implements the IEEE-754 binary32 floating point format while `double` implements the IEEE-754 binary64 floating point format, hence the name `double` indicating double floating point precision.

Floating point numbers are a unique problem in computing. It is impossible to represent all precisions a decimal number can have (number of decimal places) which still being able to compute large numbers with limited memory. To tackle this, floating point numbers break up the bit-space of the floating point into the sign, fraction and exponents chapters. The IEEE-754 binary32 format uses 1-bit for the sign, 8-bits (a byte) for the exponent and and 23-bits (3-bytes - 1-bit) for the fraction. The IEEE-754 binary64 format has; again 1-bit for the sign, 11-bits for the exponent and 52-bits for the fraction chapter. This gives you (greater than) double the number bits you can use represent your fraction chapter or $536,870,912$ times more possible values for the fraction chapter of a `double` over a `float` ($2^{52}=4.5035996\cdot10^{15}$ vs $2^{23}=8,388,608$).

### 2.4 : Void

In C++ there is a unique type called called `void`. This is an incomplete and it can not be completed. It is a unique type of literal but it holds no value. `void` is used to indicate the absence of a return value (and input parameter value in C). It is different from the unit type (which is not explicitly present in C++) which has the type `()` and value `()`, `void` has the type of `void` but not the value of `void`. It has no value.

### 2.5 : Nullptr

`nullptr` is a literal type which has type of `std::nullptr_t` and value of `nullptr`. This is a unique type used by pointers to indicate that they point to nothing.

### 2.6 : Other Types

There are two more types in C++ that are worth talking about. These are `std::size_t` and `std::ptrdiff_t`. `std::size_t` is a platform dependent type that indicates the maximum possible size of an unsigned integer in C++. This is typically a 32-bit or 64-bit number types.

`std::ptrdiff_t` is a signed number type that is returned by subtracting two pointers in C++.

### 2.6 : Auto

While C++ is a statically typed language, it is able to infer and deduce the types of many things at compile time. This is achieve with a non-type keyword called `auto`. While `auto` is used in many places that type specifiers are used (more on this in the next section), it is important to note that it itself is not a type but rather a automatic type, essentially a placeholder for the to-be deduced type.

## Links

- [Previous Page : The C++ Type System](/content/chapter2/tasks/typesystem.md)
- [Next Page : Variables](/content/chapter2/tasks/variables.md)
- [Content](/content/README.md)
- [HOME](/README.md)
