# Introduction to the Standard Library

## What is the Standard Library

The Standard Library is the full set of features in C++ that are available outside the pure language. These include mathematical functions, IO facilities, containers, algorithms and much more. These are tools that abstract a lot of the useful mechanics of C++ into safe, efficient and fast facilities that are easier to use, more consistent and far superior in functionality. The C++ Standard Library is included using headers. These are the files we have been importing using the `#include` preprocessor directive.

This week you will learn about the most useful and bare-bones features in the Standard Library that will make working with C++ much easier, more idiomatic and faster.

## Initializer Lists

Throughout the last few weeks we have been using _brace-init-lists_ to initialise objects. This is super useful for _slice-like_ types to be initialised without using for loops. In C++ these brace-init-lists are converted to `std::initializer_list<T>` (where `T` is the element type). This is a useful construct for building user-defined containers that are initialised using a brace-init-list. There is not much use for you in `std::initializer_list` now but it is useful to know about later. One important thing to know about `std::initializer_list` is that is is a construction only type. That is it is only used to create object, you cannot return a `std::initializer_list` from a function.

[`std::initializer_list`](https://en.cppreference.com/w/cpp/utility/initializer_list)

## Arrays

Slices are useful for packing contiguous data into a single object but because of the implicit nature of decaying into pointers they can be error prone. This is where C++'s array type come in.

`std::array` comes in. This is a complete array type that store both its data and size. Like slices, `std::array` must know its type and size at compile time and the type must be the same throughout the array. Because `std::array` is a complete object you can use reference semantics on it in an intuitive way. It is highly recommended to use `std::array` instead of slices everywhere you can.

```cxx
#include <iostream>
#include <array>

void print(std::array<int, 6> arr)
{
    std::cout << "[ ";
    for (auto i {0}; i < arr.size(); ++i)
        std::cout << arr[i] << ", ";
    std::cout << "]" << std::endl;
}

auto main () -> int
{
    auto a = std::array<int, 6>{ 1, 2, 3, 4, 5, 6 };
    auto b = std::to_array<int>({ -1, -2, -3, -4, -5, -6});  ///< Size can be deduced

    print(a);
    print(b);

    return 0;
}
```

[Example](https://www.godbolt.org/z/dbcKqx53f)

[`std::array`](https://en.cppreference.com/w/cpp/container/array)

## Member Access

Because we are know looking at some custom types from C++'s standard library it is important to point out how to access member functions and variables of both objects and pointers. For an object `T t();` with a member variable you access it using the `.` operator like `t.foo`. If `t::foo` is a member function you postfix parentheses to call the function like `t.foo()`. If the object is a pointer say `T* tp = &t` then the `->` operator is used instead of `.`.

## Spans

Another useful _slice-like_ structure is a `std::span`. Remember the `print()` function (in slices section of this chapter) that took a slice and a size. This is common place in many old C and C++ libraries that used pointer for all buffers. `std::span` removes the need for pointers altogether. `std::span` is a non-owning view of any object that has some contiguous data and a size. This allows libraries to accept a multitude of different intpu types that resemble the shape and work seamlessly with them all.

```cxx
#include <array>
#include <iostream>
#include <span>

void print(std::span<int> span)
{
    std::cout << "[ ";
    for (auto& e : span)
        std::cout << e << ", ";
    std::cout << "]" << std::endl;
}

auto main () -> int
{
    auto array = std::to_array<int>({ 1, 2, 3, 4, 5, 6 });
    int slice[] = {4, 46, 57};

    print(array);
    print(slice);

    return 0;
}
```

[Example](https://www.godbolt.org/z/4Yo93e7Tr)

[`std::span`](https://en.cppreference.com/w/cpp/container/span)

## Strings

Now that we have a much more powerful array type at out disposal it might be tempting to use it as a character array for strings and while this is viable we often want to form a very different set of operations on strings compared to arrays. For this we have `std::string`. `std::string` is a specialised type that has a much larger interface of string operations.

```cxx
#include <iostream>
#include <string>

auto main () -> int
{
    auto str1 {"Hello"};
    auto str2("Goodbye");
    
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;

    return 0;
}
```

> Note: There are also string type for all of C++'s character types eg. `wchar_t`.

[Example](https://www.godbolt.org/z/hqT44PM7M)

[`std::string`](https://en.cppreference.com/w/cpp/string/basic_string)

### String Views

There are also span like views for strings. This is called `std::string_view`. Like span it doesn't own its string but can be used to access its value. This is designed to be a replacement for character slices.

```cxx
#include <iostream>
#include <string_view>

void print(std::string_view s)
{ std::cout << s << std::endl; }

auto main () -> int
{
    print("Hello");

    return 0;
}
```

[Example](https://www.godbolt.org/z/cbb95YWWj)

[`std::string_view`](https://en.cppreference.com/w/cpp/string/basic_string_view)

### Literal Operators

In C++ the is a cool operator called the literal operator `""`. This is used to construct literals from string literals. The are string literal operators for `std::string` and `std::string_view` which are `""s` and `""sv` respectively.

```cxx
#include <iostream>
#include <string>
#include <string_view>

using namespace std::literals;

void print(std::string_view s)
{ std::cout << s << std::endl; }

auto main () -> int
{
    print("Hello"sv);

    std::cout << typeid("Hello").name() << std::endl;
    std::cout << typeid("Hello"s).name() << std::endl;
    std::cout << typeid("Hello"sv).name() << std::endl;

    return 0;
}
```

[Example](https://www.godbolt.org/z/jcMfrG76c)

## Smart Pointers

The final facility we will look at is C++'s smart pointers. Smart pointers allow for automatic lifetime management of heap allocated memory resources. It is highly recommended to only use smart pointers for for any kind of head resource.

All smart pointers are in the `<memory>` header.

### Unique Pointer

`std::unique_ptr` is a pointer to a uniquely owned resource. It cannot be copied, only moved. When a `std::unique_ptr` goes out of scope it automatically deletes the allocated resource. Because `std::unique_ptr` is a complete object you can pass a reference of a `std::unique_ptr` and modify the underlying value like a pointer. It also offers a safer `std::unique_ptr::get()` method that returns `nullptr` if the `std::unique_ptr` points to nothing.

```cxx
#include <iostream>
#include <memory>

void print(std::unique_ptr<int>& ptr)
{ 
    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;
}

void add_magic(std::unique_ptr<int>& ptr)
{ *ptr += 42; }

auto main () -> int
{
    std::unique_ptr<int> p1(new int(6));
    auto p2 = std::make_unique<int>(7);
    auto p3 = std::unique_ptr<int>{nullptr};

    print(p1);
    print(p2);

    add_magic(p1);
    // add_magic(p3);  ///< Would fail 

    print(p1);
    // print(p3);  ////< Would fails

    return 0;
}
```

[Example](https://www.godbolt.org/z/G1T1j84nE)

[`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr)

### Shared Pointer

Sometimes it useful to have multiple pointers refer to the same dynamic memory resource. However, one issue of this is there is know way to know if the memory resource is still needed but another pointer meaning a memory resource can be released accidently leaving all other pointers to the now deleted resource a dangling pointer. This is where `std::shared_ptr` comes in handy. This pointer will maintain a count or how many pointers refer to it. Only when this count reaches zero, indicating no more pointers are using the resource will the resource get deleted. This gives the behavior of many garbage collected languages without the massive overhead of a global gabage collecting program.

```cxx
#include <iostream>
#include <memory>

void print(std::shared_ptr<int> ptr)
{ 
    std::cout << "ptr = " << ptr << std::endl;
    std::cout << "*ptr = " << *ptr << std::endl;
    std::cout << "ptr.use_count() = " << ptr.use_count() << std::endl;
}

void add_magic(std::shared_ptr<int>& ptr)
{ *ptr += 42; }

auto main () -> int
{
    auto p = std::make_shared<int>(7);

    std::cout << "p.use_count() = " << p.use_count() << std::endl;

    print(p);
    add_magic(p);

    return 0;
}
```

[Example](https://www.godbolt.org/z/39dPYooTW)

[`std::shared_ptr`](https://en.cppreference.com/w/cpp/memory/shared_ptr)

### Weak Pointer

Sometimes it is useful to observe an existing resource that is managed by `std::shared_ptr` and only assume temporary ownership if the object still exists. This is where `std::weak_ptr` is used. It is constructed from an existing `std::shared_ptr` and observes the memory resource and is able to be converted to a `std::shared_ptr` when it needs to access the resource. This is useful for breaking reference cycles of `std::shared_ptr`'s and extend the lifetime of a memory resource to the scope of a `std::weak_ptr`. It is also able to check if the resource has been deleted already.

```cxx
#include <iostream>
#include <memory>

void print(std::weak_ptr<int> ptr)
{ 
    std::cout << "ptr.use_count() = " << ptr.use_count() << std::endl;

    if (auto sp = ptr.lock())
    {
        std::cout << "sp.use_count() = " << sp.use_count() << std::endl;
        std::cout << "sp = " << sp << std::endl;
        std::cout << "*sp = " << *sp << std::endl;
    }
    else
        std::cout << "ptr is expired" << std::endl;
}

auto main () -> int
{
    auto p = std::make_shared<int>(7);

    std::cout << "p.use_count() = " << p.use_count() << std::endl;

    print(p);

    return 0;
}
```

[Example](https://www.godbolt.org/z/PaonscnEG)

[`std::weak_ptr`](https://en.cppreference.com/w/cpp/memory/weak_ptr)
