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
      - [Task 3.5.5 : Equal Range, Lower Bound \& Upper Bound](#task-355--equal-range-lower-bound--upper-bound)
    - [Task 3.6 : Modifiers](#task-36--modifiers)
      - [Task 3.6.1 : Copy \& Move](#task-361--copy--move)
      - [Task 3.6.2 : Swap Range](#task-362--swap-range)
      - [Task 3.6.3 : Remove \& Replace](#task-363--remove--replace)
      - [Task 3.6.4 : Reverse](#task-364--reverse)
      - [Task 3.6.5 : Transform](#task-365--transform)
      - [Task 3.6.6 : Rotate](#task-366--rotate)
      - [Task 3.6.7 : Unique](#task-367--unique)
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
      - [Task 3.8.2 : Lexicographical Compare](#task-382--lexicographical-compare)
      - [Task 3.8.3 : All, Any \& None](#task-383--all-any--none)
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

`std::sort` is C++ sorting algorithm. Along with the input range, it can also take in a predicate (a binary function returning a Boolean) which is used for the comparison. This defaults to `<` making `std::sort` sort in ascending order. `std::sort` sorts in-place and is often implemented as an Introsort algorithm.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

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

`std::adjacent_find` returns the location of the first pair of adjacent elements in a ranges that satisfy a predicate. The default predicate is `==`.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 3, 4, 5 };

    println(v);
    auto result = std::adjacent_find(v.begin(), v.end());
    
    (result == v.end() ? std::cout << "no equal adjacent elemnts" << std::endl
                       : std::cout << "first equal adjacent elements occured at offset: " 
                                   << std::distance(v.begin(), result) 
                                   << " with *result = "
                                   << *result
                                   << std::endl);

    
    return 0;
}
```

[Example](https://www.godbolt.org/z/WMxqEezfn)

[`std::adjacent_find` : cppreference](https://en.cppreference.com/w/cpp/algorithm/adjacent_find)

#### Task 3.5.4 : Binary Search

Everyone knows the binary search algorithm however, `std::binary_search` is a little different. Instead of returning the location of the desired element it returns `true` if the desired value exists in the range and `false` otherwise. `std::binary_search` iin C++ is more commonly spelt **_in_**. `std::binary_search` one works on a partially ordered ranged with respect to the desired value. Partitioning with respect to the desired value is the minimum sorting requirement.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 5 };

    println(v);
    
    std::cout << std::boolalpha
              << "Found 2? -- " 
              << std::binary_search(v.begin(), v.end(), 2)
              << std::endl
              << "Found 6? -- "
              << std::binary_search(v.begin(), v.end(), 6)
              << std::noboolalpha
              << std::endl;

    
    return 0;
}
```

[Example](https://www.godbolt.org/z/xq7cerxYf)

[`std::binary_search` : cppreference](https://en.cppreference.com/w/cpp/algorithm/binary_search)

#### Task 3.5.5 : Equal Range, Lower Bound & Upper Bound

These algorithms work on partitioned ranges with respect to some value (similar to `std::binary_search`). `std::equal_range` returns a pair of iterators representing the sub-range of elements that are equal to the desired value. `std::lower_bound` and `std::upper_bound` will return an iterator representing the first value do not satisfy a predicate (default `<`) with the right argument always being the desired value for `std::lower_bound` and the left argument always being the desired value for `std::upper_bound`.

> Note: These algorithms are also member functions of all associative containers and some of the unordered associative containers.

```cxx
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 4, 4, 5 };

    println(v);

    auto [eq1, eq2] = std::equal_range(v.begin(), v.end(), 4);
    auto lwbnd4 = std::lower_bound(v.begin(), v.end(), 4);
    auto upbnd4 = std::upper_bound(v.begin(), v.end(), 4);
    
    std::cout << "Range containing 4:" << std::endl;
    println(std::vector<int>(eq1, eq2));
    std::cout << "Lower bound of 4: " << *lwbnd4 << std::endl;
    std::cout << "Upper bound of 4: " << *upbnd4 << std::endl;

    
    return 0;
}
```

[Example](https://www.godbolt.org/z/eTK3jaKb7)

- [`std::equal_range` : cppreference](https://en.cppreference.com/w/cpp/algorithm/equal_range)
- [`std::lower_bound` : cppreference](https://en.cppreference.com/w/cpp/algorithm/lower_bound)
- [`std::upper_bound` : cppreference](https://en.cppreference.com/w/cpp/algorithm/upper_bound)

### Task 3.6 : Modifiers

Modifiers are the bread and butter of the algorithms library. They are used to modify the values of sequences sometimes in-place and other times using an output iterator that becomes the writer of the algorithm. The writer iterator can be the same iterator as the one representing the start of the input ranges as long as it supports write operations (assignment to). These algorithms will often return `void` for in-place modifications or return the end iterator of the output range.

#### Task 3.6.1 : Copy & Move

The copy and move algorithms are pretty self explanatory, they well copy of move the elements from one range to another. These algorithms eliminate 90% of the use of a manual for-loop and allow for copying and moving from completely different ranges, as long as the underlying copy of move is support ie. they types are copyable or movable.

```cxx
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

auto main() -> int
{
    auto v1 = std::vector<std::string>{ "a", "b", "c", "d", "e" };
    auto v2 = std::vector<std::string>{};       ///< Empty vector
    auto v3 = std::vector<std::string>(5, "");  ///< Preallocated memory

    println(v1);
    println(v2);
    println(v3);

    /// Use back inserted to push copies to the back 
    /// of the vector as v2 has no allocated memory
    std::copy(v1.begin(), v1.end(), std::back_inserter(v2));

    /// Can us v3 iterator directly as it has
    /// preallocated memory
    std::move(v1.begin(), v1.end(), v3.begin());
    std::cout << std::endl;

    println(v1);
    println(v2);
    println(v3);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/jrhM39hz4)

- [`std::copy` : cppreference](https://en.cppreference.com/w/cpp/algorithm/copy)
- [`std::move` : cppreference](https://en.cppreference.com/w/cpp/algorithm/move)

#### Task 3.6.2 : Swap Range

`std::swap_range` is a range based form of `std::swap`. It will swap the values of two ranges until the end of the first rnage is reached.

```cxx
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

auto main() -> int
{
    auto v1 = std::vector<std::string>{ "a", "b", "c", "d", "e" };
    auto v2 = std::vector<std::string>{ "v", "w", "x", "y", "z" };

    println(v1);
    println(v2);

    std::swap_ranges(v1.begin(), v1.end(), v2.begin());
    std::cout << std::endl;

    println(v1);
    println(v2);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/3eqcdfG4f)

[`std::swap_ranges` : cppreference](https://en.cppreference.com/w/cpp/algorithm/swap_ranges)

#### Task 3.6.3 : Remove & Replace

`std::remove` and `std::replace` are also fairly simple algorithms. They will remove or replace all instances of a particular value or replacing it with a new value respectively. `std::remove` doesn't actually free memory, usually it just moves any other value forward in the range. To free the removed memory, a call to `std::remove` is followed by a call to the containers erase method or `std::erase` (for sequence containers), taking the iterator returned by `std::remove` and the containers end iterator forming the _remove-erase idiom_.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 2, 3, 5, 1, 2, 2, 3, 4, 2, 5, 3 };

    println(v);
    auto r = std::remove(v.begin(), v.end(), 3);
    std::cout << std::endl;
    println(v);
    v.erase(r, v.end());
    std::cout << std::endl;
    println(v);
    std::replace(v.begin(), v.end(), 2, -2);
    std::cout << std::endl;
    println(v);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/Er64q3T3b)

- [`std::remove` : cppreference](https://en.cppreference.com/w/cpp/algorithm/remove)
- [`std::replace` : cppreference](https://en.cppreference.com/w/cpp/algorithm/replace)

#### Task 3.6.4 : Reverse

`std::reverse` is an in-place modifier that reverses the elements of the container by swapping iterators.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 5 };

    println(v);
    std::reverse(v.begin(), v.end());
    println(v);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/cjT6vEd7M)

[`std::reverse` : cppreference](https://en.cppreference.com/w/cpp/algorithm/reverse)

#### Task 3.6.5 : Transform

`std::transform` one of the most important algorithms in any programming language. `std::transform` will apply an unary function on every element in a range, writing it to a new output range. It also is overloaded to take an additional input iterator allowing for binary transformations. `std::transform` is most commonly spelt as **_map_** in Computer Science however, this name was taken be `std::map`.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v1 = std::vector<int>{ 0, 1, 2, 3, 4 };
    auto v2 = std::vector<int>{ 9, 8, 7, 6, 5 };

    println(v1);
    std::transform(v1.begin(), v1.end(), v1.begin(), [](const auto& x){ return x * x; });
    println(v1);
    std::cout << std::endl;
    std::cout << "  ";
    println(v1);
    std::cout << "+ ";
    println(v2);
    std::transform(v1.begin(), v1.end(),
                   v2.begin(), v1.begin(),
                   [](const auto& x, const auto& y){ return x + y; });
    std::cout << "= ";
    println(v1);

    
    return 0;
}
```

[Example](https://www.godbolt.org/z/9n9WjerzG)

[`std::transform` : cppreference](https://en.cppreference.com/w/cpp/algorithm/transform)

#### Task 3.6.6 : Rotate

`std::rotate` takes three iterators first, pivot and end respectively. As normal, first and end form the range the algorithm operates on while pivot is swapped such that it becomes the new starting element of the range and the element preceding the pivot becomes the new end of the range.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6 };

    println(v);
    std::rotate(v.begin(), v.begin() + 3, v.end());
    println(v);

    
    return 0;
}
```

[Example](https://www.godbolt.org/z/YTnEn1o7d)

[`std::rotate` : cppreference](https://en.cppreference.com/w/cpp/algorithm/rotate)

#### Task 3.6.7 : Unique

Unique logically removes all duplicate elements that occur in a series. This is done by moving the duplicates to the back of the range where they hold an undeterminable value. Returns an iterator indicated the start for the sub-range of undetermined elements. Like `std::remove`, `std::unique` is often paired with a call to an erasure method to actually clear the elements. `std::unique` defaults to using `==` as the default predicate but can take any kind of predicate.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 0, 0, 1, 1, 1, 2, 2, 2 };

    println(v);
    auto r = std::unique(v.begin(), v.end());
    println(v);
    v.erase(r, v.end());
    println(v);

    
    return 0;
}
```

[Example](https://www.godbolt.org/z/Kf1vv8G8E)

[`std::unique` : cppreference](https://en.cppreference.com/w/cpp/algorithm/unique)

#### Task 3.6.10 : Sample

`std::sample` will sample $n$ random elements a range without replacement such that each sampled element has an equal probability of appearing. `std::sample` takes in a random number generator from the `<random>` header in order to generate the random access.

```cxx
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto s = std::vector<int>(4);

    println(v);
    std::sample(v.begin(), v.end(),
                s.begin(), s.size(),
                std::mt19937{ std::random_device{}() });
    println(s);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/rr6PPbb8a)

- [`std::sample` : cppreference](https://en.cppreference.com/w/cpp/algorithm/sample)
- [`<random>` : cppreference](https://en.cppreference.com/w/cpp/header/random)
- [Pseudo-random number generation : cppreference](https://en.cppreference.com/w/cpp/numeric/random)
- [`std::mersenne_twister_engine` : cppreference](https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine)

#### Task 3.6.11 : Shuffle

`std::shuffle` will randomly reorganize a range. Like `std::sample`, `std::shuffle` takes in a random number generator in order to randomly generate the index sequence.

```cxx
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    println(v);
    std::shuffle(v.begin(), v.end(), std::mt19937{ std::random_device{}() });
    println(v);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/cjY6W7cPe)

[`std::shuffle` : cppreference](https://en.cppreference.com/w/cpp/algorithm/)

### Task 3.7 : Numeric

Numerical algorithms are powerful algorithms for performing numerical computation on ranges. Many of the numerical algorithms in C++ are specialised forms of a reduction. Reductions will take a range of values and reduce the the number of elements in the resulting range. Reductions often come in the form of a folding algorithm which take and initial value, a range and a binary function. They break a range of elements into a _Head_ and _Tail_ component, with the _Head_ being the first element and _Tail_ being the rest. There are two version folds called left and right folds. A left fold will apply the initial value along with the result of left folding the _Tail_; with _Head_ being the new initial value, to the binary function. Right folds will invert this process applying _Head_ and the result of right folding the _Tail_ of the range; passing the initial value to the bottom of the fold, to the binary function. Folds spelt as reductions are often left folds with the initial value being the _Head_ of the range.

[Fold](https://docs.google.com/spreadsheets/d/16isUb2rsuzSmkJLO_FtjGCzsQJOAeRKWARBUGn_mrHI/edit#gid=631619717)

#### Task 3.7.1 : Minimums & Maximums

Minimum and maximum reductions are used to find the smallest and largest number in a range. In C++ these are spelt as `std::min_element`, `std::max_element`. These algorithms return an iterator to the element most satisfying the predicate which is defaulted to `<` but can be customised. There is also `std::minmax_element` which returns a pair of iterators indicating the minimum and maximum element in a range.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 3, 5, 0, 2, 6 };

    println(v);
    auto min1 = std::min_element(v.begin(), v.end());
    auto max1 = std::max_element(v.begin(), v.end());
    auto [min2, max2] = std::minmax_element(v.begin(), v.end());
    
    std::cout << "Min: " << *min1 << " @ " << std::distance(v.begin(), min1) << std::endl;
    std::cout << "Max: " << *max1 << " @ " << std::distance(v.begin(), max1) << std::endl;
    std::cout << "Min, Max: [" 
              << *min2 << ", " << *max2 
              << "] @ [" 
              << std::distance(v.begin(), min2)
              << ", "
              << std::distance(v.begin(), max2)
              << "]"
              << std::endl;
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/G8Y9dchEv)

[`std::min_element` : cppreference](https://en.cppreference.com/w/cpp/algorithm/min_element)
[`std::max_element` : cppreference](https://en.cppreference.com/w/cpp/algorithm/max_element)
[`std::minmax_element` : cppreference](https://en.cppreference.com/w/cpp/algorithm/minmax_element)

#### Task 3.7.2 : Count

`std::count` will count that number of occurrences of a particular value. The default predicate is `==` but it can be customised.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 2, 1, 3, 5, 2, 2, 3, 0, 2, 6, 2 };
    auto e = int{ 2 };

    println(v);
    std::cout << "Number of " << e << "'s = " << std::count(v.begin(), v.end(), e) << std::endl;
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/5xejqWf6s)

[`std::count` : cppreference](https://en.cppreference.com/w/cpp/algorithm/count)

#### Task 3.7.3 : Clamp

`std::clamp` is a scalar algorithm (doesn't work for ranges) that will clamp a value between a set range. If the value is smaller then the lower bound it is clamped to the lower bound and if it is larger than the upper bound it clamps to the upper bound, returning the value otherwise. `std::clamp` is not a reduction.

> Note: If the return value is bound to a reference and the value is a temporary to the call to `std::clamp` the reference is dangling.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto low = int{ 2 };
    auto high = int{ 3 };


    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6 };

    println(v);
    std::transform(v.begin(), v.end(), v.begin(),
                   [&](const auto& x){ return std::clamp(x, low, high); });
    println(v);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/q5sWsrK1x)

[`std::clamp` : cppreference](https://en.cppreference.com/w/cpp/algorithm/clamp)

#### Task 3.7.4 : Accumulate

`std::accumulate` is the most general numeric algorithm and can be used to implement almost all of the algorithms in the C++ standard. Accumulate takes a range of values, an initial value and a binary function defaulting to `+`. Accumulate is most commonly spelt as left-fold or foldl. `std::accumulate` is one of the only algorithms that returns a value. One point to note about `std::accumulate` is that the initial values type is unrelated to the type of the range of elements. This can cause unintended side effects due to implicit conversions. `std::accumulate` is not found in `<algorithm>` but rather `<numeric>`.

> One algorithm `std::accumulate` should not try and model is function application of maps (ie. `std::transform`).

```cxx
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    println(v);

    auto sum     = std::accumulate(v.begin(), v.end(), 0);
    auto product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<>{});
    std::cout << "Sum of v = " << sum << std::endl;
    std::cout << "Product of v = " << product << std::endl;
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/v3jEMP4c1)

[`std::accumulate` : cppreference](https://en.cppreference.com/w/cpp/algorithm/accumulate)

#### Task 3.7.5 : Inner Product

`std::inner_product` is a very powerful algorithm. It performs a binary transformation of two ranges and then performs a reduction on the resulting range. The most common form of this algorithm is known as the dot-product which applies the binary `*` on the two sets of coordinates and then a binary reduction on the resulting range using `+`. This is the default operation set for C++ `std::inner_product` but it can be customised to using any binary transformation and reduction. Like `std::accumulate` is takes an initial value which is applied to the and returns the result of the reduction. `std::inner_product` also lives in the `<numeric>` header.

```cxx
#include <iostream>
#include <numeric>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 1, 3, 5, 7, 9 };
    auto u = std::vector<int>{ 0, 2, 4, 6, 8 };

    auto r = std::inner_product(v.begin(), v.end(), u.begin(), 0);

    std::cout << "v: ";
    println(v);
    std::cout << "     x  x  x  x  x   + => " << r << std::endl;
    std::cout << "u: ";
    println(u);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/schxqWbo3)

[`std::inner_product` : cppreference](https://en.cppreference.com/w/cpp/algorithm/inner_product)

#### Task 3.7.6 : Partial Sum

`std::partial_sum` is another reduction algorithm but with a twist. Instead of reducing the range to a scalar, it partially reduces the range, saving the intermediate accumulation values. This algorithm is most commonly spelt as left scan or `scanl`. `std::partial_sum` does not take an initial but does take an iterator to the beginning of the output range. Returns the element pointing to one-past-the-end element of the output range. `std::partial_sum` is in the `<numeric>` header. The default binary function is `+`.

```cxx
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto u = std::vector<int>(v.size(), 0);
    auto w = std::vector<int>(v.size() - 1, 0);

    std::partial_sum(v.begin(), v.end(), u.begin());
    std::partial_sum(v.begin() + 1, v.end(), w.begin(), std::multiplies<>{});

    println(v);
    println(u);
    println(w);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/YnWdvq1nv)

[`std::partial_sum` : cppreference](https://en.cppreference.com/w/cpp/algorithm/partial_sum)

#### Task 3.7.7 : Adjacent Difference

`std::adjacent_difference` applies the the binary function `-` (by default) to every pair of neighboring elements writing them to a new range. This range begins at one after the passed output iterator.

```cxx
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 4, 6, 9, 13, 18, 19, 19, 15, 10 };
    auto u = std::vector<int>(v.size(), 0);
    auto w = std::vector<int>(v.size(), 0);
    w[0] = 1;

    std::adjacent_difference(v.begin(), v.end(), u.begin());
    std::adjacent_difference(w.begin(), std::prev(w.end()), std::next(w.begin()), std::plus<>{});

    println(v);
    println(u);
    std::cout << std::endl << "Fibonacci: ";
    println(w);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/rbvK3P1ah)

[`std::adjacent_difference` : cppreference](https://en.cppreference.com/w/cpp/algorithm/adjacent_difference)

### Task 3.8 : Comparisons

The following algorithms are used to perform comparisons and conditional checks both between ranges and within a range. They all return a Boolean indicating the result of the comparison.

#### Task 3.8.1 : Equal

`std::equal` performs applies a predicate to two ranges. The default predicate is `==` but any can be used.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v1 = std::vector<int>{ 0, 1, 2, 3, 4, 5 };
    auto v2 = std::vector<int>{ 1, 2, 3, 4, 5, 6 };

    println(v1);
    println(v2);

    std::cout << std::boolalpha 
              << std::equal(v1.begin(), v1.end(), v2.begin(), std::less<>{})
              << std::endl;
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/fs1T64vq5)

[`std::equal` : cppreference](https://en.cppreference.com/w/cpp/algorithm/equal)

#### Task 3.8.2 : Lexicographical Compare

`std::lexicographical_compare` checks if the first range is lexicographically less then the second range. The predicate _less_ can be changed.

```cxx
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

auto main() -> int
{
    auto s1 = std::string{ "Hello" };
    auto s2 = std::string{ "Hi" };

    std::cout << std::quoted(s1) << std::endl;
    std::cout << std::quoted(s2) << std::endl;

    std::cout << std::boolalpha 
              << std::lexicographical_compare(s1.begin(), s1.end(),
                                              s2.begin(), s2.end())
              << std::endl;
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/YqovzcTYM)

[`std::equal` : cppreference](https://en.cppreference.com/w/cpp/algorithm/equal)

#### Task 3.8.3 : All, Any & None

The three algorithms `std::all_of`, `std::any_of` and `std::none_of` will apply an unary predicate on a range returning `true` if all of, any of or none of the elements satisfy the predicate and `false` otherwise.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5 };

    println(v);

    std::cout << std::boolalpha 
              << "All Odd? -- "
              << std::all_of(v.begin(), v.end(), [](const auto& e){ return !(e % 2 == 0); })
              << std::endl
              << "Any Even? -- "
              << std::any_of(v.begin(), v.end(), [](const auto& e){ return e % 2 == 0; })
              << std::endl
              << "None are 7? -- "
              << std::none_of(v.begin(), v.end(), [](const auto& e){ return e == 7; })
              << std::endl;
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/hddx535Wj)

[`std::all_of`, `std::any_of` & `std::none_of` : cppreference](https://en.cppreference.com/w/cpp/algorithm/all_any_none_of)

### Task 3.9 : Generators

Generators allow for ranges to be filled with values after their initial construction. They are useful for manufacturing values without the need of literals.

#### Task 3.9.1 : Fill

`std::fill` is the most simple generator. It fills an entire range with a single value, modifying the range in-place.

```cxx
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5 };

    println(v);
    std::fill(v.begin(), v.end(), 8);
    println(v);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/57ssP7P36)

[`std::fill` : cppreference](https://en.cppreference.com/w/cpp/algorithm/fill)

#### Task 3.9.2 : Iota

`std::iota` is a powerful factory based generator. It is supplied and initial value and will increment (using `++`) that initial value as it iterates through the range and assigns the current iterator with the incremented value. Iota is a common factory used in many different programming languages. Its original name is iota but it is often spelt **_range_**. `std::iota` is part of the `<numeric>` header. Like `std::fill`, `std::iota` modifies a sequence in-place.

```cxx
#include <iostream>
#include <numeric>
#include <vector>

auto main() -> int
{
    auto v = std::vector<int>{ 0, 1, 2, 3, 4, 5 };

    println(v);
    std::iota(v.begin(), v.end(), -2);
    println(v);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/oz1179Gn6)

[`std::iota` : cppreference](https://en.cppreference.com/w/cpp/algorithm/iota)

#### Task 3.9.3 : Generate

`std::generate` is the most primitive generator algorithm. Instead of taking an initial value, it takes a function that gets called repeatedly on each iteration. This algorithm modifies the range in-place.

```cxx
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

auto main() -> int
{
    auto v    = std::vector<int>(10);
    auto rd   = std::random_device{};
    auto gn   = std::mt19937{ rd() };
    auto dist = std::uniform_int_distribution<>{ 0, 10 };

    println(v);
    std::generate(v.begin(), v.end(), [&]() { return dist(gn); });
    println(v);
    
    return 0;
}
```

[Example](https://www.godbolt.org/z/s3GrYnv1a)

[`std::generate` : cppreference](https://en.cppreference.com/w/cpp/algorithm/generate)

### Task 3.10 : Algorithm Extensions

Many algorithms have customised counterparts. These customisations include variants that take a predicate, or a size `n` instead of and end iterator. This are suffixed with markers such as `_if` or `_n` in the algorithm functions name. Look at cppreference for a comprehensive list of these variants.

## Links

- [Previous Page : Data Structures](/content/part6/tasks/data-structures.md)
- [Next Page : Ranges](/content/part6/tasks/ranges.md)
- [Content](/content/README.md)
- [HOME](/README.md)
