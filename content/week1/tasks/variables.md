# Variables

## Contents

- [Variables](#variables)
  - [Contents](#contents)
  - [Task 3](#task-3)
    - [3.1 : Variables](#31--variables)
    - [3.2 : Initialisation](#32--initialisation)
      - [3.2.1 : Default Initialisation](#321--default-initialisation)
      - [3.2.2 : Value Initialisation](#322--value-initialisation)
      - [3.2.3 : Copy Initialisation](#323--copy-initialisation)
      - [3.2.4 : Direct Initialisation](#324--direct-initialisation)
      - [3.2.5 : Aggregate Initialisation](#325--aggregate-initialisation)
      - [3.2.6 : List Initialisation](#326--list-initialisation)
    - [3.3 : Qualifiers](#33--qualifiers)
      - [3.3.1 : Size](#331--size)
      - [3.3.2 : Mutability](#332--mutability)
      - [3.3.3 : Storage](#333--storage)
    - [3.4 : Automatic Types](#34--automatic-types)
    - [3.5 : Value Categories](#35--value-categories)
      - [3.5.1 : Literals](#351--literals)
      - [3.5.2 : lvalues](#352--lvalues)
      - [3.5.3 : rvalues](#353--rvalues)
  - [Links](#links)

## Task 3

### 3.1 : Variables

Variables are the first form of abstraction in any mathematical and logical system and computers are no exception. In C++ a variable is an owner of some value. You can use variables to store the value of something and use it in different places throughout your software. Variables can only be of one type, this is the type of the value they hold.

To declare a variable in C++ is super simple and follows the following pattern `<type> <name> <initialiser>;`. That's it, pretty simple. However, like many things in C++ there is a slight catch. How does a variable acquire a value. In C++ there is a concept known as Resource Acquisition Is Initialisation (RAII). This essentially means that when a type obtains a resource; or rather, obtains all its necessary resources it can be considered initialised.

So what does this all mean? This means that C++ has strict rules about how values can be given to variables and that certain requirements need to be made by the constructor of a type and the variable receiving the newly constructed value of that type. However, this is mostly technical speak but seeing a bit of it now can give you a better foundation to understand some weird quirks C++ has that you will most likely encounter in the future. We will cover constructors at a later date and focus on how to initialise a variable.

### 3.2 : Initialisation

To begin open a new file or compiler explorer window so we can start writing. Make sure to have the main function so the program can run. Look in [/resources/blueprint.cxx](/resources/blueprint.cxx) for a copy of main.

#### 3.2.1 : Default Initialisation

Before we saw that creating a variable has the pattern `<type> <name> <initialiser>`. `<type>` can be any type we've seen so far or the `auto` keyword. `<name>` can be any alphanumeric (plus _) combination of characters (as long as the first character is not a number). For example an `int` called `i` would be.

```cpp
int i /* <initialiser> */;
```

But what is an initialiser? This is something that creates a value for a variable. In fact we can remove the comment as `i` has already been initialised at this point. What you are seeing above is what is called default initialisation. This is when a type is in its default or empty state which is typically an undetermined state. For `int` and in fact for all builtin types, the default initialiser will leave the corresponding variable; `i` in this case` in what's called an indeterminate state, as in its value cannot be guaranteed. In accessing default initialised variable is undefined behavior (UB) so there is no telling what can happen if you do but most like and hopefully, it will fail to compile or the program will crash when it gets to the line accessing the default initialised variable.

```cxx
/// Primitive Data Types
bool b;
int i;
char c;
wchar_t wc;
float f;
double d;
void foo();
std::nullptr_t;
nullptr;
std:: size_t sz;
std::ptrdiff_t pd;
auto a = {1};  ///< must have initialiser for type deduction.
```

[Default Initialisation](https://en.cppreference.com/w/cpp/language/default_initialization)

#### 3.2.2 : Value Initialisation

Value initialisation is used to zero-initialise a scalar variable (eg. `int` etc.) or default initialise a user defined type such as a `class`. The syntax for value initialisation varies but it typically uses `<type> <name> {}` or `<type> ()`. This is the preferred and recommended way to to initialise variables without giving them an explicit value.

```cxx
int a{};                ///< zero-initialises `a` to `0`.
int();                  ///< zero-initialises a temporary to `0`.
T t{};                  ///< Default initialises `t` using `T` default constructor
```

[Value Initialisation](https://en.cppreference.com/w/cpp/language/value_initialization)
[Zero Initialisation](https://en.cppreference.com/w/cpp/language/zero_initialization)

#### 3.2.3 : Copy Initialisation

Copy initialisation is the most common type of initialisation found in C++ as it is the method originally derived from C. Copy initialisation revolves around the assignment operator `=` but is not exclusive to it. By default, most operations in C++ use copies and thus are initialised using copy initialisation. Copy initialisation copies any expression on the right-hand-side of the `=`, provided the type is correct.

```cxx
int a = 1;              ///< Copies the value of the literal `1`.
int b = {2};            ///< List initialisation through copy. Narrowing conversions are prohibited.
int c = foo();          ///< Copies through `return` of `foo`.
T t2(t1);               ///< Copies `t1` to `t2` using `T` copy constructor.
```

Up until now, we haven't been able to give our variables custom values. With copy initialisation we can copy literals and values from other variables giving use access to any and all data. While `T t = v` is allowed for any correct value `v` of type `T`, it is preferred to use `T t = {v}` as this prevents implicit conversions.

[Copy Initialisation](https://en.cppreference.com/w/cpp/language/copy_initialization)

#### 3.2.4 : Direct Initialisation

Direct initialisation allows you to initialise a variable with an explicit set of constructor arguments. This is mostly useful for custom constructor beyond the trivial ones the compiler can provide.

```cxx
int a{1};       ///< Single element, brace-enclosed initialiser. Must be of the same type.
T t(2, 3);      ///< Direct initialisation of `t` with literals `2` and `3`.
U u(v);         ///< Direct initialisation of `u` with `v` which may be of a different type `V`.
W(x);           ///< Direct initialisation of temporary of type `W` with existing `x` of possible different type `X`.
Y(4, 6, 5);        ///< Direct initialisation of temporary of type `Y` with literals `4`, `5` and `6`.
```

[Direct Initialisation](https://en.cppreference.com/w/cpp/language/direct_initialization)

#### 3.2.5 : Aggregate Initialisation

Aggregate initialisation is special list initialisation for aggregate types. These are slice, `struct`, `class` or `union` types with (for the formers) no private data-members or user-defined constructors. This allows them to be initialised with a list.

```cxx
T t = {1, 2, 3};                ///< Copy list initialisation of aggregate `t` of type `T`.
U u{ 4, 5, 6};                  ///< List initialisation of aggregate `u` of type `U`.
V v = { .v1 = 7, .v2{8} };      ///< Copy list initialisation of aggregate `v` of type `V` with designated initialisers for `v`'s members.
W w{ .w1 = 9, .w2{10} };        ///< List initialisation of aggregate `w` of type `W` with designated initialisers for `w`'s members.
```

We want use this directly all to much as list initialisation generally applies in more cases.

[Aggregate Initialisation](https://en.cppreference.com/w/cpp/language/aggregate_initialization)

#### 3.2.6 : List Initialisation

List initialisation is a generalisation of aggregate initialisation but can be applied to user-defined types. This allows you to specify a list of values to be used as arguments for a constructor.

```cxx
T t {1, 2, 3, 4};           ///< Direct-list initialisation.
U u = {5, 6, 7, 8};         ///< Copy-list initialisation.
t = {4, 3, 2, 1};           ///< Copy-list assignment.
foo({1, 2, 3});             ///< Argument copy-list initialisation.
W w({4, 5, 6});             ///< Direct constructor list initialisation.
```

Have a play with with these and see what works with the compiler. It might be easier to play with on [godbolt](https://www.godbolt.org/z/Y34xxoahz)

[List Initialisation](https://en.cppreference.com/w/cpp/language/list_initialization)

### 3.3 : Qualifiers

#### 3.3.1 : Size

- `short`
- `signed`
- `unsigned`
- `long`

#### 3.3.2 : Mutability

- `const`
- `constexpr`
- `volatile`
- `mutable`

#### 3.3.3 : Storage

- `static`

### 3.4 : Automatic Types

### 3.5 : Value Categories

#### 3.5.1 : Literals

#### 3.5.2 : lvalues

#### 3.5.3 : rvalues

## Links

- [Previous Page : Primitive Types](/content/week1/tasks/types.md)
- [Next Page : Qualifiers](/content/week1/tasks/qualifiers.md)
- [Content](/content/README.md)
- [HOME](/README.md)
