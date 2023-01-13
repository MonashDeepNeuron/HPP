# Data Structures

## Contents

- [Data Structures](#data-structures)
  - [Contents](#contents)
  - [Task 2](#task-2)
    - [Task 2.1 : What is a Data Structure](#task-21--what-is-a-data-structure)
    - [Task 2.2 : Sequence Containers](#task-22--sequence-containers)
      - [Task 2.2.1 : Vector](#task-221--vector)
      - [Task 2.2.2 : Deque](#task-222--deque)
      - [Task 2.2.3 : Forward List](#task-223--forward-list)
      - [Task 2.2.4 : List](#task-224--list)
    - [Task 2.3 : Associative Containers](#task-23--associative-containers)
      - [Task 2.3.1 : Set](#task-231--set)
      - [Task 2.3.2 : Map](#task-232--map)
      - [Task 2.3.3 : Multiset \& Multimap](#task-233--multiset--multimap)
    - [Task 2.4 : Unordered Associative Containers](#task-24--unordered-associative-containers)
      - [Task 2.4.1 : Unordered Set](#task-241--unordered-set)
      - [Task 2.4.2 : Unordered Map](#task-242--unordered-map)
      - [Task 2.4.3 : Unordered Multiset \& Multimap](#task-243--unordered-multiset--multimap)
    - [Task 2.5 : Miscellaneous](#task-25--miscellaneous)
      - [Task 2.5.1 : Bitset](#task-251--bitset)
      - [Task 2.5.2 : Any](#task-252--any)
    - [Task 2.6 : A harsh truth](#task-26--a-harsh-truth)
  - [Links](#links)

## Task 2

### Task 2.1 : What is a Data Structure

Data structures are a fundamental concept in computer science. Data structures are types or classes used to organise and manage data. Data structures differ primarily by their internal means of organising the data they manage to be as optimal as possible and often support various different operations. Using the correct data structure can be a difficult question to answer, particularly in C++ where many operation on these most basic data structures are expected to have as little size and time overhead.

This section mostly goes into a high level look at the data structures or containers available in C++, how they work and to give an idea of when one might use them. All containers have methods for obtaining iterators to their first and last element and all work with a _range-for_ loop.

### Task 2.2 : Sequence Containers

Sequence containers are _Array-Like_ containers in the sense that they model their data as a 1D array of values. Along with slices and `std::array`, C++ offers four other sequence based containers.

#### Task 2.2.1 : Vector

`std::vector` is the most fundamental container in C++. It models a contiguous dynamic array. It has constant ($O(1)$) index-based random access to elements. Vectors offer random access insertion and erasure of elements as well as efficient pushing and popping of elements at the end of the vector. Indexing is **0-based** which is the same for all index based containers. Insertion and erasure is less efficient anywhere in the vector that is not the back ($O(n)$ where $n$ is the number elements past the insertion or erasure) as all elements past the insertion or erasure have to be moved back one cell. Insertion and erasure also (has a chance of \[invalidating\]) invalidates any iterators or references of the shifted elements. Vectors can reserve more memory then it currently uses in order to make any operations involving potential allocations more efficient by pre-allocating the resources. Erasures also do not remove the memory owned by the vector but save it for later use.

```cxx
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
    v.push_back(6);
    println(v);
    v.pop_back();
    v.pop_back();
    println(v);
    v.insert(v.begin() + 3, 77);
    println(v);
    v.erase(v.end() - 4);
    println(v);

    std::cout << "v[4] = " << v[4] << std::endl;        ///< Unsafe version
    std::cout << "v.at(2) = " << v.at(2) << std::endl;  ///< Range checked

    std::cout << "Before v.shrink_to_fit()" << std::endl;
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Capacity: " << v.capacity() << std::endl;
    println(v);

    v.shrink_to_fit();

    std::cout << "After v.shrink_to_fit()" << std::endl;
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Capacity: " << v.capacity() << std::endl;
    println(v);

    v.clear();
    std::cout << "After v.clear()" << std::endl;
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Capacity: " << v.capacity() << std::endl;
    println(v);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/sYhf5rG6r)

[`std::vector` : cppreference](https://en.cppreference.com/w/cpp/container/vector)

#### Task 2.2.2 : Deque

`std::deque` is a double ended queue that offers efficient ($O(1)$) insertion and erasure at both the front and back of a deque while also never invalidating iterators and references to the rest of the elements. Deques elements are not stored contiguously resulting in a larger memory footprint due to 'book-keeping' data for smaller deques when compared to vectors. Deques also have two indirections to get elements compared to vectors single indirection. Deques also cannot reserve extra memory for later use.

```cxx
#include <iostream>
#include <deque>

template<typename T>
auto println(const std::deque<T>& dq) -> void
{
    std::cout << "[> ";
    for (auto i { dq.size() }; const auto& e : dq)
        std::cout << e << (--i ? ", " : "");
    std::cout << " <]" << std::endl;
}

auto main() -> int
{
    auto dq = std::deque<int>{ 1, 2, 3, 4, 5 };

    println(dq);
    dq.push_back(6);
    println(dq);
    dq.pop_back();
    dq.pop_back();
    println(dq);
    dq.push_front(33);
    dq.push_front(914);
    dq.push_front(-44);
    dq.push_front(0);
    println(dq);
    dq.pop_front();
    dq.pop_front();
    println(dq);

    dq.insert(dq.begin() + 3, 77);
    println(dq);
    dq.erase(dq.end() - 4);
    println(dq);

    std::cout << "dq[4] = " << dq[4] << std::endl;        ///< Unsafe version
    std::cout << "dq.at(2) = " << dq.at(2) << std::endl;  ///< Range checked

    std::cout << "Before dq.shrink_to_fit()" << std::endl;
    std::cout << "Size: " << dq.size() << std::endl;
    println(dq);

    dq.shrink_to_fit();

    std::cout << "After dq.shrink_to_fit()" << std::endl;
    std::cout << "Size: " << dq.size() << std::endl;
    println(dq);

    dq.clear();
    std::cout << "After dq.clear()" << std::endl;
    std::cout << "Size: " << dq.size() << std::endl;
    println(dq);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/Tnx49fajv)

[`std::deque` : cppreference](https://en.cppreference.com/w/cpp/container/deque)

#### Task 2.2.3 : Forward List

`std::forward_list` is an implementation of a singly-linked-list offering fast access, insertion and erasure to the beginning of the list. Forward lists also allows for easy merging of two sorted lists as well as operations for reversing and sorting the list. Insertion and erasure has `_after` semantics meaning that these operations occur to the element after the passed iterator.
Forward lists are not indexable.

```cxx
#include <iostream>
#include <forward_list>

template<typename T>
auto println(const std::forward_list<T>& f_lst) -> void
{
    std::cout << "[ ";
    for (auto i { std::distance(f_lst.cbegin(), f_lst.cend()) }; const auto& e : f_lst)
        std::cout << e << (--i ? " -> " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto f_lst = std::forward_list<int>{ 1, 2, 3, 4, 5 };

    println(f_lst);
    f_lst.push_front(33);
    f_lst.push_front(914);
    f_lst.push_front(-44);
    f_lst.push_front(0);
    println(f_lst);
    f_lst.pop_front();
    f_lst.pop_front();
    println(f_lst);

    f_lst.insert_after(f_lst.begin(), 77);
    println(f_lst);
    f_lst.erase_after(f_lst.begin());
    println(f_lst);
    f_lst.clear();
    println(f_lst);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/Y5c4z67Pz)

[`std::forward_list` : cppreference](https://en.cppreference.com/w/cpp/container/forward_list)

#### Task 2.2.4 : List

Along with a singly-linked-list C++ offers a doubly-linked-list called `std::list`. This offers constant ($O(1)$) insertion and erasure anywhere within the container with the biggest benefits occurring at the beginning and end of the list. Lists allow for bidirectional iteration through the container. Iterators and references are not invalidated during insertion and erasure except for the element that got erased.

```cxx
#include <iostream>
#include <list>

template<typename T>
auto println(const std::list<T>& lst) -> void
{
    std::cout << "[ ";
    for (auto i { lst.size() }; const auto& e : lst)
        std::cout << e << (--i ? " <-> " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto lst = std::list<int>{ 1, 2, 3, 4, 5 };

    println(lst);
    lst.push_back(6);
    println(lst);
    lst.pop_back();
    lst.pop_back();
    println(lst);
    lst.push_front(33);
    lst.push_front(914);
    lst.push_front(-44);
    lst.push_front(0);
    println(lst);
    lst.pop_front();
    lst.pop_front();
    println(lst);

    lst.insert(lst.begin(), 77);
    println(lst);
    lst.erase(++lst.begin());
    println(lst);

    lst.clear();
    std::cout << "After lst.clear()" << std::endl;
    std::cout << "Size: " << lst.size() << std::endl;
    println(lst);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/YfoWacKcK)

[`std::list` : cppreference](https://en.cppreference.com/w/cpp/container/list)

### Task 2.3 : Associative Containers

Associative containers are used for sorted data. They allow for very fast searching as well as efficient insertion, erasure and access. Associative containers work by ordering keys and (sometimes) mapping values to these keys.

#### Task 2.3.1 : Set

`std::set` is an ordered collections of unique keys usually sorted in ascending order. Search, insertion and erasure occur in logarithmic time ($O(\log{n})$). Sets also offer merging operations for combining two sets into a single set with all elements merged and sorted. Sets can be accessed using extraction methods that moves the _node-type_ that owns the key value out of the set and gives it to the caller.

> _node-type_ is an exposition only type that is implemented as part of the set. It is not to be used as an independent type.

```cxx
#include <iostream>
#include <set>

template<typename T>
auto println(const std::set<T>& st) -> void
{
    std::cout << "{ ";
    for (auto i { st.size() }; const auto& e : st)
        std::cout << e << (--i ? ", " : "");
    std::cout << " }" << std::endl;
}

auto main() -> int
{
    auto st = std::set<int>{ 1, 2, 3, 4, 5 };

    st.insert(77);
    println(st);
    st.erase(++st.begin());
    println(st);

    std::cout << "st.extract(++st.begin()).value() = " << st.extract(++st.begin()).value() << std::endl;
    std::cout << "st.extract(5).value() = " << st.extract(5).value() << std::endl;
    println(st);

    st.merge(std::set<int>{ -1, 5, 4, 2, 0, 8, 6 });
    std::cout << "After st.merge(...): " << std::endl;
    println(st);

    st.clear();
    std::cout << "After st.clear()" << std::endl;
    std::cout << "Size: " << st.size() << std::endl;
    println(st);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/P8E99q43c)

[`std::set` : cppreference](https://en.cppreference.com/w/cpp/container/set)

#### Task 2.3.2 : Map

`std::map` is the most general associative container available in C++. Maps are made up of ordered key value pairs with strictly unique key values. Searching, key-indexing, insertion and erasure of elements is logarithmic ($O(\log{n})$) in time. Values are obtained using the associated key using indexing syntax. It also offers similar extraction and merging functionalities as sets. Maps in C++ are typically implemented as [Red-Black Trees](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree).

```cxx
#include <iostream>
#include <map>
#include <string>

template<typename K, typename V>
auto println(const std::map<K, V>& m) -> void
{
    std::cout << "[ ";
    for (auto i { m.size() }; const auto& [k, v] : m)
        std::cout << k << ": " << v << (--i ? ", " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto m = std::map<std::string, int>{ {"z", 1}, {"f", 2}, {"a", 3}, {"g", 4}, {"x", 5} };

    println(m);
    m["a"] = 5;         ///< Can read, write and insert
    println(m);
    m["q"] = 7;
    println(m);
    m.at("g") = 265;    ///< Can only be used for read or write, not insert
    println(m);
    m.insert({"w", 77});
    println(m);
    m.insert_or_assign("w", 354658);
    println(m);

    m.erase("a");
    println(m);
    m.erase(++m.begin());
    println(m);

    m.clear();
    std::cout << "After m.clear()" << std::endl;
    std::cout << "Size: " << m.size() << std::endl;
    println(m);

    return 0;
}
```

> Note: In the _range-for_ if `println()`, you may notice a weird syntax for the element. Because iterators to `std::map` yield a `std::pair` we can destructure it straight into individual variables using structured bindings.

[Exmaple](https://www.godbolt.org/z/vEj7MPfc6)

[`std::map` : cppreference](https://en.cppreference.com/w/cpp/container/map)

#### Task 2.3.3 : Multiset & Multimap

Along with the regular set and map classes, C++ offers `std::multiset` and `std::multimap` which hold ordered keys (and values) but allow for duplicate keys. They offer pretty much the exact same interface as the key-exclusive counterparts except that the order of duplicate keys is the same order as their insertion. This order between duplicates remains constant unless the node holding a particular key (and value) is extracted and it's ownership given to the caller. Searching, insertion and erasure take logarithmic time ($O(\log{n})$).

```cxx
#include <iostream>
#include <map>
#include <string>

template<typename K, typename V>
auto println(const std::multimap<K, V>& m) -> void
{
    std::cout << "[ ";
    for (auto i { m.size() }; const auto& [k, v] : m)
        std::cout << k << ": " << v << (--i ? ", " : "");
    std::cout << " ]" << std::endl;
}

auto main() -> int
{
    auto mm = std::multimap<std::string, int>{ {"z", 12}, {"f", 2}, {"a", 3}, {"g", 4}, {"x", 5} };

    println(mm);
    mm.insert({"z", 77});
    println(mm);

    mm.erase("a");
    println(mm);
    mm.erase(++mm.begin());
    println(mm);

    mm.clear();
    std::cout << "After mm.clear()" << std::endl;
    std::cout << "Size: " << mm.size() << std::endl;
    println(mm);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/8j7P4zjYv)

[`std::multiset` : cppreference](https://en.cppreference.com/w/cpp/container/multiset)
[`std::multimap` : cppreference](https://en.cppreference.com/w/cpp/container/multimap)

### Task 2.4 : Unordered Associative Containers

#### Task 2.4.1 : Unordered Set

~

```cxx

```

[Exmaple]()

[`std::unordered_set` : cppreference](https://en.cppreference.com/w/cpp/container/unordered_set)

#### Task 2.4.2 : Unordered Map

~

```cxx

```

[Exmaple]()

[`std::unordered_map` : cppreference](https://en.cppreference.com/w/cpp/container/unordered_map)

#### Task 2.4.3 : Unordered Multiset & Multimap

~

```cxx

```

[Exmaple]()

[`std::unordered_multiset` : cppreference](https://en.cppreference.com/w/cpp/container/unordered_multiset)
[`std::unordered_multimap` : cppreference](https://en.cppreference.com/w/cpp/container/unordered_multimap)

### Task 2.5 : Miscellaneous

#### Task 2.5.1 : Bitset

~

```cxx

```

[Exmaple]()

[`std::bitset` : cppreference](https://en.cppreference.com/w/cpp/utility/bitset)

#### Task 2.5.2 : Any

~

```cxx

```

[Exmaple]()

[`std::any` : cppreference](https://en.cppreference.com/w/cpp/utility/any)

### Task 2.6 : A harsh truth

## Links

- [Previous Page : Week 2](/content/part2/README.md)
- [Next Page : Primitive Data Types](/content/part2/tasks/.md)
- [Content](/content/README.md)
- [HOME](/README.md)
