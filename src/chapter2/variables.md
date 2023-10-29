# Variables

Variables are the first form of abstraction in any mathematical and logical system and computers are no exception. In C++ a variable is an owner of some value. You can use variables to store the value of something and use it in different places throughout your software. Variables can only be of one type, this is the type of the value they hold.

To declare a variable in C++ is super simple and follows the following pattern `<type> <name> <initialiser>;`. That's it, pretty simple. However, like many things in C++ there is a slight catch. How does a variable acquire a value. In C++ there is a concept known as Resource Acquisition Is Initialisation (RAII). This essentially means that when a type obtains a resource; or rather, obtains all its necessary resources it can be considered initialised.

So what does this all mean? This means that C++ has strict rules about how values can be given to variables and that certain requirements need to be made by the constructor of a type and the variable receiving the newly constructed value of that type. However, this is mostly technical speak but seeing a bit of it now can give you a better foundation to understand some weird quirks C++ has that you will most likely encounter in the future. We will cover constructors at a later date and focus on how to initialise a variable.

## Initialisation

To begin, open a new file or compiler explorer window so we can start writing. Make sure to have the main function so the program can run. Look in [/resources/blueprint.cxx](../../resources/blueprint.cxx) for a copy of main.

### Default Initialisation

Before we saw that creating a variable has the pattern `<type> <name> <initialiser>`. `<type>` can be any type we've seen so far or the `auto` keyword. `<name>` can be any alphanumeric (plus _) combination of characters (as long as the first character is not a number). For example an `int` called `i` would be.

```cpp
int i /* <initialiser> */;
```

But what is an initialiser? This is something that creates a value for a variable. In fact we can remove the comment as `i` has already been initialised at this point. What you are seeing above is what is called default initialisation. This is when a type is in its default or empty state which is typically an undetermined state. For `int` and in fact for all builtin types, the default initialiser will leave the corresponding variable; `i` in this case` in what's called an indeterminate state, as in its value cannot be guaranteed. In accessing default initialised variable is undefined behavior (UB) so there is no telling what can happen if you do but most like and hopefully, it will fail to compile or the program will crash when it gets to the line accessing the default initialised variable.

```cxx
/// Primitive Data Types
bool b = true
int i;
char c;
wchar_t wc;
float f;
double d;
void foo();
std::nullptr_t;
nullptr;
std::size_t sz;
std::ptrdiff_t pd;
auto a = {1};  ///< must have initialiser for type deduction.
```

[Default Initialisation](https://en.cppreference.com/w/cpp/language/default_initialization)

### Value Initialisation

Value initialisation is used to zero-initialise a scalar variable (eg. `int` etc.) or default initialise a user defined type such as a `class`. The syntax for value initialisation varies but it typically uses `<type> <name> {}` or `<type> ()`. This is the preferred and recommended way to to initialise variables without giving them an explicit value.

```cxx
int a{};                ///< zero-initialises `a` to `0`.
int();                  ///< zero-initialises a temporary to `0`.
T t{};                  ///< Default initialises `t` using `T` default constructor
```

- [Value Initialisation](https://en.cppreference.com/w/cpp/language/value_initialization)
- [Zero Initialisation](https://en.cppreference.com/w/cpp/language/zero_initialization)

### Copy Initialisation

Copy initialisation is the most common type of initialisation found in C++ as it is the method originally derived from C. Copy initialisation revolves around the assignment operator `=` but is not exclusive to it. By default, most operations in C++ use copies and thus are initialised using copy initialisation. Copy initialisation copies any expression on the right-hand-side of the `=`, provided the type is correct.

```cxx
int a = 1;              ///< Copies the value of the literal `1`.
int b = {2};            ///< List initialisation through copy. Narrowing conversions are prohibited.
int c = foo();          ///< Copies through `return` of `foo`.
T t2(t1);               ///< Copies `t1` to `t2` using `T` copy constructor.
```

Up until now, we haven't been able to give our variables custom values. With copy initialisation we can copy literals and values from other variables giving use access to any and all data. While `T t = v` is allowed for any correct value `v` of type `T`, it is preferred to use `T t = {v}` as this prevents implicit conversions.

[Copy Initialisation](https://en.cppreference.com/w/cpp/language/copy_initialization)

### Direct Initialisation

Direct initialisation allows you to initialise a variable with an explicit set of constructor arguments. This is mostly useful for custom constructor beyond the trivial ones the compiler can provide.

```cxx
int a{1};       ///< Single element, brace-enclosed initialiser. Must be of the same type.
T t(2, 3);      ///< Direct initialisation of `t` with literals `2` and `3`.
U u(v);         ///< Direct initialisation of `u` with `v` which may be of a different type `V`.
W(x);           ///< Direct initialisation of temporary of type `W` with existing `x` of possible different type `X`.
Y(4, 6, 5);        ///< Direct initialisation of temporary of type `Y` with literals `4`, `5` and `6`.
```

[Direct Initialisation](https://en.cppreference.com/w/cpp/language/direct_initialization)

### Aggregate Initialisation

Aggregate initialisation is special list initialisation for aggregate types. These are slice, `struct`, `class` or `union` types with (for the formers) no private data-members or user-defined constructors. This allows them to be initialised with a list.

```cxx
T t = {1, 2, 3};                ///< Copy list initialisation of aggregate `t` of type `T`.
U u{ 4, 5, 6};                  ///< List initialisation of aggregate `u` of type `U`.
V v = { .v1 = 7, .v2{8} };      ///< Copy list initialisation of aggregate `v` of type `V` with designated initialisers for `v`'s members.
W w{ .w1 = 9, .w2{10} };        ///< List initialisation of aggregate `w` of type `W` with designated initialisers for `w`'s members.
```

We want use this directly all to much as list initialisation generally applies in more cases.

[Aggregate Initialisation](https://en.cppreference.com/w/cpp/language/aggregate_initialization)

### List Initialisation

List initialisation is a generalisation of aggregate initialisation but can be applied to user-defined types. This allows you to specify a list of values to be used as arguments for a constructor.

```cxx
T t {1, 2, 3, 4};           ///< Direct-list initialisation.
U u = {5, 6, 7, 8};         ///< Copy-list initialisation.
t = {4, 3, 2, 1};           ///< Copy-list assignment.
foo({1, 2, 3});             ///< Argument copy-list initialisation.
W w({4, 5, 6});             ///< Direct constructor list initialisation.
```

Have a play with with these and see what works with the compiler. In general, stick to using copy and direct initialisation. It might be easier to play with on [Example _](https://www.godbolt.org/z/Y34xxoahz)

[List Initialisation](https://en.cppreference.com/w/cpp/language/list_initialization)

## Qualifiers

Types can have different qualifiers that change how a type behaves from its size to mutability. Qualifiers go before the type declaration.

### Signed-ness

The `signed` and `unsigned` qualifiers are used to indicate whether the first bit of the integral type is used for the sign of a number or not. All integral types are implicitly `signed` (`char` can vary). `unsigned` increases the maximum number an integral can be but disallows negative values. `unsigned` only works on integer types and not floating point types.

### Size

Size qualifiers are used to indicate the number of bits (which is platform specific) an `int` type must have at least.

- `short int` - 16-bits at least
- `int` - 16-bits at least (typically 32-bits)
- `long int` - 32-bits at least
- `long long int` - 64-bits at least

You can also combined size qualifiers with the `unsigned` (and `signed` though not strictly necessary) to allow much larger numbers. You are also able to drop the `int` type in favour of just the size qualifiers and C++ will infer it to be `int`. `long` can also be used with `double` to create a (on some systems) binary128 floating point number.

| Size Qualifiers / Primitive Type | `short` | `unsigned short` | `signed` | `unsigned` | `long` | `unsigned long` | `long long` | `unsigned long long` |
|:---------------------------:|:-------:|:----------------:|:--------:|:----------:|:------:|:---------------:|:-----------:|:--------------------:|
|            `bool`           |    ❌    |         ❌        |     ❌    |      ❌     |    ❌   |        ❌        |      ❌      |           ❌          |
|            `char`           |    ❌    |         ❌        |     ✅    |      ✅     |    ❌   |        ❌        |      ❌      |           ❌          |
|          `wchar_t`          |    ❌    |         ❌        |     ❌    |      ❌     |    ❌   |        ❌        |      ❌      |           ❌          |
|            `int`            |    ✅    |         ✅        |     ✅    |      ✅     |    ✅   |        ✅        |      ✅      |           ✅          |
|           `float`           |    ❌    |         ❌        |     ❌    |      ❌     |    ❌   |        ❌        |      ❌      |           ❌          |
|           `double`          |    ❌    |         ❌        |     ❌    |      ❌     |    ✅   |        ❌        |      ❌      |           ❌          |

[Fundamental Types](https://en.cppreference.com/w/cpp/language/types)

### Storage

Storage qualifiers allow you to specify the lifetime of variables. All variables implicitly have automatic storage duration. The exist only in a certain scope, are created when the program enters that scope and dropped at the end of that scope. `static` (and implicitly global variables) are created at the beginning of the program and are dropped only at the end of the program. Only one variable of the same name can be declared static in a given translation unit.

```cxx
static int si = {1};  ///< static variables

{
    int li = {2};  ///< local automatically dropped variable
}
```

`inline` is more of a hint to the compiler for functions and methods. It indicates to the compiler that a function call should be inlined at call, ie. the functions definition gets moved to the call site. This qualifier is mostly used in OOP classes hierarchies as its more general use has be dropped in favour of a different qualifier.

### Mutability

In C++, variables are mutable by default. There are various ways to limit the mutability of variables as well as constrain the optimisations a compiler can apply.

- `const` - A `const` object is an immutable object, it cannot be changes. It must be initialised with a values.
- `constexpr` - A `constexpr` is; as the names suggests, a constant expression. It is an expression that _may_ be evaluated at compile time. Similar to `const`.
- `volatile` - Indicates to the compiler that the variable may change in ways that it is unaware of and to avoid optimising this variables use in case of undesired behavior.
- `mutable` - Indicates a member variable may be modified even through const-qualified methods (we'll see this in [Week 5](/content/week5/README.md)).

```cxx
int i = {0};
const int ci = {1};
constexpr int cx = {2};
volatile int vi = {3};
const volatile int cv = {4};

i = 6;      ///< Ok
ci = 7;     ///< Error
cx = 8;     ///< Error
vi = 9;     ///< Ok
cv = 10;    ///< Error
```

> Note: The usage of `volatile` is highly discouraged.

## Automatic Types

The final type we look at is an automatic type. As we will see later, declaring the type of variables can get cumbersome. Since C++11, a new type introducer was create with the keyword `auto`. Variables with type `auto` will have there true type deduced at compile time based on the initialiser.

```cxx
auto ai = int{1};               ///< `ai` deduced to have the type `int`
auto al {2L};                   ///< `al` deduced to have the type `long` or `long int` (uses 'L' literal)
auto ac {'c'};                  ///< `ac` deduced to have the type `char`
auto as = "hello";              ///< `as` deduced to have the type `const char*` (more on these later)
```

## Value Categories

In C++, there are different categories of values. These determine the operations that can be performed on them. There are a few value categories in C++ but we will focus on only two of them, lvalues and rvalues.

### lvalues

In C++ and lvalue is kind of value that you would find on the left-hand-side of the `=`, hence the name lvalue or 'left-value'. You can also find lvalues on the right-hand-side of `=`. This is the semantics of a copy (may or may not be an initialisation). Typically, a variable that has an assigned value is an lvalue.

### rvalues

rvalues are; as the name suggests, variables or values found on the right-hand-side of `=`. This includes literals, temporaries and moves. For example the literal `3` is an rvalue. rvalues are also used to indicate move-semantics (more on this later on).

### Literals

Literals are types that have a explicit value to them. The literal `0` has the value of `int{0}` and type `int`. Literals allow the to be common code-point to define values into a specific character or character sequence. Essentially, literals hold the value and type they indicate.
