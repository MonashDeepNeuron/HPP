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
