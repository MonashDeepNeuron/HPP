# Threads

## Contents

- [Threads](#threads)
  - [Contents](#contents)
  - [Task 3](#task-3)
    - [Task 3.1 : What are Threads?](#task-31--what-are-threads)
    - [Task 3.2 : Thread](#task-32--thread)
    - [Task 3.3 : Automatic Threads](#task-33--automatic-threads)
    - [Task 3.4 : Thread Pools](#task-34--thread-pools)
  - [Links](#links)

## Task 3

### Task 3.1 : What are Threads?

Threads or threads of execution are the smallest sequence of instructions that is managed by a schedular of an operating system. Threads are a sub-object of a process. A process can have multiple threads allowing parts of a process to run concurrently. In C++ we can spawn thread objects that will run a function until completion and then must be rejoined to the main thread or detached.

### Task 3.2 : Thread

C++ thread object is called `std::thread`. It takes as its first argument a function to run as well as any arguments that must be forwarded to the function. The function will begin to run immediately at the threads construction. Along with `std::thread` there is the `std::this_thread` namespaces which can get the ID or make the current thread sleep for some time. `std::thread` cannot be copied but can be moved.

```cxx
#include <atomic>
#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

using namespace std::literals;

auto work = [](std::atomic_ref<int> counter)
{
    std::osyncstream(std::cout) << "Doing work on thread: " << std::this_thread::get_id() << " ...\n";
    auto count = counter.fetch_add(1, std::memory_order_relaxed);
    std::osyncstream(std::cout) << "Call count: " << count << "\n";
    std::this_thread::sleep_for(1.5s);
    std::osyncstream(std::cout) << "Thread " << std::this_thread::get_id() << " Done!\n";
};

auto main() -> int
{
    auto counter { 1 };
    auto atomic_counter = std::atomic_ref<int>{ counter };

    std::thread t1(work, atomic_counter);
    std::thread t2(work, atomic_counter);
    std::thread t3(work, atomic_counter);
    std::thread t4(work, atomic_counter);

    std::cout << "Waiting in main...\n";

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
```

> Note: Uses [`std::osyncstream`](https://en.cppreference.com/w/cpp/io/basic_osyncstream) to synchronize output.

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/thread
Waiting in main...
Doing work on thread: 139836157400640 ...
Call count: 1
Doing work on thread: 139836174186048 ...
Doing work on thread: 139836149007936 ...
Call count: 3
Doing work on thread: 139836165793344 ...
Call count: 4
Call count: 2
Thread 139836157400640 Done!
Thread 139836149007936 Done!
Thread 139836165793344 Done!
Thread 139836174186048 Done!
```

[Example](/content/part7/examples/thread/src/thread.main.cxx)

[`std::thread` : cppreference](https://en.cppreference.com/w/cpp/thread/thread)

### Task 3.3 : Automatic Threads

Since C++20 there has been a thread type that automatically joins on destruction. This is called `std::jthread`. `std::jthread` also supports the use of `std::stop_token` and `std::stop_source`. These are primitives for preemptively cancelling a `std::jthread` from other threads. The `std::stop_source` is obtained from a `std::jthread` object and can be passed to other threads. For a `std::jthread` to be able to listen for stop requests, the function it runs must takes as its first argument a `std::stop_token`.

```cxx
#include <atomic>
#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

using namespace std::literals;

auto job = [](std::stop_token tkn) 
{
    for (auto i { 10 }; i; --i) 
    {
        std::this_thread::sleep_for(150ms);

        if (tkn.stop_requested()) 
        {
            std::cout << "  The job has be requested to stop\n";
            return;
        }

        std::cout << " Continuing with job\n";
    }
};

auto stop_job = [](std::stop_source source) 
{
    std::this_thread::sleep_for(500ms);
    std::cout << "Request stop for worker via source\n";
    source.request_stop();
};

auto main() -> int
{
    auto worker = std::jthread(job);
 
    std::cout << "\nPass source to other thread:\n";
 
    std::stop_source stop_source = worker.get_stop_source();
    auto stopper = std::thread(stop_job, stop_source);
    stopper.join();
    
    std::this_thread::sleep_for(250ms);

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/jthread

Pass source to other thread:
 Continuing with job
 Continuing with job
 Continuing with job
Request stop for worker via source
  The job has be requested to stop
```

[Example](/content/part7/examples/threads/src/jthread.main.cxx)

[`std::jthread` : cppreference](https://en.cppreference.com/w/cpp/thread/jthread)

### Task 3.4 : Thread Pools

A thread pool is a very common idiom in Computer Science. It involves creating a pool or array of threads that sit idle, waiting for work. Jobs are then pushed to the pool which get assigned to an available thread. Once the thread has finished the task the thread goes idle again. The most basic way to create a thread pool is to use a vector of threads and emplace jobs at the back of the vector and then join all joinable threads.

```cxx
#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

using namespace std::literals;

auto job = [](auto job_id)
{ 
    std::this_thread::sleep_for(150ms);
    std::osyncstream(std::cout) << "Thread: " 
                                << std::this_thread::get_id()
                                << " is running job: "
                                << job_id
                                << "\n";
    std::this_thread::sleep_for(150ms);
};

auto main() -> int
{    
    auto thr_count { std::thread::hardware_concurrency() };
    auto pool = std::vector<std::thread>();

    /// Queue jobs
    for (auto i { 0u }; i < thr_count; ++i)
        pool.emplace_back(job, i);

    std::this_thread::sleep_for(200ms);

    /// Join all job threads
    for (auto& th : pool)
        if (th.joinable())
            th.join();

    return 0;
}
```

```sh
$ bpt build -t build.yaml -o build

# ...

$ ./build/thread-pools
Thread: 140166858589760 is running job: 4
Thread: 140166841804352 is running job: 6
Thread: 140166866982464 is running job: 3
Thread: 140166816626240 is running job: 9
Thread: 140166875375168 is running job: 2
Thread: 140166833411648 is running job: 7
Thread: 140166766270016 is running job: 15
Thread: 140166774662720 is running job: 14
Thread: 140166892160576 is running job: 0
Thread: 140166825018944 is running job: 8
Thread: 140166883767872 is running job: 1
Thread: 140166850197056 is running job: 5
Thread: 140166799840832 is running job: 11
Thread: 140166783055424 is running job: 13
Thread: 140166791448128 is running job: 12
Thread: 140166808233536 is running job: 10
```

[Example](/content/part7/examples/threads/src/thread-pools.main.cxx)

[Thread Pool](https://en.wikipedia.org/wiki/Thread_pool)

## Links

- [Previous Page : Atomics](/content/part7/tasks/atomics.md)
- [Next Page : Mutexes & Locks](/content/part7/tasks/mutexes.md)
- [Content](/content/README.md)
- [HOME](/README.md)
