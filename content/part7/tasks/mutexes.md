# Mutexes & Locks

## Contents

- [Mutexes \& Locks](#mutexes--locks)
  - [Contents](#contents)
  - [Task 4](#task-4)
    - [Task 4.1 : What is a Mutex?](#task-41--what-is-a-mutex)
    - [Task 4.2 : Other Mutex Types](#task-42--other-mutex-types)
    - [Task 4.6 : What is a lock?](#task-46--what-is-a-lock)
    - [Task 4.7 : Semaphores](#task-47--semaphores)
      - [Task 4.7.1 : Binary Semaphore](#task-471--binary-semaphore)
      - [Task 4.7.2 : Counting Semaphore](#task-472--counting-semaphore)
    - [4.8 : Lock types](#48--lock-types)
      - [Task 4.8.1 : Lock Guard](#task-481--lock-guard)
      - [Task 4.8.2 : Scoped Lock](#task-482--scoped-lock)
      - [Task 4.8.3 : Unique Lock](#task-483--unique-lock)
      - [Task 4.8.4 : Shared Lock](#task-484--shared-lock)
    - [Task 4.9 : Latch](#task-49--latch)
    - [Task 4.10 : Barrier](#task-410--barrier)
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

[Example](/content/part7/examples/mutex/src/mutex.main.cxx)

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

### Task 4.6 : What is a lock?

~

### Task 4.7 : Semaphores

~

#### Task 4.7.1 : Binary Semaphore

~

```cxx

```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/
```

[Example](/content/part7/examples)

[`std::binary_semaphore` : cppreference](https://en.cppreference.com/w/cpp/thread/counting_semaphore)

#### Task 4.7.2 : Counting Semaphore

~

```cxx

```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/
```

[Example](/content/part7/examples)

[`std::counting_semaphore` : cppreference](https://en.cppreference.com/w/cpp/thread/counting_semaphore)

### 4.8 : Lock types

~

#### Task 4.8.1 : Lock Guard

~

```cxx

```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/
```

[Example](/content/part7/examples)

[`std::lock_guard` : cppreference](https://en.cppreference.com/w/cpp/thread/lock_guard)

#### Task 4.8.2 : Scoped Lock

~

```cxx

```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/
```

[Example](/content/part7/examples)

[`std:scoped_lock` : cppreference](https://en.cppreference.com/w/cpp/thread/scoped_lock)

#### Task 4.8.3 : Unique Lock

~

```cxx

```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/
```

[Example](/content/part7/examples)

[`std::unique_lock` : cppreference](https://en.cppreference.com/w/cpp/thread/unique_lock)

#### Task 4.8.4 : Shared Lock

~

```cxx

```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/
```

[Example](/content/part7/examples)

[`std::shared_lock` : cppreference](https://en.cppreference.com/w/cpp/thread/shared_lock)

### Task 4.9 : Latch

~

```cxx

```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/
```

[Example](/content/part7/examples)

[`std::latch` : cppreference](https://en.cppreference.com/w/cpp/thread/latch)

### Task 4.10 : Barrier

~

```cxx

```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/
```

[Example](/content/part7/examples)

[`std::barrier` : cppreference](https://en.cppreference.com/w/cpp/thread/barrier)

## Links

- [Previous Page : Threads](/content/part7/tasks/threads.md)
- [Next Page : Async/Await](/content/part7/tasks/async.md)
- [Content](/content/README.md)
- [HOME](/README.md)
