# Async

## Contents

- [Async](#async)
  - [Contents](#contents)
  - [Task 5](#task-5)
    - [Task 5.1 : Futures and Promises](#task-51--futures-and-promises)
    - [Task 5.2 : Async](#task-52--async)
    - [Task 5.3 : Packaged Tasks](#task-53--packaged-tasks)
  - [Links](#links)

## Task 5

### Task 5.1 : Futures and Promises

A promise; represented by the class `std::promise`, is a object that stores a value or exception that is retrieved by a `std::future` object. Semantically, this means that a; generally asynchronous function has promised a value to the caller of the asynchronous function but however, does not yet have the value. The future of a promised value is obtained directly from the `std::promise` object. The caller of the promised value can query, wait for or extract the value from the corresponding `std::future` object however, these may block if the result is not yet ready. The timeout methods will return a `std::future_status` object which is an enum indicating if the wait timed out, if the future is deferred (_lazy_ loading) or ready. The value of a promise is communicated via a shared memory state between the `std::future` and `std::promise` objects. This shared state cannot be shared between different threads meaning that only one `std::future` can be used to obtain the result of a promised value. To enforce this `std::future` is move-only. A shared future can be obtained by called `std::future::share` to create a `std::shared_future` which claims ownership of the shared state such that the future can be copied between different threads. Promises and futures are found in the `<future>` header.

```cxx
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

using namespace std::literals;

auto job = [](std::promise<int>&& p, auto a, auto b)
{
    std::this_thread::sleep_for(3s);
    auto r = a + b;
    p.set_value(r);  
    std::this_thread::sleep_for(3s);
};


auto main() -> int
{
    auto p = std::promise<int>{};
    auto f = p.get_future();

    auto th = std::thread(job, std::move(p), 4, 5);

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Waiting for job...\n";
    auto r          = f.get();
    auto finish     = std::chrono::high_resolution_clock::now();
    auto duration   = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    std::cout << "Result: " << r << std::endl;
    std::cout << "Took: " << duration << " ms" << std::endl;

    th.join();

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/futures
Waiting for job...
Result: 9
Took: 3000 ms
```

[Example](/content/part7/examples/async/src/futures.main.cxx)

- [`std::future` : cppreference](https://en.cppreference.com/w/cpp/thread/future)
- [`std::shared_future` : cppreference](https://en.cppreference.com/w/cpp/thread/shared_future)
- [`std::future` : cppreference](https://en.cppreference.com/w/cpp/thread/shared_future)
- [`std::promise` : cppreference](https://en.cppreference.com/w/cpp/thread/promise)

### Task 5.2 : Async

Another way to create asynchronous functions without having to deal with threads directly is to use `std::async`. This function will create an asynchronous task that will run according to a launch policy. The standard only defines two policies, this being `std::launch::async`; which will run a function a separate thread, or `std::launch::deferred` which will run the function lazily on the calling thread the first time the value is requested. `std::async` returns a `std::future` object that is used to query, wait for or extract the result of the asynchronous function. `std::async` is found in the `<future>` header.

```cxx
#include <algorithm>
#include <chrono>
#include <concepts>
#include <execution>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
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

template<std::random_access_iterator I, std::sentinel_for<I> S, std::movable A>
auto parallel_sum(I first, S last, A init) -> A
{
    auto middle = first + ((last - first) / 2);
    
    /// Launch async sum on last half of the values 
    auto future = std::async(std::launch::async, parallel_sum<I, S, A>, middle, last, A{});
    
    /// Sum first half of the range locally.
    auto result = parallel_sum(first, middle, init);

    /// Obtain the future and sum with the result
    return result + future.get();
}

auto main() -> int
{
    auto v1 = std::vector<double>(999, 0.1);
    auto v2 = std::vector<double>(100'000'007, 0.1);

    std::cout << std::fixed << std::setprecision(5);

    auto [acc_time_v1, acc_result_v1] = measure<>::execution([](const auto& rng){ return std::accumulate(rng.begin(), rng.end(), 0.0); }, v1);
    std::cout << "std::accumulate : [v1 - 999 elements]\n";
    std::cout << "Time: " << acc_time_v1 << " us\n";
    std::cout << "Result: " << acc_result_v1 << std::endl;

    auto [reduce_time_v1, reduce_result_v1] = measure<>::execution([](const auto& rng){ return std::reduce(std::execution::par, rng.begin(), rng.end(), 0.0); }, v1);
    std::cout << "std::reduce(std::execution::par) : [v1 - 999 elements]\n";
    std::cout << "Time: " << reduce_time_v1 << " us\n";
    std::cout << "Result: " << reduce_result_v1 << std::endl;

    auto [par_time_v1, par_result_v1] = measure<>::execution([](const auto& rng){ return std::accumulate(rng.begin(), rng.end(), 0.0); }, v1);
    std::cout << "parallel_sum : [v1 - 999 elements]\n";
    std::cout << "Time: " << par_time_v1 << " us\n";
    std::cout << "Result: " << par_result_v1 << std::endl;

    std::cout << "------------------------------------------------------\n";

    auto [acc_time_v2, acc_result_v2] = measure<>::execution([](const auto& rng){ return std::accumulate(rng.begin(), rng.end(), 0.0); }, v2);
    std::cout << "std::accumulate : [v2 - 100'000'007 elements]\n";
    std::cout << "Time: " << acc_time_v2 << " us\n";
    std::cout << "Result: " << acc_result_v2 << std::endl;

    auto [reduce_time_v2, reduce_result_v2] = measure<>::execution([](const auto& rng){ return std::reduce(std::execution::par, rng.begin(), rng.end(), 0.0); }, v2);
    std::cout << "std::reduce(std::execution::par) : [v2 - 100'000'007 elements]\n";
    std::cout << "Time: " << reduce_time_v2 << " us\n";
    std::cout << "Result: " << reduce_result_v2 << std::endl;

    auto [par_time_v2, par_result_v2] = measure<>::execution([](const auto& rng){ return std::accumulate(rng.begin(), rng.end(), 0.0); }, v2);
    std::cout << "parallel_sum : [v2 - 100'000'007 elements]\n";
    std::cout << "Time: " << par_time_v2 << " us\n";
    std::cout << "Result: " << par_result_v2 << std::endl;

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/async
std::accumulate : [v1 - 999 elements]
Time: 2 us
Result: 99.90000
std::reduce(std::execution::par) : [v1 - 999 elements]
Time: 750 us
Result: 99.90000
parallel_sum : [v1 - 999 elements]
Time: 2 us
Result: 99.90000
------------------------------------------------------
std::accumulate : [v2 - 100'000'007 elements]
Time: 178779 us
Result: 10000000.68113
std::reduce(std::execution::par) : [v2 - 100'000'007 elements]
Time: 19993 us
Result: 10000000.70009
parallel_sum : [v2 - 100'000'007 elements]
Time: 153180 us
Result: 10000000.68113
```

[Example](/content/part7/examples/async/src/async.main.cxx)

- [`std::async` : cppreference](https://en.cppreference.com/w/cpp/thread/async)
- [`std::launch` : cppreference](https://en.cppreference.com/w/cpp/thread/launch)

### Task 5.3 : Packaged Tasks

The final way to create a future value is the use of `std::packaged_task`. This wraps a callable such that its result type is held in a shared state that can be accesses by a `std::future` object created from the task. `std::packaged_task` objects can be moved to `std::thread` and `std::jthread` objects so that the return value of a task can be acquired from a thread (which usually discards it). `std::packaged_task` is move-only and is found in the `<future>` header.

```cxx
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

using namespace std::literals;

auto job = [](auto a, auto b)
{
    std::this_thread::sleep_for(150ms);
    auto r = a + b;
    std::this_thread::sleep_for(150ms);
    return r;
};

auto main() -> int
{
    auto pkg    = std::packaged_task<int(int, int)>{ job };
    auto f      = pkg.get_future();

    auto th = std::thread(std::move(pkg), 4, 5);

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Waiting for job...\n";
    auto r          = f.get();
    auto finish     = std::chrono::high_resolution_clock::now();
    auto duration   = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    std::cout << "Result: " << r << std::endl;
    std::cout << "Took: " << duration << " ms" << std::endl;

    th.join();

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/packaged_task
Waiting for job...
Result: 9
Took: 300 ms
```

[Example](/content/part7/examples/async/src/packaged_task.main.cxx)

[`std::packaged_task` : cppreference](https://en.cppreference.com/w/cpp/thread/packaged_task)

## Links

- [Previous Page : Mutexes & Locks](/content/part7/tasks/mutexes.md)
- [Back to Part 7](/content/part7/README.md)
- [Content](/content/README.md)
- [HOME](/README.md)
