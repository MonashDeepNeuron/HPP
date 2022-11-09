# Primitive Data Types

## Contents

- [Primitive Data Types](#primitive-data-types)
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

#### 2.2.3 : Number Types

### 2.3 : Float Point Types

### 2.4 : Void

### 2.5 : Nullptr

### 2.6 : Auto


## Links

- [Previous Page : The C++ Type System](/content/week1/tasks/typesystem.md)
- [Next Page : Variables](/content/week1/tasks/variables.md)
- [Content](/content/README.md)
- [HOME](/README.md)
