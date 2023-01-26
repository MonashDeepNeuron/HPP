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