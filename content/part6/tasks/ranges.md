# Ranges

## Contents

- [Ranges](#ranges)
  - [Contents](#contents)
  - [Task 4](#task-4)
    - [Task 4.1 : What is a range?](#task-41--what-is-a-range)
    - [Task 4.2 : Range Concepts \& Categories](#task-42--range-concepts--categories)
  - [Links](#links)

## Task 4

### Task 4.1 : What is a range?

What is a range? So far we have considered a range as a pair of iterators pointing to the beginning and end of a collection of elements. C++ formalised this idea by defining a range as an iterator and sentinel pair. This allowed for C++ to introduced the Ranges Library. One problem with the main C++ standard algorithms library is that is was made in the 1990's. As such the algorithms were designed with implicit constraints but had no way to enforce them. Because of backwards compatibility the standard library algorithms could not be updated to use concepts, instead C++ introduces new overloads for the standard library algorithms in the nested `std::ranges` namespace. Along with the original iterator (now iterator and sentinel design) interface, these algorithms accept a range object as an input sequence (output ranges are still modelled using an output iterator). This allowed for algorithm calls to be much simpler while also enforcing constraints on ranges. Almost all of the original algorithms have a `std::ranges` counterpart. If you can use the range version, even with the iterator interfaces as they impose stricter but safer requirements on the iterators to ensure that algorithms behave correctly. Range algorithms also support projections, allowing for in-place temporary transformations of data. This is defaulted to `std::identity`. All containers in the C++ standard library are considered valid ranges.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    println(v);
    std::ranges::transform(v, v.begin(), [](const auto& x){ return x * x; });
    println(v);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/6bdKa63j4)

- [Constrained Algorithms : cppreference](https://en.cppreference.com/w/cpp/algorithm/ranges)
- [`std::ranges::transform` : cppreference](https://en.cppreference.com/w/cpp/algorithm/ranges/transform)

### Task 4.2 : Range Concepts & Categories

Like iterators, there are different categories describing the requirements of a range type. These categories have concept definitions so you can constrain your own algorithms. Here is a table of different sequence containers and how they match up against the different range concepts.

|                                    | `std::forward_list` | `std::list` | `std::deque` | `std::array` | `std::vector` |
|:----------------------------------:|:-------------------:|:-----------:|:------------:|:------------:|:-------------:|
|     `std::ranges::input_range`     |          ✅          |      ✅      |       ✅      |       ✅      |       ✅       |
|    `std::ranges::forward_range`    |          ✅          |      ✅      |       ✅      |       ✅      |       ✅       |
| `std::ranges::bidirectional_range` |                     |      ✅      |       ✅      |       ✅      |       ✅       |
| `std::ranges::random_access_range` |                     |             |       ✅      |       ✅      |       ✅       |
|   `std::ranges::contiguous_range`  |                     |             |              |       ✅      |       ✅       |

> Note: `std::output_range` is not shown here. This is because an `std::output_range` is similar to `std::input_range` except it models writing to as opposed to reading.

## Links

- [Previous Page : Algorithms](/content/part6/tasks/algorithms.md)
- [Next Page : Views](/content/part6/tasks/views.md)
- [Content](/content/README.md)
- [HOME](/README.md)
