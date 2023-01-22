# Parallel Algorithms

## Contents

- [Parallel Algorithms](#parallel-algorithms)
  - [Contents](#contents)
  - [Task 1](#task-1)
    - [Task 1.1 : Execution Policies](#task-11--execution-policies)
    - [Task 1.2 : Alternative Algorithms](#task-12--alternative-algorithms)
      - [Task 1.2.1 : Reduce](#task-121--reduce)
      - [Task 1.2.2 : Transform Reduce](#task-122--transform-reduce)
      - [Task 1.2.3 : Exclusive Scan](#task-123--exclusive-scan)
      - [Task 1.2.4 : Inclusive Scan](#task-124--inclusive-scan)
      - [Task 1.2.5 : Transform Exclusive Scan](#task-125--transform-exclusive-scan)
      - [Task 1.2.6 : Transform Inclusive Scan](#task-126--transform-inclusive-scan)
  - [Links](#links)

## Task 1

### Task 1.1 : Execution Policies

The most basic parallelism comes from the algorithms library. Since C++17 almost all of the algorithms (iterator-based not range-based) in the standard library feature an overload that allows for the algorithm to potentially perform in parallel. These overloads accepts as their first arguments an execution policy. This is an object that represent the level of freedom an algorithms implementation has to try and parallelize its operation. Execution policies are found in the `<execution>` header under the `std::execution` namespace. Execution policies are suggestions, they indicate that a algorithm may be able to be parallelized. How the parallelism is achieve is up to the implementation and requires a parallelism backend library that the implementations will use. The most common is Intel's Thread Building Blocks (TBB) library. Using parallel overloads does require some due-diligence from the programmer to not create deadlocks or data races. The parallel algorithms will not automatically stop these from happening.

|       Execution Policy      |                                                                                                                                                           Description                                                                                                                                                           |
|:---------------------------:|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
|    `std::execution::seq`    |                                                                                  Forbids an algorithm from being parallelized. Invocations of element access functions within the algorithm are indeterminately sequenced in the calling thread                                                                                 |
|    `std::execution::par`    | Specifies that an algorithm can be parallelized. Invocations of element access functions within the algorithm are permitted to execute in the working thread or in a thread implicitly created by the underlying parallel library. Invocations executing in the same thread are indeterminately sequenced in the calling thread |
|   `std::execution::unseq`   |                                                                                                 Specifies that an algorithm can be vectorized such that a single thread using instructions that operate on multiple data items.                                                                                                 |
| `std::execution::par_unseq` |                 Specifies that an algorithm can be parallelized, vectorized or migrated across threads. Invocations of element access functions within the algorithm are permitted to execute in unordered fashion in unspecified threads and can be un-sequenced with respect to one another within each thread.                |

[Execution Policies : cppreference](https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t)

### Task 1.2 : Alternative Algorithms

There are a few algorithms in C++ that did not get parallel overloads. Namely a few of the numerical reductions. This is because reduction algorithms typically use binary operators in order to combine elements. The issue with this is not all binary operators are commutative or associative. This can cause problems when making an algorithm work in parallel because the order of operations can affect the result of the reduction. C++ regular reduction algorithms apply their operations in-order meaning that the commutative and associative properties of the binary operator do not matter. For parallel algorithms, commutativity and associativity must be assumed of the binary operator so that operations can be out-of-order.

#### Task 1.2.1 : Reduce

`std::reduce` is the parallel form of `std::accumulate`. It performs a regular left-fold and can take an optional initial value.

```cxx
#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template <typename time_t = std::chrono::microseconds>
struct measure
{
    template <typename F, typename... Args>
    static auto execution(F func, Args&&... args) 
        -> std::pair<typename time_t::rep, std::invoke_result_t<F, Args...>>
    {
        auto start = std::chrono::system_clock::now();
        auto result = std::invoke(func, std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<time_t>(std::chrono::system_clock::now() - start);
        return std::pair<typename time_t::rep, std::invoke_result_t<F, Args...>>{ duration.count(), result };
    }
};

auto main() -> int
{
    auto dv = std::vector<double>(100'000'007, 0.1);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;
    std::cout << "|    Algorithm    | Exec Policy | Binary-Op |  Type  |    Time    |     Result     |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::accumulate |   Serial    |     +     | double | ";
    auto [acc_time, acc_result] = measure<>::execution([](const auto& v){ return std::accumulate(v.begin(), v.end(), 0.0); }, dv);
    std::cout << std::setw(7) << acc_time << " us |  " << acc_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "|   std::reduce   | Sequencial  |     +     | double | ";
    auto [seq_time, seq_result] = measure<>::execution([](const auto& v){ return std::reduce(std::execution::seq, v.begin(), v.end(), 0.0); }, dv);
    std::cout << std::setw(7) << seq_time << " us |  " << seq_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "|   std::reduce   |  Parallel   |     +     | double | ";
    auto [par_time, par_result] = measure<>::execution([](const auto& v){ return std::reduce(std::execution::par, v.begin(), v.end(), 0.0); }, dv);
    std::cout << std::setw(7) << par_time << " us |  " << par_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "|   std::reduce   | Unsequenced |     +     | double | ";
    auto [unseq_time, unseq_result] = measure<>::execution([](const auto& v){ return std::reduce(std::execution::unseq, v.begin(), v.end(), 0.0); }, dv);
    std::cout << std::setw(7) << unseq_time << " us |  " << unseq_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "|   std::reduce   |  Par-Unseq  |     +     | double | ";
    auto [par_unseq_time, par_unseq_result] = measure<>::execution([](const auto& v){ return std::reduce(std::execution::par_unseq, v.begin(), v.end(), 0.0); }, dv);
    std::cout << std::setw(7) << par_unseq_time << " us |  " << par_unseq_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;
    
    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/reduce
+-----------------+-------------+-----------+--------+------------+----------------+
|    Algorithm    | Exec Policy | Binary-Op |  Type  |    Time    |     Result     |
+-----------------+-------------+-----------+--------+------------+----------------+
| std::accumulate |   Serial    |     +     | double | 151,861 us |  10,000,000.7  |
+-----------------+-------------+-----------+--------+------------+----------------+
|   std::reduce   | Sequencial  |     +     | double |  76,011 us |  10,000,000.7  |
+-----------------+-------------+-----------+--------+------------+----------------+
|   std::reduce   |  Parallel   |     +     | double |  21,098 us |  10,000,000.7  |
+-----------------+-------------+-----------+--------+------------+----------------+
|   std::reduce   | Unsequenced |     +     | double | 135,906 us |  10,000,000.7  |
+-----------------+-------------+-----------+--------+------------+----------------+
|   std::reduce   |  Par-Unseq  |     +     | double |  23,752 us |  10,000,000.7  |
+-----------------+-------------+-----------+--------+------------+----------------+
```

[Example](/content/part7/examples/par-algs/src/reduce.main.cxx)

[`std::reduce` : cppreference](https://en.cppreference.com/w/cpp/algorithm/reduce)

#### Task 1.2.2 : Transform Reduce

`std::transform_reduce` is akin to `std::inner_product` performing the same default unary transformation (`*`) and reduction (`+`). Takes an initial value that is used as the base accumulator.

```cxx
#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template <typename time_t = std::chrono::microseconds>
struct measure
{
    template <typename F, typename... Args>
    static auto execution(F func, Args&&... args) 
        -> std::pair<typename time_t::rep, std::invoke_result_t<F, Args...>>
    {
        auto start = std::chrono::system_clock::now();
        auto result = std::invoke(func, std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<time_t>(std::chrono::system_clock::now() - start);
        return std::pair<typename time_t::rep, std::invoke_result_t<F, Args...>>{ duration.count(), result };
    }
};

auto main() -> int
{
    auto v1 = std::vector<double>(100'000'007, 0.145);
    auto v2 = std::vector<double>(100'000'007, 0.524);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(4);
    
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;
    std::cout << "|       Algorithm       | Exec Policy | Binary-Ops |  Type  |    Time    |     Result     |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "|  std::inner_product   |   Serial    | (*) -> (+) | double | ";
    auto [in_prod_time, in_prod_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << in_prod_time << " us | " << in_prod_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::transform_reduce | Sequencial  | (*) -> (+) | double | ";
    auto [seq_time, seq_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::transform_reduce(std::execution::seq, v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << seq_time << " us | " << seq_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::transform_reduce |  Parallel   | (*) -> (+) | double | ";
    auto [par_time, par_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::transform_reduce(std::execution::par, v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << par_time << " us | " << par_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::transform_reduce | Unsequenced | (*) -> (+) | double | ";
    auto [unseq_time, unseq_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::transform_reduce(std::execution::unseq, v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << unseq_time << " us | " << unseq_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::transform_reduce |  Par-Unseq  | (*) -> (+) | double | ";
    auto [par_unseq_time, par_unseq_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::transform_reduce(std::execution::par_unseq, v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << par_unseq_time << " us | " << par_unseq_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

./build/transform_reduce
+-----------------------+-------------+------------+--------+------------+----------------+
|       Algorithm       | Exec Policy | Binary-Ops |  Type  |    Time    |     Result     |
+-----------------------+-------------+------------+--------+------------+----------------+
|  std::inner_product   |   Serial    | (*) -> (+) | double | 144,255 us | 7,598,000.5455 |
+-----------------------+-------------+------------+--------+------------+----------------+
| std::transform_reduce | Sequencial  | (*) -> (+) | double | 119,467 us | 7,598,000.5455 |
+-----------------------+-------------+------------+--------+------------+----------------+
| std::transform_reduce |  Parallel   | (*) -> (+) | double |  53,172 us | 7,598,000.5318 |
+-----------------------+-------------+------------+--------+------------+----------------+
| std::transform_reduce | Unsequenced | (*) -> (+) | double | 131,677 us | 7,598,000.5455 |
+-----------------------+-------------+------------+--------+------------+----------------+
| std::transform_reduce |  Par-Unseq  | (*) -> (+) | double |  51,095 us | 7,598,000.5319 |
+-----------------------+-------------+------------+--------+------------+----------------+
```

[Example](/content/part7/examples/par-algs/src/transform_reduce.main.cxx)

[`std::transform_reduce` : cppreference](https://en.cppreference.com/w/cpp/algorithm/transform_reduce)

#### Task 1.2.3 : Exclusive Scan

`std::exclusive_scan` is akin to `std::partial_sum` except is takes in an initial value and excludes the $ith$ input element from the $ith$ sum (reduction).

```cxx
#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template <typename time_t = std::chrono::microseconds>
struct measure
{
    template <typename F, typename... Args>
    static auto execution(F func, Args&&... args) 
        -> typename time_t::rep
    {
        auto start = std::chrono::system_clock::now();
        std::invoke(func, std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<time_t>(std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

template<typename T>
auto operator<< 
(std::ostream& os, const std::vector<T>& v) -> std::ostream&
{
    os << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        if (--i > (v.size() - 3))
            os << e << ", ";

    auto last = v.end() - 3;
    os << "..., " << *++last << ", ";
    os << *++last << " ]";
    return os;
}

auto main() -> int
{
    auto v = std::vector<double>(100'000'007, 0.1);
    auto r = std::vector<double>(100'000'007, 0.0);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;
    std::cout << "|      Algorithm      | Exec Policy | Binary-Op |  Type  |    Time    |                    Result                     |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "|  std::partial_sum   |   Serial    |     +     | double | ";
    auto scan_time = measure<>::execution([](const auto& v, auto& r){ std::partial_sum(v.begin(), v.end(), r.begin()); }, v, r);
    std::cout << std::setw(7) << scan_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::exclusive_scan | Sequencial  |     +     | double | ";
    auto seq_time = measure<>::execution([](const auto& v, auto& r){ std::exclusive_scan(std::execution::seq, v.begin(), v.end(), r.begin(), 0.0); }, v, r);
    std::cout << std::setw(7) << seq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::exclusive_scan |  Parallel   |     +     | double | ";
    auto par_time = measure<>::execution([](const auto& v, auto& r){ std::exclusive_scan(std::execution::par, v.begin(), v.end(), r.begin(), 0.0); }, v, r);
    std::cout << std::setw(7) << par_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::exclusive_scan | Unsequenced |     +     | double | ";
    auto unseq_time = measure<>::execution([](const auto& v, auto& r){ std::exclusive_scan(std::execution::unseq, v.begin(), v.end(), r.begin(), 0.0); }, v, r);
    std::cout << std::setw(7) << unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::exclusive_scan |  Par-Unseq  |     +     | double | ";
    auto par_unseq_time = measure<>::execution([](const auto& v, auto& r){ std::exclusive_scan(std::execution::par_unseq, v.begin(), v.end(), r.begin(), 0.0); }, v, r);
    std::cout << std::setw(7) << par_unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;
    
    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

./build/exclusive_scan
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
|      Algorithm      | Exec Policy | Binary-Op |  Type  |    Time    |                    Result                     |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
|  std::partial_sum   |   Serial    |     +     | double | 119,096 us | [ 0.1, 0.2, ..., 10,000,000.6, 10,000,000.7 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
| std::exclusive_scan | Sequencial  |     +     | double | 143,338 us | [ 0.0, 0.1, ..., 10,000,000.5, 10,000,000.6 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
| std::exclusive_scan |  Parallel   |     +     | double | 146,967 us | [ 0.0, 0.1, ..., 10,000,000.5, 10,000,000.6 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
| std::exclusive_scan | Unsequenced |     +     | double | 140,900 us | [ 0.0, 0.1, ..., 10,000,000.5, 10,000,000.6 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
| std::exclusive_scan |  Par-Unseq  |     +     | double | 145,098 us | [ 0.0, 0.1, ..., 10,000,000.5, 10,000,000.6 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
```

[Example](/content/part7/examples/par-algs/src/exclusive_scan.main.cxx)

[`std::exclusive_scan` : cppreference](https://en.cppreference.com/w/cpp/algorithm/exclusive_scan)

#### Task 1.2.4 : Inclusive Scan

`std::inclusive_scan` is identical to `std::partial_sum`. It does not take an initial value and unlike `std::exclusive_scan` includes the $ith$ element from the input range in the $ith$ reduction.

```cxx
#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template <typename time_t = std::chrono::microseconds>
struct measure
{
    template <typename F, typename... Args>
    static auto execution(F func, Args&&... args) 
        -> typename time_t::rep
    {
        auto start = std::chrono::system_clock::now();
        std::invoke(func, std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<time_t>(std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

template<typename T>
auto operator<< 
(std::ostream& os, const std::vector<T>& v) -> std::ostream&
{
    os << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        if (--i > (v.size() - 3))
            os << e << ", ";

    auto last = v.end() - 3;
    os << "..., " << *++last << ", ";
    os << *++last << " ]";
    return os;
}

auto main() -> int
{
    auto v = std::vector<double>(100'000'007, 0.1);
    auto r = std::vector<double>(100'000'007);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;
    std::cout << "|      Algorithm      | Exec Policy | Binary-Op |  Type  |    Time    |                    Result                     |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "|  std::partial_sum   |   Serial    |     +     | double | ";
    auto scan_time = measure<>::execution([](const auto& v, auto& r){ std::partial_sum(v.begin(), v.end(), r.begin()); }, v, r);
    std::cout << std::setw(7) << scan_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::inclusive_scan | Sequencial  |     +     | double | ";
    auto seq_time = measure<>::execution([](const auto& v, auto& r){ std::inclusive_scan(std::execution::seq, v.begin(), v.end(), r.begin()); }, v, r);
    std::cout << std::setw(7) << seq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::inclusive_scan |  Parallel   |     +     | double | ";
    auto par_time = measure<>::execution([](const auto& v, auto& r){ std::inclusive_scan(std::execution::par, v.begin(), v.end(), r.begin()); }, v, r);
    std::cout << std::setw(7) << par_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::inclusive_scan | Unsequenced |     +     | double | ";
    auto unseq_time = measure<>::execution([](const auto& v, auto& r){ std::inclusive_scan(std::execution::unseq, v.begin(), v.end(), r.begin()); }, v, r);
    std::cout << std::setw(7) << unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::inclusive_scan |  Par-Unseq  |     +     | double | ";
    auto par_unseq_time = measure<>::execution([](const auto& v, auto& r){ std::inclusive_scan(std::execution::par_unseq, v.begin(), v.end(), r.begin()); }, v, r);
    std::cout << std::setw(7) << par_unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;
    
    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

./build/inclusive_scan
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
|      Algorithm      | Exec Policy | Binary-Op |  Type  |    Time    |                    Result                     |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
|  std::partial_sum   |   Serial    |     +     | double | 121,801 us | [ 0.1, 0.2, ..., 10,000,000.6, 10,000,000.7 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
| std::inclusive_scan | Sequencial  |     +     | double | 120,705 us | [ 0.1, 0.2, ..., 10,000,000.6, 10,000,000.7 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
| std::inclusive_scan |  Parallel   |     +     | double | 150,662 us | [ 0.1, 0.2, ..., 10,000,000.6, 10,000,000.7 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
| std::inclusive_scan | Unsequenced |     +     | double | 120,440 us | [ 0.1, 0.2, ..., 10,000,000.6, 10,000,000.7 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
| std::inclusive_scan |  Par-Unseq  |     +     | double | 145,441 us | [ 0.1, 0.2, ..., 10,000,000.6, 10,000,000.7 ] |
+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+
```

[Example](/content/part7/examples/par-algs/src/inclusive_scan.main.cxx)

[`std::inclusive_scan` : cppreference](https://en.cppreference.com/w/cpp/algorithm/inclusive_scan)

#### Task 1.2.5 : Transform Exclusive Scan

`std::transform_exclusive_scan` will perform a unary transformation and then performs a left exclusive scan on a range.

```cxx
#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template <typename time_t = std::chrono::microseconds>
struct measure
{
    template <typename F, typename... Args>
    static auto execution(F func, Args&&... args) 
        -> typename time_t::rep
    {
        auto start = std::chrono::system_clock::now();
        std::invoke(func, std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<time_t>(std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

template<typename T>
auto operator<< 
(std::ostream& os, const std::vector<T>& v) -> std::ostream&
{
    os << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        if (--i > (v.size() - 3))
            os << e << ", ";

    auto last = v.end() - 3;
    os << "..., " << *++last << ", ";
    os << *++last << " ]";
    return os;
}

auto main() -> int
{
    auto v = std::vector<double>(100'000'007, 0.1);
    auto r = std::vector<double>(100'000'007, 0.0);
    auto times2 = [](const auto& x){ return x * 2; };
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "+-------------------------------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;
    std::cout << "|           Algorithm           | Exec Policy | Operations  |  Type  |    Time    |                    Result                     |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::transform_inclusive_scan | Sequencial  | (*2) -> (+) | double | ";
    auto seq_time = measure<>::execution([&](const auto& v, auto& r){  std::transform_inclusive_scan(std::execution::seq, v.begin(), v.end(), r.begin(), std::plus<>{}, times2, 0.0); }, v, r);
    std::cout << std::setw(7) << seq_time << " us | " << r << " |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::transform_inclusive_scan |  Parallel   | (*2) -> (+) | double | ";
    auto par_time = measure<>::execution([&](const auto& v, auto& r){  std::transform_inclusive_scan(std::execution::par, v.begin(), v.end(), r.begin(), std::plus<>{}, times2, 0.0); }, v, r);
    std::cout << std::setw(7) << par_time << " us | " << r << " |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::transform_inclusive_scan | Unsequenced | (*2) -> (+) | double | ";
    auto unseq_time = measure<>::execution([&](const auto& v, auto& r){  std::transform_inclusive_scan(std::execution::unseq, v.begin(), v.end(), r.begin(), std::plus<>{}, times2, 0.0); }, v, r);
    std::cout << std::setw(7) << unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::transform_inclusive_scan |  Par-Unseq  | (*2) -> (+) | double | ";
    auto par_unseq_time = measure<>::execution([&](const auto& v, auto& r){  std::transform_inclusive_scan(std::execution::par_unseq, v.begin(), v.end(), r.begin(), std::plus<>{}, times2, 0.0); }, v, r);
    std::cout << std::setw(7) << par_unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;
    
    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

./build/transform_exclusive_scan
+-------------------------------+-------------+-------------+--------+------------+-----------------------------------------------+
|           Algorithm           | Exec Policy | Operations  |  Type  |    Time    |                    Result                     |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
| std::transform_exclusive_scan | Sequencial  | (*2) -> (+) | double | 125,675 us | [ 0.0, 0.2, ..., 20,000,001.0, 20,000,001.2 ] |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
| std::transform_exclusive_scan |  Parallel   | (*2) -> (+) | double | 150,095 us | [ 0.0, 0.2, ..., 20,000,001.0, 20,000,001.2 ] |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
| std::transform_exclusive_scan | Unsequenced | (*2) -> (+) | double | 167,813 us | [ 0.0, 0.2, ..., 20,000,001.0, 20,000,001.2 ] |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
| std::transform_exclusive_scan |  Par-Unseq  | (*2) -> (+) | double | 146,167 us | [ 0.0, 0.2, ..., 20,000,001.0, 20,000,001.2 ] |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
```

[Example](/content/part7/examples/par-algs/src/transform_exclusive_scan.main.cxx)

[`std::transform_exclusive_scan` : cppreference](https://en.cppreference.com/w/cpp/algorithm/transform_exclusive_scan)

#### Task 1.2.6 : Transform Inclusive Scan

`std::transform_inclusive_scan` will perform a unary transformation and then performs a left inclusive scan on a range.

```cxx
#include <algorithm>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template <typename time_t = std::chrono::microseconds>
struct measure
{
    template <typename F, typename... Args>
    static auto execution(F func, Args&&... args) 
        -> typename time_t::rep
    {
        auto start = std::chrono::system_clock::now();
        std::invoke(func, std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<time_t>(std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

template<typename T>
auto operator<< 
(std::ostream& os, const std::vector<T>& v) -> std::ostream&
{
    os << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        if (--i > (v.size() - 3))
            os << e << ", ";

    auto last = v.end() - 3;
    os << "..., " << *++last << ", ";
    os << *++last << " ]";
    return os;
}

auto main() -> int
{
    auto v = std::vector<double>(100'000'007, 0.1);
    auto r = std::vector<double>(100'000'007, 0.0);
    auto times2 = [](const auto& x){ return x * 2; };
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "+-------------------------------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;
    std::cout << "|           Algorithm           | Exec Policy | Operations  |  Type  |    Time    |                    Result                     |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::transform_exclusive_scan | Sequencial  | (*2) -> (+) | double | ";
    auto seq_time = measure<>::execution([&](const auto& v, auto& r){  std::transform_exclusive_scan(std::execution::seq, v.begin(), v.end(), r.begin(), 0.0, std::plus<>{}, times2); }, v, r);
    std::cout << std::setw(7) << seq_time << " us | " << r << " |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::transform_exclusive_scan |  Parallel   | (*2) -> (+) | double | ";
    auto par_time = measure<>::execution([&](const auto& v, auto& r){  std::transform_exclusive_scan(std::execution::par, v.begin(), v.end(), r.begin(), 0.0, std::plus<>{}, times2); }, v, r);
    std::cout << std::setw(7) << par_time << " us | " << r << " |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::transform_exclusive_scan | Unsequenced | (*2) -> (+) | double | ";
    auto unseq_time = measure<>::execution([&](const auto& v, auto& r){  std::transform_exclusive_scan(std::execution::unseq, v.begin(), v.end(), r.begin(), 0.0, std::plus<>{}, times2); }, v, r);
    std::cout << std::setw(7) << unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::transform_exclusive_scan |  Par-Unseq  | (*2) -> (+) | double | ";
    auto par_unseq_time = measure<>::execution([&](const auto& v, auto& r){  std::transform_exclusive_scan(std::execution::par_unseq, v.begin(), v.end(), r.begin(), 0.0, std::plus<>{}, times2); }, v, r);
    std::cout << std::setw(7) << par_unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+" << std::endl;
    
    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

./build/transform_inclusive_scan
+-------------------------------+-------------+-------------+--------+------------+-----------------------------------------------+
|           Algorithm           | Exec Policy | Operations  |  Type  |    Time    |                    Result                     |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
| std::transform_inclusive_scan | Sequencial  | (*2) -> (+) | double | 120,220 us | [ 0.2, 0.4, ..., 20,000,001.2, 20,000,001.4 ] |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
| std::transform_inclusive_scan |  Parallel   | (*2) -> (+) | double | 148,472 us | [ 0.2, 0.4, ..., 20,000,001.2, 20,000,001.4 ] |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
| std::transform_inclusive_scan | Unsequenced | (*2) -> (+) | double | 135,489 us | [ 0.2, 0.4, ..., 20,000,001.2, 20,000,001.4 ] |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
| std::transform_inclusive_scan |  Par-Unseq  | (*2) -> (+) | double | 150,443 us | [ 0.2, 0.4, ..., 20,000,001.2, 20,000,001.4 ] |
+--------------------+----------+-------------+-------------+--------+------------+-----------------------------------------------+
```

[Example](/content/part7/examples/par-algs/src/transform_inclusive_scan.main.cxx)

[`std::transform_inclusive_scan` : cppreference](https://en.cppreference.com/w/cpp/algorithm/transform_inclusive_scan)

## Links

- [Previous Page : Part 7](/content/part7/README.md)
- [Next Page : Atomics](/content/part7/tasks/atomics.md)
- [Content](/content/README.md)
- [HOME](/README.md)
