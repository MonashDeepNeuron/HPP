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