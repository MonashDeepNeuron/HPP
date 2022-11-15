# Ordering and Equality

## Contents

- [Ordering and Equality](#ordering-and-equality)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : Equality](#task-11--equality)
    - [Task 1.2 : Ordering](#task-12--ordering)
    - [Task 1.3 : Spaceships and Ordering Types](#task-13--spaceships-and-ordering-types)
  - [Links](#links)

## Task 1

### Task 1.1 : Equality

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

[Godbolt](https://www.godbolt.org/z/EK14h6fhd)

### Task 1.2 : Ordering

Checking for equality is pretty straight forward. Some more interesting operations are the ordering operators.

### Task 1.3 : Spaceships and Ordering Types

## Links

- [Previous Page : Week 2](/content/weekn/README.md)
- [Next Page : ](/content/weekn/tasks/.md)
- [Content](/content/README.md)
- [HOME](/README.md)
