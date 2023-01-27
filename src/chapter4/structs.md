# Structures

## Contents

- [Structures](#structures)
  - [Contents](#contents)
  - [Task 5](#task-5)
    - [Task 4.1 : Structures](#task-41--structures)
  - [Assignment 1 : Your Turn](#assignment-1--your-turn)
    - [Requirements](#requirements)
    - [Bonus](#bonus)
    - [Submitting](#submitting)
  - [Links](#links)

## Task 5

### Task 4.1 : Structures

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

## Assignment 1 : Your Turn

Having learnt a massive chunk of C++ now I want you to try and right some code for yourself. Your task is to create a triple struct, ie. like a 3D point but semantically more general. You must demonstrate and run all of the properties of the struct. The program should be called `triple.cxx` (or `triple.main.cxx` if using bpt)

### Requirements

- Must have three members of the same type (either `int`, `float` or `double`)
- A way to add two points
- A way to subtract two points
- A way to multiply a point by a scalar (of the same underlying type)
- A way to divide a point by a scalar (of the same underlying type)
- A way to be print a formatted output using `std::cout`

### Bonus

- A way to be created using input from `std::cin`
- Create a 'triple' structure for the other underlying types.

### Submitting

You can use Godbolt or bpt to build and test your struct. Once you have created your implementation:

- clone this repo using `git clone https://github.com/MonashDeepNeuron/HPP.git`.
- create a new branch using `git checkout -b triple/<your-name>`.
- create a folder in the `/content/chapter4` directory called `submissions/<your-name>`.
- Copy your mini project into this directory (bpt setup, cmake scripts etc.) with a `README.md` or comment in the code on how to run the program (verify it still works). There is a sample header file in `/templates` that you can use.
- Go to <https://github.com/MonashDeepNeuron/HPP/pulls> and click 'New pull request'.
- Change the branches in the drop down so that your branch is going into `main` and `Create new pull request.
- Give the pull request a title and briefly describe what you were able to implement and any struggles you had.
- On the right side-panel, under the 'Assignees' section, click the cog and assign me.
- Click 'Create pull request' and I'll take it from there.

> Note: If you created a GodBolt instance, put the link in a comment at the top of the file (under your copy comments). This is generated by clicking the `share` button in the top-right-most corner of the webpage and clicking the 'short link' option.

This, ideally should be submitted before our meetup on 11/01/2023. Please note that I will be asking each of you a few questions about how you went and your thought processes in throughout the implementation.

## Links

- [Previous Page : Unions](/content/chapter4/tasks/enums.md)
- [Back to Chapter 4](/content/chapter4/README.md)
- [Content](/content/README.md)
- [HOME](/README.md)