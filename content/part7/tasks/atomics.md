# Atomics

## Contents

- [Atomics](#atomics)
  - [Contents](#contents)
  - [Task 2](#task-2)
    - [Task 2.1 : Data Races \& Shared Resources](#task-21--data-races--shared-resources)
    - [Task 2.2 : Atomic Types](#task-22--atomic-types)
  - [Links](#links)

## Task 2

### Task 2.1 : Data Races & Shared Resources

In any program, data is shared across multiple parts of the system. This is largely not a problem because there is only a single thread accessing the data meaning all operations occur sequentially. This guarantees that data will only every be read from or written to but not both at the same time. However, when a program starts to introduce concurrency data now may be shared between different execution processes. This means that data can be read from or written at the same time causing a _Race Condition_. _Race Conditions_ are UB in almost all programming languages as there is no way for the compiler or interpreter to tell which operation will happen first. There are many techniques to prevent and outright disallow race conditions from occur while still allowing for data to exist in a shared state. The first of which we will look at is `std::atomic`.

### Task 2.2 : Atomic Types

`std::atomic` is a template class type that represents an _atomic-object_. Reading from and writing to an _atomic-object_ at the same time is considered well defined. This is because operations are performed atomically meaning that no race conditions can occur as the memory ordering must be specified. `std::atomic` can accept template types that are integrals, floating-points, pointers, `std::shared_ptr` or `std::weak_ptr`. It can also accept custom types that are trivially copyable and copy and move constructible/assignable. `std::atomic` also can be used to synchronize execution by blocking and notifying different executions processes. `std::atomic` itself cannot be copied or move. There is also `std::atomic_ref` which creates a reference to existing data for which all operations are atomic. The referred object's lifetime must exceed that of the atomic reference the underlying object can only be access through atomic references for the lifetime of all atomic references. `std::atomic_ref` can by copied.

```cxx
#include <algorithm>
#include <atomic>
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
    auto count = std::atomic<int>{ 0 };
    auto v = std::vector<double>(100'000'007, 0.1);

    auto alg = [&count](const auto& v)
    { 
        return std::reduce(
            std::execution::par_unseq,
            v.begin(),
            v.end(),
            0.0,
            [&count](const auto& x, const auto& y) {
                count.fetch_add(1, std::memory_order_relaxed);
                return x + y;
            }
        ); 
    };

    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(4);
    
    auto [time, result] = measure<>::execution(alg, v);

    std::cout << "std::reduce (parallel-unsequenced execution):\n"
              << "Result: " << result << "\n"
              << "Time: " << time << " us\n"
              << "Atomic Count: " << count.load() << std::endl;
    
    return 0;
}
```

```sh
bpt build -t build.yaml -o build

# ...

./build/atomic
std::reduce (parallel-unsequenced execution):
Result: 10,000,000.7000
Time: 1,699,214 us
Atomic Count: 100,000,007
```

[Example](/content/part7/examples/atomic/src/atomic.main.cxx)

- [`std::atomic` : cppreference](https://en.cppreference.com/w/cpp/atomic/atomic)
- [`std::atomic_ref` : cppreference](https://en.cppreference.com/w/cpp/atomic/atomic_ref)

## Links

- [Previous Page : Parallel Algorithms](/content/part7/tasks/parallel-alg.md)
- [Next Page : Threads](/content/part7/tasks/threads.md)
- [Content](/content/README.md)
- [HOME](/README.md)
