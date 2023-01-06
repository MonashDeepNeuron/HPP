# Classes

## Contents

- [Classes](#classes)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : What Is a Class?](#task-11--what-is-a-class)
    - [Task 1.2 : Defining a Class](#task-12--defining-a-class)
      - [Task 1.2.1 : Member Access](#task-121--member-access)
        - [Task 1.2.1.1 : General Access](#task-1211--general-access)
        - [Task 1.2.1.2 : Access in Derived Classes](#task-1212--access-in-derived-classes)
    - [Task 1.3 : Constructors and Destructors](#task-13--constructors-and-destructors)
      - [Task 1.3.1 : Explicit Constructors](#task-131--explicit-constructors)
        - [Task 1.3.1.1 : Member Initialisers Lists](#task-1311--member-initialisers-lists)
      - [Task 1.3.2 : Default Constructor](#task-132--default-constructor)
      - [Task 1.3.3 : Copy Constructors](#task-133--copy-constructors)
      - [Task 1.3.4 : Move Constructors](#task-134--move-constructors)
      - [Task 1.3.5 : Destructors](#task-135--destructors)
      - [Task 1.3.6 : RAII](#task-136--raii)
      - [Task 1.3.7 : Letting the compiler do the work for you](#task-137--letting-the-compiler-do-the-work-for-you)
    - [Task 1.4 : Members \& Methods](#task-14--members--methods)
      - [Task 1.4.1 : This](#task-141--this)
      - [Task 1.4.2 : Operator Overloading](#task-142--operator-overloading)
      - [Task 1.4.3.1 : Assignment Overloads](#task-1431--assignment-overloads)
      - [Task 1.4.3 : Friend Methods](#task-143--friend-methods)
    - [Task 1.6 : Dynamic Inheritance](#task-16--dynamic-inheritance)
      - [Task 1.6.1 : Virtual Methods](#task-161--virtual-methods)
      - [Task 1.6.2 : Virtual Inheritance](#task-162--virtual-inheritance)
      - [Task 1.6.3 : Abstract Classes](#task-163--abstract-classes)
  - [Links](#links)

## Task 1

### Task 1.1 : What Is a Class?

What is a class? Classes are the same as types. They allow for defining a set of valid operations on a particular configuration or amalgamation of data. In C++ there are two category of types, primitives and classes. Primitives are the basic types your were first introduced to in Part 2. Many other programming languages do not primitives because the language undergoes many more transformations before becoming machine code. As an example, `int` in Python is an object. It meets all the basic requirements of an object same as any other object in Python. This is not the case in C++. `int` in C++ is directly lowered (translated) into a assembly or machine type. You can a can access the bits that represent the `int`, even mutate them. They have a fixed width in memory (although varying from platform-to-platform) and cannot have their interfaces changes or adapted. Classes are different, they are much like object from Python (although, due to C++'s zero overhead principle, you only pay for what you ask for). Class are custom types that anyone can define and even modify through hierarchy structures and inheritance.

### Task 1.2 : Defining a Class

A class is defined identically to a structure. In fact, to C++ they are identical. You can use either keyword to create a class type. Typically however, `struct` is reserved for simple structures while classes are use for more complex types. There is one distinction between the two type declarators, classes will make all of its members (methods and variables) private while structures are public by default. From now on I'll refer to structures and classes as classes or types.

```cxx
#include <iostream>

class Point
{
    int x;
    int y;
};

auto main() -> int
{
    auto p = Point{ 2, 5 };

    std::cout << "( " << p.x << ", " << p.y << " )" << std::endl;  ///< Fails as `x` and `y` are private

    return 0;
}
```

[Example 69](https://www.godbolt.org/z/MrorPKKxW)

#### Task 1.2.1 : Member Access

Classes allow for you to specify the access rights of its members. There are three member access categories. Each allows for a different level of access permissions from both direct users of the class and the children (derived) of the class.

> Note: The term 'Member' means any method (function) or variable owned by a class, structure or type.

##### Task 1.2.1.1 : General Access

When defining a class, you can specify parts of its definition to be either `private`, `protected` or `public`. This is done by putting an accessor label (with the keyword being one of the previously mentioned accessor categories with a `:` suffix) in a region of the classes body. All declared members following the label will adopt the accessor policy. You can reuse access specifiers as much as you want.

Here are the rules for the different accessor policies.

| Accessor Category |                                                      Meaning                                                      |
|:-----------------:|:-----------------------------------------------------------------------------------------------------------------:|
|     `private`     |          Member can only be used by member functions of the same class or friends (functions or classes).         |
|    `protected`    | Member can only be used by member functions of the same class, friends (functions or classes) or derived classes. |
|      `public`     |                                             Can be accessed by anyone.                                            |

```cxx
#include <iostream>

class Point
{
public:             ///< Declare members `x` and `y` as public
    int x;
    int y;
};

auto main() -> int
{
    Point p{ 2, 5 };  ///< Now succeeds

    std::cout << "( " << p.x << ", " << p.y << " )" << std::endl;  ///< Now succeeds

    return 0;
}
```

[Example 70](https://www.godbolt.org/z/1hWjrhee7)

##### Task 1.2.1.2 : Access in Derived Classes

When deriving from another classes (more on inheritance [here](#task-15--dynamic-inheritance)), you can specify the access rights of the parent classes members through the base class.

| Base Classes Access policy |                    `private`                   |                           `protected`                          | `public`                                                       |
|:--------------------------:|:----------------------------------------------:|:--------------------------------------------------------------:|----------------------------------------------------------------|
|                            | Always inaccessible with any derivation access |   `private` in derived class if you use `private` derivation   | `private` in derived class if you use `private` derivation     |
|                            |                                                | `protected` in derived class if you use `protected` derivation | `protected` in derived class if you use `protected` derivation |
|                            |                                                |   `protected` in derived class if you use `public` derivation  | `public` in derived class if you use `public` derivation       |

```cxx
#include <iostream>

class Point
{
public:
    int x;
    int y;
};

class Point3D
    : protected Point       ///< Points members are `protected`
{
public:
    int z;
};

auto main() -> int
{
    Point p{ 2, 5 };
    Point3D p3d{};

    std::cout << "( " << p.x << ", " << p.y << " )" << std::endl;
    std::cout << "p3d.z = " << p3d.z << std::endl;
    std::cout << "( " << p3d.x << ", " << p3d.y << ", " << p3d.z << " )" << std::endl;  ///< Fails, `x` and `y` are inaccessible

    return 0;
}
```

[Example 71](https://www.godbolt.org/z/Wr8av57cz)

> Note: Classes can access their own members regardless of the access policy even if it is a different instance.

### Task 1.3 : Constructors and Destructors

So far we haven't seen much difference from classes than just using them as aggregate structures. One of the unique benefits of classes in C++ is the ability to explicitly define and control how structures are created and destroyed. This gives you powerful control over the lifetime of a type and how its resources are managed at the definition stage removing the need for manual management at runtime. This is done through constructors and destructors. These are special members (functions) with the same name as the class. A class can have any number of constructors (following the normal function overloading rules) but can only have one destructor.

> Note: Creation or construction of a type refers to the explicit instantiation of an object with a particular class type.

#### Task 1.3.1 : Explicit Constructors

The most useful kind of constructors for defining custom creation of a class are explicit constructors. These constructors take explicitly specified arguments, usually used to initialise member variables with a particular value. Explicit constructors are often marked with the `explicit` keyword in their function signature. Means the constructor must be explicitly called, ie. passed the correct types.

Throughout this part we are going to build up the `Point` class. Lets start by making it possible to define the point from two `int`. I've defined the explicit constructor for initialising the members `Point::x` and `Point::y` as well as temporary getters/setters.

```cxx
#include <iostream>

class Point
{
public:

    /// Explicit Constructor for initialising `x` and `y`
    explicit constexpr
    Point(int x, int y) noexcept
    : x{ x }, y{ y }
    { }

    constexpr auto
    X() noexcept -> int&
    { return x; }

    constexpr auto
    Y() noexcept -> int&
    { return y; }

private:
    int x;
    int y;

};  /// class Point

auto main() -> int
{
    Point p{ 2, 5 };

    std::cout << "( " << p.X() << ", " << p.Y() << " )" << std::endl;


    return 0;
}
```

[Example 72](https://www.godbolt.org/z/748dx3vG1)

> Note: Even though it is taught often in; OOP centric or even OOP enabled languages, to define 'getters' and 'setters' for member variables. This is bad practice as it often leads to users of types and classes manually mutating the data themselves instead of defining access patterns and stateful transitions through methods or algorithms. If you must use 'getter' or 'setter' access patterns then you member variables should be publicly accessible.

##### Task 1.3.1.1 : Member Initialisers Lists

You may notice the comma separated 'list' under the constructors declaration. This is called an member initialiser list. It is used to initialise the members of a class from the arguments of the called constructor or from other members of the class. Member initialiser lists are specified between a constructors declaration and its body. Members are initialised in the following order regardless of the order specified by the member initialiser list.

1. If the constructor is for the most-derived class, virtual bases are initialized in the order in which they appear in depth-first left-to-right traversal of the base class declarations (left-to-right refers to the appearance in base-specifier lists)
2. Then, direct bases are initialized in left-to-right order as they appear in this class's base-specifier list
3. Then, non-static data member are initialized in order of declaration in the class definition.
4. Finally, the body of the constructor is executed

[Constructors and member initializer lists](https://en.cppreference.com/w/cpp/language/constructor)

#### Task 1.3.2 : Default Constructor

Sometimes, you don't know the state a type should by in when it is being initialised. In these cases it is useful to have a fallback state. To achieve this we use a default constructor. This will usually take no parameters.

```cxx
#include <iostream>

class Point
{
public:

    /// Default Constructor
    constexpr
    Point() noexcept
        : x{ 0 }, y{ 0 }
    { }

    /// Explicit Constructor for initialising `x` and `y`
    explicit constexpr
    Point(int x, int y) noexcept
        : x{ x }, y{ y }
    { }

    constexpr auto
    X() noexcept -> int&
    { return x; }

    constexpr auto
    Y() noexcept -> int&
    { return y; }

private:
    int x;
    int y;

};  /// class Point

auto main() -> int
{
    Point p1{ 2, 5 };
    Point p2{};

    std::cout << "( " << p1.X() << ", " << p1.Y() << " )" << std::endl;
    std::cout << "( " << p2.X() << ", " << p2.Y() << " )" << std::endl;


    return 0;
}
```

[Example 73](https://www.godbolt.org/z/Wrne3b1nd)

#### Task 1.3.3 : Copy Constructors

Constructors allow for defining custom semantics for common meta-like operations. For example, if you define a constructor that takes a constant reference to another `Point`, the only thing to can do is copy the data from the other class. This constructor pattern is called Copy Semantics. We can also overload the `=` operator so we can perform copy assignments.
Let's define a copy constructor for `Point`.

```cxx
#include <iostream>

class Point
{
public:

    /// Default Constructor
    constexpr
    Point() noexcept
        : x{ 0 }, y{ 0 }
    { }

    /// Explicit Constructor for initialising `x` and `y`
    explicit constexpr
    Point(int x, int y) noexcept
        : x{ x }, y{ y }
    { }

    /// Copy Constructor
    constexpr Point(const Point& p) noexcept
        : x{ p.x }, y{ p.y }
    { }

    constexpr auto
    X() noexcept -> int&
    { return x; }

    constexpr auto
    Y() noexcept -> int&
    { return y; }

private:
    int x;
    int y;

};  /// class Point

auto main() -> int
{
    Point p1{ 2, 5 };
    Point p2{ p1 };   ///< Copy Constructor Called

    std::cout << "( " << p1.X() << ", " << p1.Y() << " )" << std::endl;
    std::cout << "( " << p2.X() << ", " << p2.Y() << " )" << std::endl;
    
    p2.X() = 8;
    p2.Y() = 9;

    std::cout << "( " << p1.X() << ", " << p1.Y() << " )" << std::endl;
    std::cout << "( " << p2.X() << ", " << p2.Y() << " )" << std::endl;

    return 0;
}
```

[Example 74](https://www.godbolt.org/z/YYhf9baW3)

#### Task 1.3.4 : Move Constructors

While our `Point` class has gotten pretty sophisticated there is one file base constructor we need in order to complete its baseline functionality. In C++, all data has an owner. We can get pointers and references to data so that other can borrow the data. We can even copy data so that a new owner can have the same values as another however, there is one missing piece. The transfer of ownership, what if we want to give ownership of some data to a new owner. We see this principle with rvalue references. When we initialise an `int` with a literal; say `1`, we are transferring ownership of the data associated with the literal `1` to the named variable. In C++ this is called a move. Moves occur when a constructor (or assignment) of a type is called on a rvalue reference which invokes the class's move constructor. Moves will rip the data of a type out of it and transfer the ownership of the data and resource to the new object, leaving the old owner in a default initialised state (usually). Moves can be induced using the `std::move()` function from the `<utility>` header.

> Note: Moves of literal types will often invoke a copy over a move because they are primitive types and this cheap to copy. Moves are mostly relevant to more complex types.

```cxx
#include <iostream>
#include <utility>

class Point
{
public:

    /// Default Constructor
    constexpr
    Point() noexcept
        : x{ 0 }, y{ 0 }
    { }

    /// Explicit Constructor for initialising `x` and `y`
    explicit constexpr
    Point(int x, int y) noexcept
        : x{ x }, y{ y }
    { }

    /// Copy Constructor
    constexpr Point(const Point& p) noexcept
        : x{ p.x }, y{ p.y }
    { }

    /// Move Constructor
    constexpr Point(Point&& p) noexcept
        : x{ std::move(p.x) }, y{ std::move(p.y) }
    { 
        p.x = int();
        p.y = int();
    }

    constexpr auto
    X() noexcept -> int&
    { return x; }

    constexpr auto
    Y() noexcept -> int&
    { return y; }

private:
    int x;
    int y;

};  /// class Point

auto main() -> int
{
    Point p1{ 2, 5 };

    std::cout << "( " << p1.X() << ", " << p1.Y() << " )" << std::endl;
    
    Point p2{ std::move(p1) };   ///< Move Constructor Called

    std::cout << "( " << p1.X() << ", " << p1.Y() << " )" << std::endl;
    std::cout << "( " << p2.X() << ", " << p2.Y() << " )" << std::endl;

    return 0;
}
```

[Example 75](https://www.godbolt.org/z/TfGEWW7qM)

- [`std::move()` : cppreference](https://en.cppreference.com/w/cpp/utility/move)
- [`<utility>` : cppreference](https://en.cppreference.com/w/cpp/header/utility)

#### Task 1.3.5 : Destructors

So far we have built a pretty sophisticated type of our own with many ways to construct it however, what happens when it gets destroyed. This will invoke the classes destructor. The destructor is declared the same as the default constructor however, it is prefixed with a tilde ('~') in the constructors name. Destructors are used to properly free resources from the type. Resources include things such as dynamic memory, device handles, web sockets etc. For our `Point` class our destructor is really a no-op as all of its members are trivial to destruct and will automatically occur. A trivial constructor will look like this.

```cxx
/// ... Rest of `Point` class's constructors

constexpr ~Point() noexcept {}

/// ... Members variables
```

#### Task 1.3.6 : RAII

So why have all these means of specifying creation and deletion of objects? One of the core faults of many programs in C is the requirement to explicitly create and destroy resources, even of structures. One of the first things introduced to C++ where constructors and destructors so that the creation of object of a type and its subsequent destruction were tied to the type itself anf could be implicitly handled by the compiler. It also allowed for classes to acquire all resources they needed at the time of construction. This principle is known as 'Resource Acquisition Is Initialisation' or RAII. This means that the lifetime of any resource owned by a class is tied to the lifetime of an instance of that class.

How this works is that a constructor acquires all the required resources at construction meaning that after construction the object must be initialised. Similarly, the destructor releases resources in reverse-acquisition-order to prevent resource leaks.
This also means that if a constructor should fail (by throwing an exception), any already acquired resources are released in reverse acquisition order and destructors must never throw.

Classes with member functions named `open()`/`close()`, `lock()`/`unlock()`, or `init()`/`copyFrom()`/`destroy()`
(or similar, carrying the same semantics meaning) are typical examples of non-RAII classes.

#### Task 1.3.7 : Letting the compiler do the work for you

Because our `Point` class is superficial and almost trivial, it can be annoying to define all the constructors and when the resources being initialised are trivial. It would be nice to not have to specify every constructor. What if we could make the compiler generate the constructors for us? Well, we can. By just declaring the constructors signature with no member initialiser list or body, we can use the `= default` suffix specifier indicating for the compiler to generate the constructor for us. We will do this for the default constructor.

```cxx
/// ... Point details 

constexpr Point() noexcept = default;

/// ... Point details
```

> Note: It should be noted that you should only do this if the operation of performed by a particular constructor is trivial and predictable and doesn't require specific set of operations to occur.

You can also disallow the use of a particular constructor entirely by deleting it.

```cxx
/// ... Point details

constexpr Point(const Point& p) noexcept = delete;  ///< Point objects cannot be copied.

/// ... Point details
```

### Task 1.4 : Members & Methods

While constructors and destructors ensure resource and lifetime safety for classes they are only half the story. Member functions or methods allow us to define operations that we want to on or using the data help by a class. They allow for stateful modification of data while ensuring type safety. To define a methods for a class you simply define a function within the classes body. Normal rules for naming and overloading apply however methods are able to access all members (function and variable) of the immediate class and any `protected` and `public` members of parent classes. In our `Point` class we already have to members; `Point::X()` and `Point::Y()` which return `int&` of the members `Point::x` and `Point::y` respectively.

```cxx
/// ... Point details

constexpr auto
X() noexcept -> int&
{ return x; }

constexpr auto
Y() noexcept -> int&
{ return y; }

/// ... Point details
```

#### Task 1.4.1 : This

It is useful for a class to be self aware and have some means of referring to itself, for example when working with another instance of the same class in a method it can be ambiguous when you are using members from your instance and from the other objects instance. Classes in C++ implicitly have a member called `this`. `this` is a pointer to the current instance of a class in memory. Using `this` allows for qualified lookup of names for the current object. Like any other pointer it can be dereferenced so that it can be used as a reference or have its members accessed using `this->`. `this` can only be used in methods and has the type of the class type the method was called with including cv-qualifications.

```cxx
/// ... Point details

constexpr auto
X() noexcept -> int&
{ return this->x; }

constexpr auto
Y() noexcept -> int&
{ return this->y; }

/// ... Point details
```

[The `this` pointer](https://en.cppreference.com/w/cpp/language/this)

#### Task 1.4.2 : Operator Overloading

Much like how you can overload operators as free functions, classes can define there own overloads for operators. operator overloads for classes are defined just like regular methods for classes however, the first argument is implicitly `this` object.

```cxx
/// ... Point details

constexpr auto
operator+ (const Point& p) noexcept -> Point
{ return Point{ x + p.x, y + p.y }; }

constexpr auto
operator- (const Point& p) noexcept -> Point
{ return Point{ x - p.x, y - p.y }; }

constexpr auto
operator== (const Point& p)
    noexcept -> bool
{ return (x == p.x) && (y == p.y); }

constexpr auto
operator!= (const Point& p)
noexcept -> bool
{ return !(*this == p); }

/// ... Point details
```

[Example 75](https://www.godbolt.org/z/TG9WW74bo)

#### Task 1.4.3.1 : Assignment Overloads

One of the most useful operator overloads we can define for a class is an overload for `=`; two in fact, one for each of copy semantics and move semantics. This methods work identical to their constructor counterparts except they must have an explicit return type and value, cannot have a member initializer list and must only be defined for a single argument.

```cxx
/// ... Point details

constexpr auto
operator= (const Point& p) noexcept -> Point&
{
    if (p != *this)
    {
        x = p.x;
        y = p.y;
    }

    return *this;
}

constexpr auto
operator= (Point&& p) noexcept -> Point&
{
    if (p != *this)
    {
        x = std::move(p.x);
        y = std::move(p.y);
    }

    return *this;
}

/// ... Point details
```

> Note: The `if (p != *this)` check ensures self assignment does not occur.

[Example 76](https://www.godbolt.org/z/xvcf57xcT)

#### Task 1.4.3 : Friend Methods

Sometimes it is useful to access the internal `private` and `protected` data of a class without having to make it exposed to everyone. This is were friends come in handy. The `friend` keyword can be attached to nested class forward specifications and functions. This makes free functions able to access and modify the internal data of a class. Friendship is most useful for creating relationships between hierarchal unrelated classes interoperate with each other such as in certain operator overloads.

- > Note: Friendship is not transitive - A friend of your friend is not your friend
- > Note: Friendship is not inherited - Your friends children are not your friends

Here I've defined an overload for `<<` as a `friend` function. This is because `std::ostream` is an unrelated type to `Point` but we want to be able to access the non-public members of a `Point` object. With this, we can delete the `Point::X()` and `Point::Y()` methods.

```cxx
/// ... Point details

friend auto
operator<< (std::ostream& os, const Point& p)
    noexcept -> std::ostream&
{ 
    os << "( " << p.x << ", " << p.y << " )";
    return os;
}

/// ... Point details
```

[Example 77](https://www.godbolt.org/z/MxacvscTY)

[Version 1 of `Point`](/content/part5/examples/point-v1.hxx)

### Task 1.6 : Dynamic Inheritance

You are able to inherit the members of another class into your own class. This allows for many OOP concepts to be applied such as inheritance and polymorphism. Base classes are specified after the derived classes name specification. All classes can be inherited from (unless declared as `final`).

> Note: OOP principles are not the focus of this series and is only covered lightly. C++ is by no means a Object Oriented language (despite similar naming). Rather C++ supports OOP principles in order to benefit from these principles however, many parts of the language (Standard Library) will utilise these features and principles in a far more general sense.

```cxx
#include <iostream>

struct A
{
    int n;
};

struct B : public A
{
    float f;
};

auto main() -> int
{
    A a();
    std::cout << a.n << std::endl;
    a.n = 7;
    std::cout << a.n << std::endl;

    B b();
    std::cout << b.n << std::endl;
    std::cout << b.f << std::endl;
    b.n = 4;
    std::cout << b.n << std::endl;
    std::cout << a.n << std::endl;

    b.f = 8.53464f;
    std::cout << b.f << std::endl;

    return 0;
}
```

[Example 78](https://www.godbolt.org/z/xvMdeq3n5)

#### Task 1.6.1 : Virtual Methods

A method can be marked as virtual with the `virtual` specifier. This means that classes that derive this method can override them by specifying them as overridden with the `override` keyword in the derived class.

```cxx
#include <iostream>

struct A
{
    virtual void foo();
};

void A::foo() { std::cout << "A::foo()" << std::endl; }

struct B : public A
{
    void foo() override;
};

void B::foo() { std::cout << "B::foo()" << std::endl; }

auto main() -> int
{
    A a;
    a.foo();

    B b;
    b.foo();

    return 0;
}
```

- > Note: `virtual` and `override` methods cannot have deduced return types
- > Note: The definition of virtual functions must be defined separate from the declaration.

[Example 79](https://www.godbolt.org/z/zrMs4EhKn)

- [`virtual` function specifier : cppreference](https://en.cppreference.com/w/cpp/language/virtual)
- [`override` specifier : cppreference](https://en.cppreference.com/w/cpp/language/override)

#### Task 1.6.2 : Virtual Inheritance

Classes can also inherit base classes virtually. For each base class that is specified as virtual, the most derived object will contain only one sub-object of that `virtual` base class, even if the class appears many times in the inheritance hierarchy (as long as it is inherited `virtual` every time)*.

```cxx
#include <iostream>

struct B 
{ int n; };

class X : public virtual B {};
class Y : virtual public B {};
class Z : public B {};
 
// every object of type AA has one X, one Y, one Z, and two B's:
// one that is the base of Z and one that is shared by X and Y
struct AA : X, Y, Z
{
    AA()
    {
        X::n = 1; // modifies the virtual B sub-object's member
        Y::n = 2; // modifies the same virtual B sub-object's member
        Z::n = 3; // modifies the non-virtual B sub-object's member
 
        std::cout << X::n << Y::n << Z::n << '\n';
    }
};

auto main() -> int
{
    AA aa;

    return 0;
}
```

[Example 80](https://www.godbolt.org/z/qT5v7aEPx)

[Derived Classes : cppreference](https://en.cppreference.com/w/cpp/language/derived_class)

> *Note: This is an adaptation (paraphrase) from [cppreference](https://en.cppreference.com/w/cpp/language/derived_class#:~:text=initializer%20list.-,Virtual%20base%20classes,-For%20each%20distinct)

#### Task 1.6.3 : Abstract Classes

Abstract classes are classes which define or inherit at least one 'pure' `virtual` methods. Pure `virtual` methods are `virtual` methods whose declaration are suffixed by the `= 0;` pure-specifier expression. Abstract classes cannot be instantiated but can be pointer to or referred to.

```cxx
#include <iostream>

struct Base
{
    virtual void g() = 0;
    virtual ~Base() {}
};

void Base::g() { std::cout << "Base::g()" << std::endl; }
 
struct A : Base
{
    virtual void g() override;
};

void A::g() 
{ 
    Base::g();
    std::cout << "A::g()" << std::endl; 
}

auto main() -> int
{
    // Base b;  ///< Fails `cannot declare variable 'b' to be of abstract type 'Base'`

    A a;
    a.g();

    return 0;
}
```

[Example 81](https://www.godbolt.org/z/axj9Tbr4v)

[Abstract class : cppreference](https://en.cppreference.com/w/cpp/language/abstract_class)

## Links

- [Previous Page : Part 5](/content/part5/README.md)
- [Next Page : Templates](/content/part5/tasks/templates.md)
- [Content](/content/README.md)
- [HOME](/README.md)
