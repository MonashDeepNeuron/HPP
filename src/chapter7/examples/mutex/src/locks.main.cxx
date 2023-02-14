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