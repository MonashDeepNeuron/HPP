# Data Structures

## Section 2

### Section 2.1 : What is a Data Structure

Data structures are a fundamental concept in computer science. Data structures are types or classes used to organise and manage data. Data structures differ primarily by their internal means of organising the data they manage to be as optimal as possible and often support various different operations. Using the correct data structure can be a difficult question to answer, chaptericularly in C++ where many operation on these most basic data structures are expected to have as little size and time overhead.

This section mostly goes into a high level look at the data structures or containers available in C++, how they work and to give an idea of when one might use them. All containers have methods for obtaining iterators to their first and last element and all work with a _range-for_ loop.

### Section 2.2 : Sequence Containers

Sequence containers are _Array-Like_ containers in the sense that they model their data as a 1D array of values. Along with slices and `std::array`, C++ offers four other sequence based containers.

#### Section 2.2.1 : Vector

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

#### Section 2.2.2 : Deque

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

#### Section 2.2.3 : Forward List

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

#### Section 2.2.4 : List

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

#### Section 2.2.5 : A harsh truth

While many of these sequences offer a variety of different ways to organise data and offer different performance guarantees to fit different needs when it comes to searching, insertion and erasure, the harsh reality is often this doesn't matter outside of semantics. 99.9% of the time (I'm exaggerating a bit) the best data structure; chaptericularly for sequences based organisation of data, are vectors. Even for searching, sorting, insertion and erasure. This is because computers are so much faster then they were two decades ago and CPU's have much larger (L2) caches. What does this have to do with it? Well, computer memory is sequential in nature meaning that all data that is stored contiguously. Copying, allocating and transfer of sequential memory is almost always faster as the CPU will often vectorize the operation, assuming that it can move sequential from memory to the cache even if it doesn't explicitly know this. Compare this to other data structures, chaptericularly linked-lists which 'optimise' insertion and erasure by having nodes of data spread out throughout memory, removing the restriction on the data needing to be contiguous. What this actually does is prevent the CPU from predicting what memory it might use maximizing the opportunity for a cache miss to occur which is much slower than copying more data. Copies are cheap, especially for `std::vector` as it contains only three pointers. One to the start of the data, one to the end of the used memory and one to the end of the owned memory. All of this pointers are reachable from each other. To get to the data, it costs one pointer indirection to the data and one jump of size `n` to the desired value. This jump happens in constant time as the CPU will already know exactly how many bytes over this is (exactly $n \cdot sizeof(element)$) and can add this directly to the pointer to the start of the data. If the CPU can figure out that memory near the current memory being fetched will ned to be fetched as well it will take as much as it can from the region, optimising the IO the CPU does which is one of the largest bottlenecks of performance. Compare this to many pointer indirections that have to go into getting a single node from a linked list. Not to mention the CPU has no way of determining where the next memory it needs might be, increasing the fetching time the CPU execute. Not to mention that is has to make room in its cache and eject memory every time it reads.

What does this all mean? Don't think too much about which data structure is best based on the $BigO$ complexities. Start with using vectors and arrays and adapt your programs to use specific data structures as you need. After all; for C++, the $BigO$ complexity are minimum requirements for the standard library that must be met by a chaptericular implementation and not their real world average performance. That is not to say that linked lists or deques do not have there uses. Linked lists are used in the Linux kernel to connect and organise related data. It looks very different to lists in C++ but has a pretty intuitive implementation and use. It is implemented as a intrusive linked list. How this works is that a data structure will have a member that is node containing a pointer to the previous and next node. The benefit to this is that the list is not tied to any type as the nodes don't hold any data themselves, instead the data holds information on how to get to the nxe or previous node. This list structure is used everywhere in the Linux kernel and is very efficient.

### Section 2.3 : Associative Containers

Associative containers are used for sorted data. They allow for very fast searching as well as efficient insertion, erasure and access. Associative containers work by ordering keys and (sometimes) mapping values to these keys.

#### Section 2.3.1 : Set

`std::set` is an ordered collections of unique keys usually sorted in ascending order. Search, insertion and erasure occur in logarithmic time ($O(\log{n})$). Sets also offer merging operations for combining two sets into a single set with all elements merged and sorted. Sets can be accessed using extraction methods that moves the _node-type_ that owns the key value out of the set and gives it to the caller.

> _node-type_ is an exposition only type that is implemented as chapter of the set. It is not to be used as an independent type.

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

#### Section 2.3.2 : Map

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

[Exmaple](https://www.godbolt.org/z/Wb5xPhraq)

[`std::map` : cppreference](https://en.cppreference.com/w/cpp/container/map)

#### Section 2.3.3 : Multiset & Multimap

Along with the regular set and map classes, C++ offers `std::multiset` and `std::multimap` which hold ordered keys (and values) but allow for duplicate keys. They offer pretty much the exact same interface as the key-exclusive counterchapters except that the order of duplicate keys is the same order as their insertion. This order between duplicates remains constant unless the node holding a chaptericular key (and value) is extracted and it's ownership given to the caller. Searching, insertion and erasure take logarithmic time ($O(\log{n})$).

```cxx
#include <iostream>
#include <map>
#include <string>

template<typename K, typename V>
auto println(const std::multimap<K, V>& m) -> void
{
    std::cout << "{ ";
    for (auto i { m.size() }; const auto& [k, v] : m)
        std::cout << k << ": " << v << (--i ? ", " : "");
    std::cout << " }" << std::endl;
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

[Exmaple](https://www.godbolt.org/z/ro5MaxeEG)

[`std::multiset` : cppreference](https://en.cppreference.com/w/cpp/container/multiset)
[`std::multimap` : cppreference](https://en.cppreference.com/w/cpp/container/multimap)

### Section 2.4 : Unordered Associative Containers

Unordered associative containers are data structures that do not sort their key values but instead use a hashing function to create bucket based access to elements. Hashing functions are designed to avoid hash collisions however, many hashed data structures account for hash collisions. Hashing is the process of computing a discrete hash value for a key indicating the index in an internalised array or _bucket_. Which bucket a key (and value) is placed in relies solely on the result of hashing that key, with keys creating duplicate hash results being placed in the same bucket (typically).

#### Section 2.4.1 : Unordered Set

`std::unordered_set` is the first of our unordered associative containers. Unlike sets, hashed sets do not need to order their keys. Searching, insertion and erasure in a hashed set occurs in constant time ($O(1)$). Elements of a hashed set cannot be changes as this would invalidate the hash table. Instead erasure and insertion must be used instead.

```cxx
#include <iostream>
#include <unordered_set>
#include <string>

template<typename K>
auto println(const std::unordered_set<K>& ust) -> void
{
    std::cout << "{ ";
    for (auto i { ust.size() }; const auto& k : ust)
        std::cout << k << (--i ? ", " : "");
    std::cout << " }" << std::endl;
}

auto main() -> int
{
    auto ust = std::unordered_set<std::string>{ "z", "f", "a", "g", "x" };

    println(ust);
    ust.insert("k");
    println(ust);

    ust.erase("a");
    println(ust);
    ust.erase(++ust.begin());
    println(ust);

    std::cout << "Loading Factor: " << ust.load_factor() << std::endl;
    std::cout << "Max Loading Factor: " << ust.max_load_factor() << std::endl;

    std::cout << "Size: " << ust.size() << std::endl;
    std::cout << "# Buckets: " << ust.bucket_count() << std::endl;
    ust.insert("m");
    println(ust);
    std::cout << "Size: " << ust.size() << std::endl;
    std::cout << "# Buckets: " << ust.bucket_count() << std::endl;

    auto bckt = ust.bucket("f");  ///< returns index of bucket
    std::cout << "Bucket Size: " << ust.bucket_size(bckt) << std::endl;

    ust.clear();
    std::cout << "After ust.clear()" << std::endl;
    std::cout << "Size: " << ust.size() << std::endl;
    println(ust);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/G97n97r3G)

[`std::unordered_set` : cppreference](https://en.cppreference.com/w/cpp/container/unordered_set)

#### Section 2.4.2 : Unordered Map

`std::unordered_map` is a hashed version of a regular map but like its hash set counterchapter, instead of ordering keys it uses a hashing functions to create an index into buckets. Search, insertion and erasure all happen in constant time ($O(1)$). Unlike hashed sets, values can be accessed and inserted using key-based indexing.

```cxx
#include <iostream>
#include <unordered_map>
#include <string>

template<typename K, typename V>
auto println(const std::unordered_map<K, V>& umap) -> void
{
    std::cout << "{ ";
    for (auto i { umap.size() }; const auto& [k, v] : umap)
        std::cout << k << ": " << v << (--i ? ", " : "");
    std::cout << " }" << std::endl;
}

auto main() -> int
{
    auto umap = std::unordered_map<std::string, int>{ {"z", 12}, {"f", 2}, {"a", 3}, {"g", 4}, {"x", 5} };

    println(umap);
    umap["h"] = 576;
    println(umap);
    umap.at("f") = 368548;
    println(umap);

    println(umap);
    umap.insert({"k", 56});
    println(umap);

    umap.erase("a");
    println(umap);
    umap.erase(++umap.begin());
    println(umap);

    std::cout << "Loading Factor: " << umap.load_factor() << std::endl;
    std::cout << "Max Loading Factor: " << umap.max_load_factor() << std::endl;

    std::cout << "Size: " << umap.size() << std::endl;
    std::cout << "# Buckets: " << umap.bucket_count() << std::endl;
    umap.insert({"m", 78});
    println(umap);
    std::cout << "Size: " << umap.size() << std::endl;
    std::cout << "# Buckets: " << umap.bucket_count() << std::endl;

    auto bckt = umap.bucket("f");  ///< returns index of bucket
    std::cout << "Bucket Size: " << umap.bucket_size(bckt) << std::endl;

    umap.clear();
    std::cout << "After umap.clear()" << std::endl;
    std::cout << "Size: " << umap.size() << std::endl;
    println(umap);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/qj5bq9fze)

[`std::unordered_map` : cppreference](https://en.cppreference.com/w/cpp/container/unordered_map)

#### Section 2.4.3 : Unordered Multiset & Multimap

Much like how there are sets and maps that can store duplicate keys, there are hashed versions of these data structures called `std::unordered_multiset` and `std::unordered_multimap` respectively. Search, insertion and erasure occur in constant time ($O(n)$). Hashed multimaps cannot be accessed using key-based indexing as it cannot be determined which key to return if duplicates exist.

```cxx
#include <iostream>
#include <unordered_map>
#include <string>

template<typename K, typename V>
auto println(const std::unordered_multimap<K, V>& ummap) -> void
{
    std::cout << "{ ";
    for (auto i { ummap.size() }; const auto& [k, v] : ummap)
        std::cout << k << ": " << v << (--i ? ", " : "");
    std::cout << " }" << std::endl;
}

auto main() -> int
{
    auto ummap = std::unordered_multimap<std::string, int>{ {"z", 1}, {"f", 2}, {"a", 3}, {"g", 4}, {"x", 5} };

    println(ummap);
    ummap.insert({"w", 77});
    println(ummap);
    ummap.insert({"w", 879});
    println(ummap);
    ummap.insert({"w", -23});
    println(ummap);
    ummap.insert({"w", 209538});
    println(ummap);

    std::cout << "Loading Factor: " << ummap.load_factor() << std::endl;
    std::cout << "Max Loading Factor: " << ummap.max_load_factor() << std::endl;

    std::cout << "Size: " << ummap.size() << std::endl;
    std::cout << "# Buckets: " << ummap.bucket_count() << std::endl;
    ummap.insert({"m", 78});
    println(ummap);
    std::cout << "Size: " << ummap.size() << std::endl;
    std::cout << "# Buckets: " << ummap.bucket_count() << std::endl;

    auto bckt = ummap.bucket("w");  ///< returns index of bucket
    std::cout << "Bucket Size: " << ummap.bucket_size(bckt) << std::endl;

    std::cout << "w: { ";
    auto i { ummap.bucket_size(bckt) };
    for (auto it = ummap.begin(bckt); it != ummap.end(bckt); ++it)
        std::cout << it->first << ": " << it->second << (--i ? ", " : "");
    std::cout << " }" << std::endl;

    ummap.erase("a");
    println(ummap);
    ummap.erase(++ummap.begin());
    println(ummap);

    ummap.clear();
    std::cout << "After ummap.clear()" << std::endl;
    std::cout << "Size: " << ummap.size() << std::endl;
    println(ummap);

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/heKfcz6K1)

[`std::unordered_multiset` : cppreference](https://en.cppreference.com/w/cpp/container/unordered_multiset)
[`std::unordered_multimap` : cppreference](https://en.cppreference.com/w/cpp/container/unordered_multimap)

### Section 2.5 : Miscellaneous

#### Section 2.5.1 : Bitset

`std::bitset` allows for efficient storage of individually addressable bits. The size of a bitset is fixed at compile time allowing for bitsets to be evaluated in `constexpr` context. The standard bit manipulation operators are available for bitwise manipulation between bitsets. Bitset also allow for single bit access as well as testing of single or all bits in the bitset. Bitsets also have conversion methods for obtaining the string, and integral representations of the bits. Bitsets can be constructed from string representations of bits or or from binary literal integrals. The bit to the right is the least significant bit ie. the first bit.

```cxx
#include <iostream>
#include <bitset>
#include <string>

template<std::size_t N>
auto println(const std::bitset<N>& b) -> void
{ std::cout << "0b" << b << std::endl; }

auto main() -> int
{
    auto b = std::bitset<6>(0b011010uLL);

    println(b);
    b[2] = true;
    println(b);
    b.set(4) = false;

    b.flip(0);
    println(b);
    b.flip();
    println(b);
    b.reset();
    println(b);

    std::cout << std::boolalpha;
    std::cout << (b.test(5) == false) << std::endl;
    std::cout << b.any() << std::endl;
    std::cout << b.all() << std::endl;
    std::cout << b.none() << std::endl;
    std::cout << std::noboolalpha;

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/1qnYTWxMb)

[`std::bitset` : cppreference](https://en.cppreference.com/w/cpp/utility/bitset)

#### Section 2.5.2 : Any

`std::any` is a unique data structure that can hold any _Copy-Constructable_ type. It can also be changed to any new type simply through assignment. You can introspect the type contained as well as destroy the contained object. The only way to access the contained value is through an `std::any_cast<>` which will yield the value which is cast to the template type of the any cast. Any also comes with a factory function for creating a any object.

```cxx
#include <iostream>
#include <any>

template<typename T>
auto println(const std::any& a) -> void
{ std::cout << std::any_cast<T>(a) << std::endl; }

auto main() -> int
{
    auto a = std::make_any<int>(6);

    println<int>(a);
    a.emplace<double>(6.797898);
    println<double>(a);    

    std::cout << a.type().name() << std::endl; 

    std::cout << std::boolalpha;
    std::cout << a.has_value() << std::endl;
    a.reset();
    std::cout << a.has_value() << std::endl;
    std::cout << std::noboolalpha;

    return 0;
}
```

[Exmaple](https://www.godbolt.org/z/n57nYonqs)

[`std::any` : cppreference](https://en.cppreference.com/w/cpp/utility/any)
