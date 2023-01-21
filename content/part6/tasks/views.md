# Views

## Contents

- [Views](#views)
  - [Contents](#contents)
  - [Task 5](#task-5)
    - [Task 5.1 : What is a View?](#task-51--what-is-a-view)
    - [Task 5.2 : Lazy Evaluation](#task-52--lazy-evaluation)
    - [Task 5.3 : Factories](#task-53--factories)
    - [Task 5.4 : Range Adaptors, Composition \& The Pipe Operators](#task-54--range-adaptors-composition--the-pipe-operators)
    - [Task 5.5 : Standard View Range Adaptors](#task-55--standard-view-range-adaptors)
    - [Task 5.6 : Assignment 3](#task-56--assignment-3)
      - [Requirements](#requirements)
      - [Optional](#optional)
  - [Links](#links)

## Task 5

### Task 5.1 : What is a View?

A view is a simple abstraction on a range. Views can be thought of as a reference or pointer to a range that is cheap to copy, move, assign and destroy. Views allow for a ranges to be used in a lazy evaluation contexts. Views are found in the `std::ranges` namespace from the `<range>` header, often with a '_view' suffix or can be found in the `std::views` namespace of the same header without the suffix. Views can be passed to range based algorithms or even used as the range evaluated in a range-for.

Ranges can be created from an iterator and sentinel pair or a range using `std::subrange`.

```cxx
#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 5 };

    /// Note: This is unnecessary and is only a showcase 
    for (const auto& e : std::ranges::subrange(v.begin(), v.end()))
        std::cout << e << " ";

    std::cout << std::endl;
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/sE5Eq5a3z)

### Task 5.2 : Lazy Evaluation

What is lazy evaluation? Lazy evaluation is the process of delaying evaluation of functions and expressions until the result of the evaluation is actually needed. This reduces the amount of memory, compute cycles and evaluations the function undergoes and allows for easier composition of functions.

### Task 5.3 : Factories

Some views are used convert ranges and scalars into views. These views are called factories as they generate a view from its arguments.

- `std::views::empty` - A view containing no element. It still takes an unused template type parameter.
- `std::views::single` - A owning view containing a single element.
- `std::views::iota` - A range factory, generating a elements from a repeatedly incremented initial value. This view can be bound to a final value or unbounded, generating an infinite view. Bounded iota views are exclusive ie. the bound is excluded from the resulting range.
- `std::views::istream` - A range factory, generating elements by repeated calls to `>>` on a input stream eg. `std::cin`.

```cxx
#include <algorithm>
#include <iostream>
#include <ranges>

auto main() -> int
{
    /// Prints "0 1 2 3 4 5 6 7 8 9 10"
    std::ranges::copy(std::views::iota(0, 11), std::ostream_iterator<int>(std::cout, " "));
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/brff8rY5T)

- [`std::views::empty` : cppreference](https://en.cppreference.com/w/cpp/ranges/empty_view)
- [`std::views::single` : cppreference](https://en.cppreference.com/w/cpp/ranges/single_view)
- [`std::views::iota` : cppreference](https://en.cppreference.com/w/cpp/ranges/iota_view)
- [`std::views::istream` : cppreference](https://en.cppreference.com/w/cpp/ranges/basic_istream_view)

### Task 5.4 : Range Adaptors, Composition & The Pipe Operators

So far views aren't all that interesting. The true power of views comes from their ability to be composed. Composition allows for views to be combined to build more complex views over data while still adhering to lazy evaluation. Instead of evaluating each function one at a time a single function, which is the composition of all the view functions gets evaluated once for every access to the element. Views are composed using the pipe operator (`|`) and are read from left-to-right as opposed to inside-out. This makes function composition far more expressible and extensible. Range (including containers) or view object are 'piped' to the range adaptor with the resulting view; when evaluated, applying the range adaptor on the every element.

### Task 5.5 : Standard View Range Adaptors

- `std::views::transform` - a range adapter whose resulting view maps an unary function to the input range.
- `std::views::filter` - a range adaptor that whose resulting view excludes any element that do not satisfy an unary predicate.
- `std::views::reverse`  - a range adaptor returning a view of the input range as if its order was reversed.
- `std::views::take` - a range adaptor whose resulting view take only $n$ elements from the input range. Performs bound checks to ensure that it doesn't take more elements then the view can see.
- `std::views::take_while` - a range adaptor whose resulting view contains every element until an unary predicate returns `false`.
- `std::views::drop` - a range adapter whose resulting view skips the first $n$ elements from a input range.
- `std::views::drop_while` -  a range adaptor whose resulting view starts at the first element for which the unary predicate evaluates `false`.
- `std::views::join` - a range adaptor whose resulting view will flatten nested range or view object a single view.
- `std::views::split` - a range adaptor whose resulting view contains subranges split by a given deliminator. Is not entirely lazy and will eagerly move forward through the view at each iteration during evaluation.
- `std::views::lazy_split` - a range adaptor whose resulting view contains subranges split by a given deliminator Is entirely lazy evaluated but is unable to model the subranges as a [common range](https://en.cppreference.com/w/cpp/ranges/common_range)(a range with the same type for the iterator and sentinel) and cannot be used in algorithms expecting a bidirectional range (or higher).
- `std::views::common` - a range adaptor whose resulting view adapts the input range to have the same type for its iterator and sentinels.
- `std::views::element` - a range adaptor that accepts an input range with _Tuple-Like_ elements and whose resulting view contains the $Nth$ entry from every _Tuple-Like_ element of the input range.
- `std::views::keys` - a range adaptor who is a specialisations of `std::views::elements` taking the $0th$ entry of a view of _Tuple-Like_ elements. This can be used to obtain a view of just the keys of an associative container.
- `std::views::values` - a range adaptor who is a specialisations of `std::views::elements` taking the $1st$ entry of a view of _Tuple-Like_ elements. This can be used to obtain a view of just the values of an associative container.

```cxx
#include <algorithm>
#include <iostream>
#include <ranges>

auto square = [](const auto& x){ return x * x; };
auto even = [](const auto& x){ return x % 2 == 0; };

auto main() -> int
{
    auto nums = std::views::iota(0) 
              | std::views::transform(square)
              | std::views::filter(even)
              | std::views::take(10);

    std::ranges::copy(nums, std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/3fdW1P7hj)

- [`std::views::transform` : cppreference](https://en.cppreference.com/w/cpp/ranges/transform_view)
- [`std::views::filter` : cppreference](https://en.cppreference.com/w/cpp/ranges/filter_view)
- [`std::views::reverse` : cppreference](https://en.cppreference.com/w/cpp/ranges/reverse_view)
- [`std::views::take` : cppreference](https://en.cppreference.com/w/cpp/ranges/take_view)
- [`std::views::take_while` : cppreference](https://en.cppreference.com/w/cpp/ranges/take_while_view)
- [`std::views::drop` : cppreference](https://en.cppreference.com/w/cpp/ranges/drop_view)
- [`std::views::drop_while` : cppreference](https://en.cppreference.com/w/cpp/ranges/drop_while_view)
- [`std::views::join` : cppreference](https://en.cppreference.com/w/cpp/ranges/join_view)
- [`std::views::split` : cppreference](https://en.cppreference.com/w/cpp/ranges/split_view)
- [`std::views::lazy_split` : cppreference](https://en.cppreference.com/w/cpp/ranges/lazy_split_view)
- [`std::views::common` : cppreference](https://en.cppreference.com/w/cpp/ranges/common_view)
- [`std::views::elements` : cppreference](https://en.cppreference.com/w/cpp/ranges/elements_view)
- [`std::views::keys` : cppreference](https://en.cppreference.com/w/cpp/ranges/keys_view)
- [`std::views::values` : cppreference](https://en.cppreference.com/w/cpp/ranges/values_view)

### Task 5.6 : Assignment 3

This assignment is a tricker one. Your job is to implement a [circular buffer](https://en.wikipedia.org/wiki/Circular_buffer) or a ring buffer. Circular buffers are First-In-First-Out buffers

#### Requirements

- Must be a `class` (or `struct`).
- Must have these constructors
  - Default
  - Copy
  - Move
  - Assignment Copy
  - Assignment Move
  - A destructor
- Must be templated for any element type `T`.
- Must have a begin and end iterator (_hint: can just be pointers_) with the relevant methods for obtaining them.
- Can either be dynamic in size (adds memory as it needs) or semi-static (fixed maximum but variable current size)
- Methods for pushing in a new element to the front and popping the oldest from the back.
- Introspection methods
  - Current size
  - Current capacity
  - One that returns a pointer to the first element
- Element access
  - _at-like_ method with index checking
  - subscript operator overload (`[]`)

You can manually create and destroy the memory, use smart pointers or use a container to store the underlying memory.

#### Optional

- front and and back element access.
- Equality (`==`) and inequality (`!=`) operator overloads.
- Output stream operator overload (`>>`).
- Constructor and assignment operator overload (`=`) that take an `std::initializer_list`.
- Uses an allocator (eg. `std::allocator`) to allocate memory.
- Takes an additional template argument that correlates to a generic allocator type.
- Takes an additional template parameter that correlates to the type of the underlying container used to for storage of elements (eg. `std::vector`) making the circular buffer an adaptor.

## Links

- [Previous Page : Ranges](/content/part6/tasks/ranges.md)
- [Back to Part 6](/content/part6/README.md)
- [Content](/content/README.md)
- [HOME](/README.md)
