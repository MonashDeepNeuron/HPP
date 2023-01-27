# Mutexes & Locks

## Contents

- [Mutexes \& Locks](#mutexes--locks)
  - [Contents](#contents)
  - [Task 4](#task-4)
    - [Task 4.1 : What is a Mutex?](#task-41--what-is-a-mutex)
    - [Task 4.2 : Other Mutex Types](#task-42--other-mutex-types)
    - [Task 4.3 : What is a lock?](#task-43--what-is-a-lock)
    - [Task 4.4 : Semaphores](#task-44--semaphores)
    - [Task 4.5 : Lock Types](#task-45--lock-types)
    - [Task 4.6 : Latches](#task-46--latches)
    - [Task 4.7 : Barriers](#task-47--barriers)
  - [Links](#links)

## Task 4

### Task 4.1 : What is a Mutex?

A mutex is a _mutually-exclusive-object_. It is used to synchronize access to shared memory resources across multiple threads. C++ mutex type is called `std::mutex` from the `<mutex>` header. Threads can own a `std::mutex` by locking it. Other threads will block when they try to lock a `std::mutex` owned by another thread. `std::mutex` also implement a try-lock that returns a Boolean indicating the result off the lock attempt. A thread cannot own a `std::mutex` before it tries to lock it. Mutexes are generally implemented as a OS primitive. Because `std::mutex` (and C++ other mutex types) use locking and unlocking methods to control access, these types are not considered to be RAII types. Instead there are locking types that will lock a mutex on construction and unlock it on destruction (more below).

```cxx
#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

using namespace std::literals;

auto mx  = std::mutex{};
auto map = std::map<int, long long>{};

auto job = [](auto job_id)
{ 
    std::this_thread::sleep_for(150ms);
    auto ss = std::stringstream{};
    ss << std::this_thread::get_id();
    auto thread_id = std::stoll(ss.str());

    while (!mx.try_lock())
        std::this_thread::sleep_for(150ms);

    map.insert({ job_id, thread_id });
    mx.unlock();
    std::this_thread::sleep_for(150ms);
};

auto main() -> int
{    
    auto thr_count { std::thread::hardware_concurrency() };
    auto pool = std::vector<std::thread>(thr_count);

    /// Queue jobs
    for (auto i { 0u }; i < thr_count; ++i)
        pool.emplace_back(job, i);

    std::this_thread::sleep_for(200ms);

    /// Join all job threads
    for (auto& th : pool)
        if (th.joinable())
            th.join();

    std::cout << "{ ";
    for (auto i { map.size() }; auto& [k, v] : map)
        std::cout << k << ": " << v << (i-- ? ", " : "");
    std::cout << " }" << std::endl;

    return 0;
}
```

```sh
bpt build -t build.yaml -o build

# ...

./build/mutex
{ 0: 140667719128640, 1: 140667710735936, 2: 140667702343232, 3: 140667693950528, 4: 140667685557824, 5: 140667677165120, 6: 140667668772416, 7: 140667660379712, 8: 140667651987008, 9: 140667643594304, 10: 140667635201600, 11: 140667626808896, 12: 140667618416192, 13: 140667610023488, 14: 140667601630784, 15: 140667593238080,  }
```

[Example](/content/chapter7/examples/mutex/src/mutex.main.cxx)

[`std::mutex` : cppreference](https://en.cppreference.com/w/cpp/thread/mutex)

### Task 4.2 : Other Mutex Types

- `std::timed_mutex` - Mutex that offers timeout based locking methods. Locking will be attempted for a certain duration.
- `std::recursive_mutex` - Mutex that can be repeatedly locked by the same thread multiple times. Must be unlocked the same number of times to become fully unlocked.
- `std::recursive_timed_mutex` - Recursive mutex with timeout locking.
- `std::shared_mutex` - A mutex that offers to levels of access, _shared_ or _exclusive_. Shared locking allows for multiple threads to share a mutex and read the shared memory resources while exclusive only allows one thread to access the shared resources with write privileges. If one thread has a shared lock an a mutex other threads can only gain a shared lock on it as well prohibiting the ability to gain exclusive access from another thread until all threads have unlocked the shared lock. Similarly, a thread with an exclusive lock on a thread disallows other threads from gaining any lock on the mutex until it has been unlocked.
- `std::shared_timed_mutex` - Same as a `std::shared_mutex` but offers timeout based exclusive and shared locking.

- [`std::timed_mutex` : cppreference](https://en.cppreference.com/w/cpp/thread/timed_mutex)
- [`std::recursive_mutex` : cppreference](https://en.cppreference.com/w/cpp/thread/recursive_mutex)
- [`std::recursive_timed_mutex` : cppreference](https://en.cppreference.com/w/cpp/thread/recursive_timed_mutex)
- [`std::shared_mutex` : cppreference](https://en.cppreference.com/w/cpp/thread/shared_mutex)
- [`std::shared_timed_mutex` : cppreference](https://en.cppreference.com/w/cpp/thread/shared_timed_mutex)

### Task 4.3 : What is a lock?

A lock is another kind of synchronization primitive. Locks can be used to wrap other synchronization primitives like mutexes and bind the locking and unlocking if the mutex to the lifetime of the lock using RAII or can themselves be synchronization primitives that must be acquires and released. Most locks in C++ perform the former which allow for mutex locking to be scoped ensuring proper releasing of resources even if exceptions are thrown. Locks however, can also be used erroneously creating _deadlocks_ for which two threads rely on the releasing of each others locks in order to release their respective locks. They also have a little more overhead as you have to create and destroy locks. Locks will often be created in an unnamed scope to ensure that it only lives as long as it needs.

### Task 4.4 : Semaphores

The most simple type of lock is a semaphore. Semaphores allow multiple threads to access the same resource. The number of accessors is dictated by a count which decrements when the semaphore is acquires and blocks for any acquisitions for which the count is zero. C++ semaphore type which supports arbitrary size counts is called `std::counting_semaphore`. There is also a specialisation for which only a single accessor is allowed, called `std::binary_semaphore`. Both of these live in the `semaphore` header.

```cxx
#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

using namespace std::literals;

auto toMain     = std::binary_semaphore{ 0 };
auto fromMain   = std::binary_semaphore{ 0 };

auto work = []()
{ 
    fromMain.acquire();

    std::cout << "[thread]: Got signal" << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << "[thread]: Sent signal" << std::endl;

    toMain.release();
};

auto main() -> int
{    
    auto th = std::thread{ work };

    std::cout << "[Main]: Sent signal" << std::endl;
    fromMain.release();
    toMain.acquire();
    std::cout << "[Main]: Got signal" << std::endl;

    th.join();

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/semaphores 
[Main]: Sent signal
[thread]: Got signal
[thread]: Sent signal
[Main]: Got signal
```

[Example](/content/chapter7/examples/mutex/src/semaphores.main.cxx)

[`std::counting_semaphore` & `std::binary_semaphore` : cppreference](https://en.cppreference.com/w/cpp/thread/counting_semaphore)

### Task 4.5 : Lock Types

- `std::lock_guard` - The most basic kind of mutex locking wrapper. It binds the locking lifetime of a mutex to the lifetime of the lock. It takes a template type parameter of the mutex type and a mutex as a constructor argument. It can also adopt the ownership of a mutex by passing a second constructor argument `std::adopt_lock` which does not lock the mutex but ensuring the calling thread will unlock it. `std::lock_guard` is non-copyable.
- `std::scoped_lock` - A lock for acquiring ownership of zero or more mutexes for the duration of a scope block. When constructed and given ownership of multiple mutexes, the locking and unlocking of mutexes uses a deadlock avoidance algorithm.
- `std::unique_lock` - Used to acquire an exclusive lock on a mutex with deferred, time-constrained, recursive and transfer semantics for locking. It is non-copyable but is moveable.
- `std::shared_lock` - Used to gain shared access to a mutex with similar semantics to `std::unique_lock`. Used for locking a `std::shared_mutex` in a shared ownership model.

```cxx
#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

using namespace std::literals;

auto mx  = std::mutex{};
auto map = std::map<int, long long>{};

auto job = [](auto job_id)
{ 
    std::this_thread::sleep_for(150ms);
    auto ss = std::stringstream{};
    ss << std::this_thread::get_id();
    auto thread_id = std::stoll(ss.str());

    /// Acquire a lock on mx that lasts for this scope
    {
        auto lk = std::lock_guard{ mx };
        map.insert({ job_id, thread_id });
    }
    
    std::this_thread::sleep_for(150ms);
};

auto main() -> int
{    
    auto thr_count { std::thread::hardware_concurrency() };
    auto pool = std::vector<std::thread>(thr_count);

    /// Queue jobs
    for (auto i { 0u }; i < thr_count; ++i)
        pool.emplace_back(job, i);

    std::this_thread::sleep_for(200ms);

    /// Join all job threads
    for (auto& th : pool)
        if (th.joinable())
            th.join();

    std::cout << "{ ";
    for (auto i { map.size() }; auto& [k, v] : map)
        std::cout << k << ": " << v << (i-- ? ", " : "");
    std::cout << " }" << std::endl;

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/locks
{ 0: 139998766057024, 1: 139998757664320, 2: 139998749271616, 3: 139998740878912, 4: 139998732486208, 5: 139998724093504, 6: 139998715700800, 7: 139998707308096, 8: 139998698915392, 9: 139998690522688, 10: 139998682129984, 11: 139998673737280, 12: 139998665344576, 13: 139998656951872, 14: 139998648559168, 15: 139998640166464,  }
```

[Example](/content/chapter7/examples/mutex/src/locks.main.cxx)

- [`std::lock_guard` : cppreference](https://en.cppreference.com/w/cpp/thread/lock_guard)
- [`std:scoped_lock` : cppreference](https://en.cppreference.com/w/cpp/thread/scoped_lock)
- [`std::unique_lock` : cppreference](https://en.cppreference.com/w/cpp/thread/unique_lock)
- [`std::shared_lock` : cppreference](https://en.cppreference.com/w/cpp/thread/shared_lock)
- [Locking Strategies : cppreference](https://en.cppreference.com/w/cpp/thread/lock_tag)

### Task 4.6 : Latches

A `std::latch` is count-down synchronization primitive with the count is initialized on construction. Threads can wait at a `std::latch` until the count reaches zero. Once this happens, all the threads waiting on the latch are released. `std::latch` cannot increment or reset its counter after construction making it a single use barrier. `std::latch` is non-copyable and lives in the `<latch>` header.

```cxx
#include <chrono>
#include <iostream>
#include <latch>
#include <syncstream>
#include <thread>
#include <vector>

using namespace std::literals;

auto thr_count  = std::thread::hardware_concurrency();
auto done       = std::latch{ thr_count };
auto cleanup    = std::latch{ 1 };

auto job = [](auto job_id)
{ 
    std::this_thread::sleep_for(2s);
    std::osyncstream(std::cout) << "Job " << job_id << " done.\n";
    done.count_down();
    cleanup.wait();
    std::osyncstream(std::cout) << "Job " << job_id << " cleaned up.\n";
};

auto main() -> int
{    
    auto pool = std::vector<std::thread>(thr_count);

    std::cout << "Starting jobs...\n";
    for (auto i { 0u }; i < thr_count; ++i)
        pool.emplace_back(job, i);

    done.wait();
    std::cout << "All jobs done.\n";
    std::this_thread::sleep_for(200ms);
    std::cout << "\nStarting cleanup...\n";
    cleanup.count_down();
    std::this_thread::sleep_for(200ms);

    for (auto& th : pool)
        if (th.joinable())
            th.join();
    std::cout << "All jobs cleaned up.\n";

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/latch
Starting jobs...
Job 1 done.
Job 0 done.
Job 3 done.
Job 5 done.
Job 4 done.
Job 7 done.
Job 6 done.
Job 8 done.
Job 2 done.
Job 10 done.
Job 9 done.
Job 13 done.
Job 12 done.
Job 11 done.
Job 14 done.
Job 15 done.
All jobs done.

Starting cleanup...
Job 4 cleaned up.
Job 6 cleaned up.
Job 7 cleaned up.
Job 12 cleaned up.
Job 13 cleaned up.
Job 0 cleaned up.
Job 14 cleaned up.
Job 10 cleaned up.
Job 11 cleaned up.
Job 2 cleaned up.
Job 15 cleaned up.
Job 5 cleaned up.
Job 3 cleaned up.
Job 9 cleaned up.
Job 8 cleaned up.
Job 1 cleaned up.
All jobs cleaned up.
```

[Example](/content/chapter7/examples/mutex/src/latch.main.cxx)

[`std::latch` : cppreference](https://en.cppreference.com/w/cpp/thread/latch)

### Task 4.7 : Barriers

`std::barrier` is a more general version of `std::latch`. The lifetime of a `std::barrier` consists of one or more phases. The first is a synchronization phase for which threads will block where once the counter has reach zero for the `std::barrier` the threads will unblock. Right before unblocking, a completion function will run which is optionally supplied at the `std::barrier` construction. After this the `std::barrier` will reset its counter and can be reused. The overall count can be reduced on arrival by a thread. `std::barrier` is non-copyable and lives in the `<barrier>` header.

```cxx
#include <chrono>
#include <iostream>
#include <barrier>
#include <syncstream>
#include <string>
#include <thread>
#include <vector>

using namespace std::literals;

auto thr_count  = std::thread::hardware_concurrency();

auto on_completion = []() noexcept
{ 
    static auto message = "All jobs done.\nWorkers are at lunch before cleaning up...\n"s;
    std::osyncstream(std::cout) << message;
    std::this_thread::sleep_for(3s);
    message = "All cleaned up.\n"s;
};

auto barrier = std::barrier{ thr_count, on_completion };

auto job = [](auto job_id)
{ 
    std::this_thread::sleep_for(2s);
    std::osyncstream(std::cout) << "Job " << job_id << " done.\n";
    barrier.arrive_and_wait();
    std::osyncstream(std::cout) << "Job " << job_id << " cleaned up.\n";
    barrier.arrive_and_wait();
};

auto main() -> int
{    
    auto pool = std::vector<std::thread>(thr_count);

    std::cout << "Starting jobs...\n";
    for (auto i { 0u }; i < thr_count; ++i)
        pool.emplace_back(job, i);

    std::this_thread::sleep_for(200ms);

    for (auto& th : pool)
        if (th.joinable())
            th.join();
    
    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/barrier
Starting jobs...
Job 2 done.
Job 1 done.
Job 3 done.
Job 5 done.
Job 0 done.
Job 4 done.
Job 8 done.
Job 7 done.
Job 6 done.
Job 12 done.
Job 11 done.
Job 10 done.
Job 9 done.
Job 15 done.
Job 13 done.
Job 14 done.
All jobs done.
Workers are at lunch before cleaning up...
Job 2 cleaned up.
Job 8 cleaned up.
Job 1 cleaned up.
Job 0 cleaned up.
Job 6 cleaned up.
Job 3 cleaned up.
Job 14 cleaned up.
Job 4 cleaned up.
Job 11 cleaned up.
Job 15 cleaned up.
Job 12 cleaned up.
Job 9 cleaned up.
Job 13 cleaned up.
Job 7 cleaned up.
Job 5 cleaned up.
Job 10 cleaned up.
All cleaned up.
```

[Example](/content/chapter7/examples/mutex/src/barrier.main.cxx)

[`std::barrier` : cppreference](https://en.cppreference.com/w/cpp/thread/barrier)

## Links

- [Previous Page : Threads](/content/chapter7/tasks/threads.md)
- [Next Page : Async](/content/chapter7/tasks/async.md)
- [Content](/content/README.md)
- [HOME](/README.md)
