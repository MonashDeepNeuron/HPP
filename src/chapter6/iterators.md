# Iterators

## Contents

- [Iterators](#iterators)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : What is an iterator?](#task-11--what-is-an-iterator)
    - [Task 1.2 : Iterator Categories](#task-12--iterator-categories)
    - [Task 1.3 : Obtaining Iterators](#task-13--obtaining-iterators)
    - [Task 1.4 : Iterator Functionalities](#task-14--iterator-functionalities)
      - [Task 1.4.1 : Common Operator Interface](#task-141--common-operator-interface)
      - [Task 1.4.2 : Iterator Functions](#task-142--iterator-functions)
    - [Task 1.5 : Sentinels](#task-15--sentinels)
    - [Task 1.6 : Iterator Adaptors](#task-16--iterator-adaptors)
  - [Links](#links)

## Task 1

### Task 1.1 : What is an iterator?

An iterator is an abstraction for representing an item, element, value etc. in a collection or container of values that also has some notion how to get to a obtain or yield a new item from the container. In C++ iterators a lot like pointers in the sense that they hold some value, usually the location of it and has a means of either yielding the value for reading or allows for writing to that value.

### Task 1.2 : Iterator Categories

There are 6 main iterator categories considered in C++. Each subsequent iterator category builds upon the previous categories requirements with increasingly more requirements.

<table>
<thead>
  <tr>
    <th rowspan="2">Iterator Category</th>
    <th colspan="7">Valid Operations</th>
  </tr>
  <tr>
    <th>write</th>
    <th>read</th>
    <th>increment</th>
    <th>multiple passes</th>
    <th>decrement</th>
    <th>random access</th>
    <th>contiguous storage</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>Output</td>
    <td>✅</td>
    <td></td>
    <td>✅</td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Input</td>
    <td>❓(might support writing)</td>
    <td>✅</td>
    <td>✅</td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Forward<br>(Satisfies Input)</td>
    <td></td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Bidirectional<br>(Satisfies Forward)</td>
    <td></td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>Random Access<br>(Satisfies Bidirectional)</td>
    <td></td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td></td>
  </tr>
  <tr>
    <td>Contiguous<br>(Satisfies Random Access)</td>
    <td></td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
    <td>✅</td>
  </tr>
</tbody>
</table>

> Note: A pointer actually satisfies the Contiguous Iterator Category

Before C++20, there were empty structs used as tags to help categorise an iterator into its respective category. Since C++ there have been concepts introduces to perform this check more elegantly along with other iterator-related concepts to all for anything modelling an iterator to satisfy the constraints.

### Task 1.3 : Obtaining Iterators

Almost all collections or containers have iterators to their first and last element. To obtain these iterator from any container kinds we call the `std::begin()` and `std::end` functions from the `<iterator>` header respectively. There are also constant and reverse and constant reverse versions of the functions.

```cxx
#include <array>
#include <iostream>
#include <iterator>

auto main() -> int
{
    auto a = std::to_array<int>({1, 3, 4, 565, 868, 5, 46});
    
    std::cout << std::begin(a) << std::endl;
    std::cout << *std::begin(a) << std::endl;
    std::cout << std::end(a) << std::endl;
    std::cout << *(std::end(a) - 1) << std::endl;

    return 0;
}
```

[Example](https://www.godbolt.org/z/MG7q3d63a)

- [`<iterator>` : cppreference](https://en.cppreference.com/w/cpp/header/iterator)
- [`std::begin()` & `std::cbegin()` : cppreference](https://en.cppreference.com/w/cpp/iterator/begin)
- [`std::end()` & std::cend()` : cppreference](https://en.cppreference.com/w/cpp/iterator/end)
- [`std::rbegin()` & std::crbegin()` : cppreference](https://en.cppreference.com/w/cpp/iterator/rbegin)
- [`std::rend()` & std::crend()` : cppreference](https://en.cppreference.com/w/cpp/iterator/rend)

### Task 1.4 : Iterator Functionalities

There are a few ways to interact with an iterator directly. One is to use the overloaded operators for the iterator object. Most iterators implement and overload the same operator set that is used by pointers. The other way is to use functions to interact with iterators, allowing for a more generic interface if a iterator doesn't support the common operator overload set and the implementer preferred to overload the functions. The only way to yield or write to the item held by an iterator is to use the dereference operator `*`.

#### Task 1.4.1 : Common Operator Interface

|  Operation  |         |          |          |
|:-----------:|:-------:|:--------:|:--------:|
| dereference |   `*i`  | `*i = v` | `v = *i` |
|  increment  |  `i++`  |   `++i`  |          |
|  decrement  |  `i--`  |   `--i`  |          |
|  difference | `i - j` |          |          |
|   advance   | `i + n` |  `i - n` |          |
|    index    |  `i[n]` |          |          |

> Where `i` is an iterator object

```cxx
#include <array>
#include <iostream>
#include <iterator>

auto main() -> int
{
    auto a  = std::to_array<int>({1, 3, 4, 565, 868, 5, 46});
    auto it = std::begin(a);

    std::cout << *it << std::endl;
    std::cout << *(it++) << std::endl;
    std::cout << *(++it) << std::endl;
    std::cout << *(it--) << std::endl;
    std::cout << *(--it) << std::endl;
    std::cout << *(it + 4) << std::endl;
    std::cout << *(std::end(a) - 4) << std::endl;
    std::cout << it[6] << std::endl;

    auto v { *it };
    *it = 757657;
    std::cout << v << std::endl;
    std::cout << *it << std::endl;

    return 0;
}
```

[Example](https://www.godbolt.org/z/jeGjnrWvn)

#### Task 1.4.2 : Iterator Functions

There are four functions involved in manipulating an object of iterator kind. These are used to move an iterator between elements.

- `std::next` - Obtains the next iterator from the passed iterator. Can be passed an integral `n` to obtain the _nth_ next iterator. If `n` is negative, the iterator must satisfy _Bidirectional Iterator_.
- `std::prev`- Obtains the previous iterator from the pass iterator. Can be passed an integral to obtain the _nth_ previous iterator. The iterator must satisfy the requirements of a _Bidirectional Iterator_.
- `std::distance` - Obtains the number of increments required by the first iterator to reach the second iterator.
- `std::advance` - Advances the passed iterator by _n_ increments. If _n_ is negative, the iterator must satisfy _Bidirectional Iterator_.

```cxx
#include <array>
#include <iostream>
#include <iterator>

auto main() -> int
{
    auto a  = std::to_array<int>({1, 3, 4, 565, 868, 5, 46});
    auto it = std::begin(a);

    std::cout << *it << std::endl;
    std::cout << *std::next(it) << std::endl;
    std::cout << *std::prev(it) << std::endl;
    std::cout << *std::next(it, 4) << std::endl;

    auto end = std::end(a);

    std::cout << *std::next(end, -4) << std::endl;

    std::cout << std::distance(it, end - 3) << std::endl;

    std::advance(it, 3);
    std::cout << *it << std::endl;

    return 0;
}
```

[Example](https://www.godbolt.org/z/P17PEnsaE)

- [`std::next()` : cppreference](https://en.cppreference.com/w/cpp/iterator/next)
- [`std::prev()` : cppreference](https://en.cppreference.com/w/cpp/iterator/prev)
- [`std::distance()` : cppreference](https://en.cppreference.com/w/cpp/iterator/distance)
- [`std::advance()` : cppreference](https://en.cppreference.com/w/cpp/iterator/advance)

### Task 1.5 : Sentinels

Iterators are able to move through a container indefinitely however this can lead to iterators being dereferenced for a value that doesn't belong to the container. To fix this, we need some notion of the end of a container. Sentinels are a kind that behaves like a marker representing the end of a container. There are many different things you can use as a sentinel from specific values that appear in a container (`\0` is used as a sentinel for char slices in C), to iterators. Before C++20, the 'end' iterator was the most common sentinel kind used. The iterator holds the item that is one-past-the-end of a container. When another iterator reaches it the container has been exhausted. Since C++20, the notion of the end of a container has been formalised to be sentinels over 'end' iterators. This allows for containers to be infinite with an unreachable sentinel type or have regular bounds.

```cxx
#include <array>
#include <iostream>
#include <iterator>

auto main() -> int
{
    auto a = std::to_array<int>({1, 3, 4, 565, 868, 5, 46});
    
    /// Uses the iterator obtained by `std::end` from `a` as sentinel
    for (auto it = std::begin(a); it != std::end(a); ++it)
        std::cout << *it << (std::distance(it, std::end(a)) - 1 ? ", " : "");

    return 0;
}
```

[Example](https://www.godbolt.org/z/9dzsjn1eM)

- [`std::default_sentinel_t` : cppreference](https://en.cppreference.com/w/cpp/iterator/default_sentinel_t)
- [`std::unreachable_sentinel_t` : cppreference](https://en.cppreference.com/w/cpp/iterator/unreachable_sentinel_t)
- [`std::move_sentinel<S>` : cppreference](https://en.cppreference.com/w/cpp/iterator/move_sentinel)

### Task 1.6 : Iterator Adaptors

There are a few iterator adaptors in the C++ standard library allowing for regular iterators, often supplied by container kind types have certain operational semantics. This include a reverse, inserter, counted and move iterators. This allows for efficient operations between containers and containers to be implemented through iterators. Many of these iterators come with a factory function (often prefixed with `make_`) that can make the desired iterator and perform the necessary argument type deductions.

- [`std::reverse_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/reverse_iterator)
- [`std::move_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/move_iterator)
- [`std::common_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/common_iterator)
- [`std::counted_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/counted_iterator)
- [`std::back_insert_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/back_insert_iterator)
- [`std::front_insert_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/front_insert_iterator)
- [`std::insert_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/insert_iterator)
- [`std::istream_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/istream_iterator)
- [`std::ostream_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/ostream_iterator)
- [`std::istreambuf_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/istreambuf_iterator)
- [`std::ostreambuf_iterator` : cppreference](https://en.cppreference.com/w/cpp/iterator/ostreambuf_iterator)

## Links

- [Previous Page : Chapter 6](/content/chapter6/README.md)
- [Next Page : Data Structures](/content/chapter6/tasks/data-structures.md)
- [Content](/content/README.md)
- [HOME](/README.md)
