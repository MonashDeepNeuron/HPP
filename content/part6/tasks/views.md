# Views

## Contents

- [Views](#views)
  - [Contents](#contents)
  - [Task 5](#task-5)
    - [Task 5.1 : What is a View?](#task-51--what-is-a-view)
    - [Task 5.2 : Lazy Evaluation](#task-52--lazy-evaluation)
    - [Task 5.3 : Factories](#task-53--factories)
    - [Task 5.4 : Range Adaptors, Composition \& The Pipe Operators](#task-54--range-adaptors-composition--the-pipe-operators)
      - [Task 5.4.1 : Transform](#task-541--transform)
      - [Task 5.4.2 : Filter](#task-542--filter)
      - [Task 5.4.3 : Reverse](#task-543--reverse)
      - [Task 5.4.4 : Take \& Take While](#task-544--take--take-while)
      - [Task 5.4.5 : Drop \& Drop While](#task-545--drop--drop-while)
      - [Task 5.4.6 : Join](#task-546--join)
      - [Task 5.4.7 : Split](#task-547--split)
      - [Task 5.4.8 : Common](#task-548--common)
      - [Task 5.4.9 : Associative Container Views](#task-549--associative-container-views)
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

#### Task 5.4.1 : Transform

The `std::views::transform` range adapter takes an unary function as its argument, applying it to every element in the view.

```cxx

```

[Example]()

[`std::views::transform` : cppreference](https://en.cppreference.com/w/cpp/ranges/transform_view)

#### Task 5.4.2 : Filter

`std::views::filter` will exclude elements based on a unary predicate, keeping the elements for which the predicate evaluates as `true`.

```cxx

```

[Example]()

[`std::views::filter` : cppreference](https://en.cppreference.com/w/cpp/ranges/filter_view)

#### Task 5.4.3 : Reverse

`std::views::reverse` returns are view of the range as if its order was reversed.

```cxx

```

[Example]()

[`std::views::reverse` : cppreference](https://en.cppreference.com/w/cpp/ranges/reverse_view)

#### Task 5.4.4 : Take & Take While

`std::views::take` will take $n$ elements from the piped range or view object. `std::views::take` performs bound checks to ensure that it doesn't take elements past the end of the view. `std::views::take_while` is similar to `std::views::Take` in that it will take elements as long as an unary predicate evaluates to `true`.

```cxx

```

[Example]()

[`std::views::take` : cppreference](https://en.cppreference.com/w/cpp/ranges/take_view)
[`std::views::take_while` : cppreference](https://en.cppreference.com/w/cpp/ranges/take_while_view)

#### Task 5.4.5 : Drop & Drop While

`std::views::drop` drops $n$ elements from a piped view. `std::views::drop_while` drops elements as long as an unary predicate evaluates to `true`.

```cxx

```

[Example]()

[`std::views::drop` : cppreference](https://en.cppreference.com/w/cpp/ranges/drop_view)
[`std::views::drop_while` : cppreference](https://en.cppreference.com/w/cpp/ranges/drop_while_view)

#### Task 5.4.6 : Join

`std::views::join` will flatten a range or view object that have nested range or view objects into a single view.

```cxx

```

[Example]()

[`std::views::join` : cppreference](https://en.cppreference.com/w/cpp/ranges/join_view)

#### Task 5.4.7 : Split

`std::views::split` will a range or view object based on a specified deliminator into a view object of subranges. `std::views::split` is not entirely lazy and will eagerly move forward through the view at each iteration during evaluation. For full lazy evaluation use `std::views::lazy_split` which is entirely lazy. However, `std::views::lazy_split` is unable to model the subranges as a [common range](https://en.cppreference.com/w/cpp/ranges/common_range)(a range with the same type for the iterator and sentinel) and cannot be used in algorithms expecting a bidirectional range (or higher).

```cxx

```

[Example]()

[`std::views::split` : cppreference](https://en.cppreference.com/w/cpp/ranges/split_view)
[`std::views::lazy_split` : cppreference](https://en.cppreference.com/w/cpp/ranges/lazy_split_view)

#### Task 5.4.8 : Common

`std::views::common` adapts a view of range object with different iterator and sentinel types to a view that has the same type for the iterator and sentinel.

```cxx

```

[Example]()

[`std::views::common` : cppreference](https://en.cppreference.com/w/cpp/ranges/common_view)

#### Task 5.4.9 : Associative Container Views

Most range adaptors operate on ranges as if they are sequences. This can make working with views of _Tuple-Like_ elements or associative containers cumbersome. C++ offers some range adaptors for working with the views and range objects of _Tuple-Like_ elements (eg. _key-value_ pairs from associative containers) to make this easier and more expressible. The range adaptor `std::views::element` accepts a view of _Tuple-Like_ elements and creates a view object that contains the $Nth$ entry from every _Tuple-Like_ element of the input range or view object. `std::views::keys` and `std::views::values` are specialisations of `std::views::elements` taking the $0th$ and $1st$ entry of a view of _Tuple-Like_ elements respectively. This can be used to obtain a view of just the keys or values of an associative container respectively.

```cxx

```

[Example]()

[`std::views::elements` : cppreference](https://en.cppreference.com/w/cpp/ranges/elements_view)
[`std::views::keys` : cppreference](https://en.cppreference.com/w/cpp/ranges/keys_view)
[`std::views::values` : cppreference](https://en.cppreference.com/w/cpp/ranges/values_view)

## Links

- [Previous Page : Ranges](/content/part6/tasks/ranges.md)
- [Back to Part 6](/content/part6/README.md)
- [Content](/content/README.md)
- [HOME](/README.md)
