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
