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