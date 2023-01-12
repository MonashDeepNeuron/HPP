# Iterators

## Contents

- [Iterators](#iterators)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : What is an iterator?](#task-11--what-is-an-iterator)
    - [Task 1.2 : Iterator Categories](#task-12--iterator-categories)
    - [Task 1.3 : Iterator Functionalities](#task-13--iterator-functionalities)
      - [Task 1.3.1 : Common Operator Interface](#task-131--common-operator-interface)
      - [Task 1.3.2 : Iterator Functions](#task-132--iterator-functions)
  - [Links](#links)

## Task 1

### Task 1.1 : What is an iterator?

An iterator is an abstraction for representing an item, element, value etc. in a collection or sequence of values that also has some notion how to get to a obtain or yield a new item from the sequence. In C++ iterators a lot like pointers in the sense that they hold some value, usually the location of it and has a means of either yielding the value for reading or allows for writing to that value.

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

### Task 1.3 : Iterator Functionalities

There are a few ways to interact with an iterator directly. One is to use the overloaded operators for the iterator object. Most iterators implement and overload the same operator set that is used by pointers. The other way is to use functions to interact with iterators, allowing for a more generic interface if a iterator doesn't support the common operator overload set and the implementer preferred to overload the functions. The only way to yield or write to the item held by an iterator is to use the dereference operator `*`.

#### Task 1.3.1 : Common Operator Interface

|  Operations |         |          |          |
|:-----------:|:-------:|:--------:|:--------:|
| dereference |   `*i`  | `*i = v` | `v = *i` |
|  increment  |  `i++`  |   `++i`  |          |
|  decrement  |  `i--`  |   `--i`  |          |
|  difference | `i - j` |          |          |
|   advance   | `i + n` |  `i - n` |          |
|    index    |  `i[n]` |          |          |
|             |         |          |          |

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

#### Task 1.3.2 : Iterator Functions

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

- [`<iterator>` : cppreference](https://en.cppreference.com/w/cpp/header/iterator)
- [`std::next()` : cppreference](https://en.cppreference.com/w/cpp/iterator/next)
- [`std::prev()` : cppreference](https://en.cppreference.com/w/cpp/iterator/prev)
- [`std::distance()` : cppreference](https://en.cppreference.com/w/cpp/iterator/distance)
- [`std::advance()` : cppreference](https://en.cppreference.com/w/cpp/iterator/advance)

## Links

- [Previous Page : Part 6](/content/part6/README.md)
- [Next Page : Data Structures](/content/part6/tasks/data-structures.md)
- [Content](/content/README.md)
- [HOME](/README.md)
