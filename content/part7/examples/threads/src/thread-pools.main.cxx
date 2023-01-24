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
    auto pool = std::vector<std::thread>(thr_count);

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