# Algorithms

## Contents

- [Algorithms](#algorithms)
  - [Contents](#contents)
  - [Task 3](#task-3)
    - [Task 3.1 : What is an algorithm?](#task-31--what-is-an-algorithm)
      - [Task 3.1.1 : Algorithm Intuition](#task-311--algorithm-intuition)
    - [Task 3.2 : The Standard Template Library](#task-32--the-standard-template-library)
    - [Task 3.3 : General](#task-33--general)
    - [Task 3.4 : Sorting](#task-34--sorting)
      - [Task 3.4.1 : Sort](#task-341--sort)
      - [Task 3.4.2 : Partition](#task-342--partition)
      - [Task 3.4.3 : Nth Element](#task-343--nth-element)
      - [Task 3.4.4 : Mismatch](#task-344--mismatch)
    - [Task 3.5 : Searching](#task-35--searching)
      - [Task 3.5.1 : Find](#task-351--find)
      - [Task 3.5.2 : Search](#task-352--search)
      - [Task 3.5.3 : Adjacent Find](#task-353--adjacent-find)
      - [Task 3.5.4 : Binary Search](#task-354--binary-search)
      - [Task 3.5.5 : Lower Bound](#task-355--lower-bound)
      - [Task 3.5.6 : Upper Bound](#task-356--upper-bound)
      - [Task 3.5.7 : Equal Range](#task-357--equal-range)
    - [Task 3.6 : Modifiers](#task-36--modifiers)
      - [Task 3.6.1 : Copy](#task-361--copy)
      - [Task 3.6.2 : Move](#task-362--move)
      - [Task 3.6.3 : Swap Range](#task-363--swap-range)
      - [Task 3.6.4 : Remove](#task-364--remove)
      - [Task 3.6.5 : Replace](#task-365--replace)
      - [Task 3.6.6 : Reverse](#task-366--reverse)
      - [Task 3.6.7 : Transform](#task-367--transform)
      - [Task 3.6.8 : Rotate](#task-368--rotate)
      - [Task 3.6.9 : Unique](#task-369--unique)
      - [Task 3.6.10 : Sample](#task-3610--sample)
      - [Task 3.6.11 : Shuffle](#task-3611--shuffle)
    - [Task 3.7 : Numeric](#task-37--numeric)
      - [Task 3.7.1 : Minimums \& Maximums](#task-371--minimums--maximums)
      - [Task 3.7.2 : Count](#task-372--count)
      - [Task 3.7.3 : Clamp](#task-373--clamp)
      - [Task 3.7.4 : Accumulate](#task-374--accumulate)
      - [Task 3.7.5 : Inner Product](#task-375--inner-product)
      - [Task 3.7.6 : Partial Sum](#task-376--partial-sum)
      - [Task 3.7.7 : Adjacent Difference](#task-377--adjacent-difference)
    - [Task 3.8 : Comparisons](#task-38--comparisons)
      - [Task 3.8.1 : Equal](#task-381--equal)
      - [Task 3.8.2 : All, Any \& None](#task-382--all-any--none)
    - [Task 3.9 : Generators](#task-39--generators)
      - [Task 3.9.1 : Fill](#task-391--fill)
      - [Task 3.9.2 : Iota](#task-392--iota)
      - [Task 3.9.3 : Generate](#task-393--generate)
    - [Task 3.10 : Algorithm Extensions](#task-310--algorithm-extensions)
  - [Links](#links)

## Task 3

### Task 3.1 : What is an algorithm?

What is an algorithm? The simplest definition is that is is a function. The longer definition is that an algorithm is a set of instructions that occur in a finite number of steps. Algorithms are used to manipulate data, perform computation or even perform introspection on data. Powerful algorithms when paired with efficient data structures are what make programs. So far we have seen how to create our own data structures in C++ through classes and concepts. We have also seen the data structures already offered by C++, we will now look at how you can use any algorithm available in C++ with all of these data structures and perform computation entirely (almost) independent of how it is organised.

#### Task 3.1.1 : Algorithm Intuition

This section is not really about how to implement any particular algorithm. Instead it is aimed at building what is called algorithm intuition. This focuses not on how I do make an algorithm that performs the steps X, Y and Z to some data, taking into account A, B and C but rather on knowing about existing algorithms, what they do and how you can piece and compose different algorithms together to create a more general solution. This idea of composition is a super power to programming as it enables creating solutions from smaller reusable components.

### Task 3.2 : The Standard Template Library

The C++ algorithms library as it stands today was created by the brilliant mind of [Alexander Stepanov](https://en.wikipedia.org/wiki/Alexander_Stepanov). Alex Stepanov was a pioneer in practical generic programming and created what is known as the Standard Template Library (STL). The STL was the predecessor to everything in the C++ Standard Library that uses templates which is almost everything. The biggest edition to the C++ standard from the STL was the container and algorithm libraries. All algorithms in C++ use iterator pairs (with identical types), one to the beginning of a sequence and one to the end. This means that any container just has to provide an iterator to its first and last elements and any algorithm can work with it. A pair of iterators is called a range in C++. All algorithms take at least a pair of iterators with some taking more.

[`<algorithm>` : cppreference](https://en.cppreference.com/w/cpp/algorithm)

### Task 3.3 : General

The most general algorithm is `std::for_each`. This algorithm can take a single ranges and an unary function that will be applied to each element. `std::for_each` is often used to replace for-loops in certain context, mostly when a function has a side effect.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 5 };

    std::for_each(v.begin(), v.end(), [](const auto& e){ std::cout << e << ' '; });

    return 0;
}
```

[Example](https://www.godbolt.org/z/W1croE686)

[`std::for_each` : cppreference](https://en.cppreference.com/w/cpp/algorithm/for_each)

### Task 3.4 : Sorting

Sorting is a very common operation in programming. It allows us to more efficiently search for particular elements and guarantee certain properties and relationships between elements. In C++ there are a few different kinds of sorting algorithms including partitioning and introspection of data.

#### Task 3.4.1 : Sort

`std::sort` is C++ sorting algorithm. Along with the input range, it can also take in a predicate (a function returning a Boolean) which is used for the comparison. This defaults to `<` making `std::sort` sort in ascending order. `std::sort` sorts in-place and is often implemented as an Introsort algorithm.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template<typename T>
auto println(const std::vector<T>& v) -> void
{
    std::cout << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        std::cout << e << (--i ? ", " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto v = std::vector<int>{ 2, 576, -3, 678, 3, -2543, 6 };

    println(v);
    std::sort(v.begin(), v.end());
    println(v);

    std::sort(v.begin(), v.end(), std::greater<>{});
    println(v);

    return 0;
}
```

[Example](https://www.godbolt.org/z/d9K618hhn)

[`std::sort` : cppreference](https://en.cppreference.com/w/cpp/algorithm/sort)

#### Task 3.4.2 : Partition

Partitioning is the process of sorting elements based on a predicate such that any element for which the predicate is `true` precedes any element for which the predicate is `false`. This can be used to separate evens and odds or positive and negatives or even implement quicksort. The individual partitions are not necessarily sorted.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template<typename T>
auto println(const std::vector<T>& v) -> void
{
    std::cout << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        std::cout << e << (--i ? ", " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto v = std::vector<int>{ -1, 2, -3, -4, 5 };

    println(v);
    std::partition(v.begin(), v.end(), [](const auto& e){ return e % 2 == 0; });
    println(v);

    std::partition(v.begin(), v.end(), [](const auto& e){ return e > 0; });
    println(v);

    return 0;
}
```

[Example](https://www.godbolt.org/z/48jfqqdcd)

[`std::partition` : cppreference](https://en.cppreference.com/w/cpp/algorithm/partition)

#### Task 3.4.3 : Nth Element

`std::nth_element` sorts a range such that the element pointed to by nth is the element that would occur in that position if the range was sorted. `std::nth_element` is a partial sorting algorithm.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template<typename T>
auto println(const std::vector<T>& v) -> void
{
    std::cout << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        std::cout << e << (--i ? ", " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto v = std::vector<int>{ -24, 573, -3, 677, 3, -2543, 6 };

    println(v);
    auto m = v.begin() + (v.size() / 2);
    std::nth_element(v.begin(), m, v.end());
    std::cout << v[v.size() / 2] << std::endl;
    println(v);

    std::nth_element(v.begin(), v.end() - 2, v.end(), std::greater<>{});
    std::cout << *(v.end() - 2) << std::endl;
    println(v);

    return 0;
}
```

[Example](https://www.godbolt.org/z/GM1rrW68P)

[`std::nth_element` : cppreference](https://en.cppreference.com/w/cpp/algorithm/nth_element)

#### Task 3.4.4 : Mismatch

Finds the first mismatch between two ranges returning an `std::pair` of the iterators to the mismatch in the ranges. The binary predicate (default `==`) can be changed so that mismatch triggers on the first evaluation of `false` from the predicate.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template<typename T>
auto println(const std::vector<T>& v) -> void
{
    std::cout << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        std::cout << e << (--i ? ", " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto v1 = std::vector<int>{ 1, 2, 3, 4, 5 };
    auto v2 = v1;
    v2[3] = 465;

    println(v1);
    println(v2);
    std::cout << std::endl;

    const auto [v1ms, v2ms] = std::mismatch(v1.begin(), v1.end(), v2.begin());
    
    std::cout << "v1: " << *v1ms << ", v2: " << *v2ms << std::endl;    

    return 0;
}
```

[Example](https://www.godbolt.org/z/jj69vr5qe)

[`std::mismatch` : cppreference](https://en.cppreference.com/w/cpp/algorithm/mismatch)

### Task 3.5 : Searching

More often than not, you do not know anything about which values actually exists in your range. This is why searching algorithms are important part of computer programming. They allow us to find elements what we need or handle the case when they do not exist.

#### Task 3.5.1 : Find

`std::find` is used to find a particular value in range. returning the iterator to its location. It is not very efficient but is the most general searcher.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template<typename T>
auto println(const std::vector<T>& v) -> void
{
    std::cout << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        std::cout << e << (--i ? ", " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 5 };

    println(v);
    auto result1 = std::find(v.begin(), v.end(), 3);
    auto result2 = std::find(v.begin(), v.end(), 68);
    
    (result1 == v.end() ? std::cout << 3 << " not found" << std::endl
                        : std::cout << 3 << " found at " << std::distance(v.begin(), result1) << std::endl);

    (result2 == v.end() ? std::cout << 68 << " not found" << std::endl
                        : std::cout << 68 << " found at " << std::distance(v.begin(), result2) << std::endl);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/KhqvGao43)

[`std::find` : cppreference](https://en.cppreference.com/w/cpp/algorithm/find)

#### Task 3.5.2 : Search

`std::search` is used fo find the first occurrence of a subsequence in a range. `std::search` can also be passed a different searcher to change how it searches for the subsequence.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template<typename T>
auto println(const std::vector<T>& v) -> void
{
    std::cout << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        std::cout << e << (--i ? ", " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 5 };
    auto s = std::vector<int>{ 2, 3, 4 };

    println(v);
    println(s);
    auto result = std::search(v.begin(), v.end(), s.begin(), s.end());
    
    (result == v.end() ? std::cout << "sequence { 2, 3, 4 } not found" << std::endl
                       : std::cout << "sequence { 2, 3, 4 } found at offset " << std::distance(v.begin(), result) << std::endl);

    
    return 0;
}
```

[Example](https://www.godbolt.org/z/51cqjG8Pb)

[`std::` : cppreference](https://en.cppreference.com/w/cpp/algorithm/search)

#### Task 3.5.3 : Adjacent Find

~

```cxx

```

[Example]()

[`std::adjacent_find` : cppreference](https://en.cppreference.com/w/cpp/algorithm/adjacent_find)

#### Task 3.5.4 : Binary Search

~

```cxx

```

[Example]()

[`std::binary_search` : cppreference](https://en.cppreference.com/w/cpp/algorithm/binary_search)

#### Task 3.5.5 : Lower Bound

~

```cxx

```

[Example]()

[`std::lower_bound` : cppreference](https://en.cppreference.com/w/cpp/algorithm/lower_bound)

#### Task 3.5.6 : Upper Bound

~

```cxx

```

[Example]()

[`std::upper_bound` : cppreference](https://en.cppreference.com/w/cpp/algorithm/upper_bound)

#### Task 3.5.7 : Equal Range

~

```cxx

```

[Example]()

[`std::equal_range` : cppreference](https://en.cppreference.com/w/cpp/algorithm/equal_range)

### Task 3.6 : Modifiers

~

#### Task 3.6.1 : Copy

~

```cxx

```

[Example]()

[`std::copy` : cppreference](https://en.cppreference.com/w/cpp/algorithm/copy)

#### Task 3.6.2 : Move

~

```cxx

```

[Example]()

[`std::move` : cppreference](https://en.cppreference.com/w/cpp/algorithm/move)

#### Task 3.6.3 : Swap Range

~

```cxx

```

[Example]()

[`std::swap_ranges` : cppreference](https://en.cppreference.com/w/cpp/algorithm/swap_ranges)

#### Task 3.6.4 : Remove

~

```cxx

```

[Example]()

[`std::` : cppreference](https://en.cppreference.com/w/cpp/algorithm/remove)

#### Task 3.6.5 : Replace

~

```cxx

```

[Example]()

[`std::replace` : cppreference](https://en.cppreference.com/w/cpp/algorithm/replace)

#### Task 3.6.6 : Reverse

~

```cxx

```

[Example]()

[`std::reverse` : cppreference](https://en.cppreference.com/w/cpp/algorithm/reverse)

#### Task 3.6.7 : Transform

~

```cxx

```

[Example]()

[`std::transform` : cppreference](https://en.cppreference.com/w/cpp/algorithm/transform)

#### Task 3.6.8 : Rotate

~

```cxx

```

[Example]()

[`std::rotate` : cppreference](https://en.cppreference.com/w/cpp/algorithm/rotate)

#### Task 3.6.9 : Unique

~

```cxx

```

[Example]()

[`std::` : cppreference](https://en.cppreference.com/w/cpp/algorithm/unique)

#### Task 3.6.10 : Sample

~

```cxx

```

[Example]()

[`std::sample` : cppreference](https://en.cppreference.com/w/cpp/algorithm/sample)

#### Task 3.6.11 : Shuffle

~

```cxx

```

[Example]()

[`std::shuffle` : cppreference](https://en.cppreference.com/w/cpp/algorithm/)

### Task 3.7 : Numeric

~

#### Task 3.7.1 : Minimums & Maximums

~

```cxx

```

[Example]()

[`std::min_element` : cppreference](https://en.cppreference.com/w/cpp/algorithm/min_element)
[`std::max_element` : cppreference](https://en.cppreference.com/w/cpp/algorithm/max_element)
[`std::minmax_element` : cppreference](https://en.cppreference.com/w/cpp/algorithm/minmax_element)

#### Task 3.7.2 : Count

~

```cxx

```

[Example]()

[`std::count` : cppreference](https://en.cppreference.com/w/cpp/algorithm/count)

#### Task 3.7.3 : Clamp

~

```cxx

```

[Example]()

[`std::clamp` : cppreference](https://en.cppreference.com/w/cpp/algorithm/clamp)

#### Task 3.7.4 : Accumulate

~

```cxx

```

[Example]()

[`std::accumulate` : cppreference](https://en.cppreference.com/w/cpp/algorithm/accumulate)

#### Task 3.7.5 : Inner Product

~

```cxx

```

[Example]()

[`std::inner_product` : cppreference](https://en.cppreference.com/w/cpp/algorithm/inner_product)

#### Task 3.7.6 : Partial Sum

~

```cxx

```

[Example]()

[`std::partial_sum` : cppreference](https://en.cppreference.com/w/cpp/algorithm/partial_sum)

#### Task 3.7.7 : Adjacent Difference

~

```cxx

```

[Example]()

[`std::adjacent_difference` : cppreference](https://en.cppreference.com/w/cpp/algorithm/adjacent_difference)

### Task 3.8 : Comparisons

#### Task 3.8.1 : Equal

~

```cxx

```

[Example]()

[`std::equal` : cppreference](https://en.cppreference.com/w/cpp/algorithm/equal)

#### Task 3.8.2 : All, Any & None

~

```cxx

```

[Example]()

[`std::all_of`, `std::any_of` & `std::none_of` : cppreference](https://en.cppreference.com/w/cpp/algorithm/all_any_none_of)

### Task 3.9 : Generators

~

#### Task 3.9.1 : Fill

~

```cxx

```

[Example]()

[`std::fill` : cppreference](https://en.cppreference.com/w/cpp/algorithm/fill)

#### Task 3.9.2 : Iota

~

```cxx

```

[Example]()

[`std::iota` : cppreference](https://en.cppreference.com/w/cpp/algorithm/iota)

#### Task 3.9.3 : Generate

~

```cxx

```

[Example]()

[`std::generate` : cppreference](https://en.cppreference.com/w/cpp/algorithm/generate)

### Task 3.10 : Algorithm Extensions

Many algorithms have customised counterparts. These customisations include variants that take a predicate, or a size `n` instead of and end iterator. This are suffixed with markers such as `_if` or `_n` in the algorithm functions name. Look at cppreference for a comprehensive list of these variants.

## Links

- [Previous Page : Data Structures](/content/part6/tasks/data-structures.md)
- [Next Page : Primitive Data Types](/content/part6/tasks/ranges.md)
- [Content](/content/README.md)
- [HOME](/README.md)
