#include <algorithm>
#include <atomic>
#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

template <typename time_t = std::chrono::microseconds>
struct measure
{
    template <typename F, typename... Args>
    static auto execution(F func, Args&&... args) 
        -> std::pair<typename time_t::rep, std::invoke_result_t<F, Args...>>
    {
        auto start = std::chrono::system_clock::now();
        auto result = std::invoke(func, std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<time_t>(std::chrono::system_clock::now() - start);
        return std::pair<typename time_t::rep, std::invoke_result_t<F, Args...>>{ duration.count(), result };
    }
};

auto main() -> int
{
    auto count = std::atomic<int>{ 0 };
    auto v = std::vector<double>(100'000'007, 0.1);

    auto alg = [&count](const auto& v)
    { 
        return std::reduce(
            std::execution::par_unseq,
            v.begin(),
            v.end(),
            0.0,
            [&count](const auto& x, const auto& y) {
                count.fetch_add(1, std::memory_order_relaxed);
                return x + y;
            }
        ); 
    };

    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(4);
    
    auto [time, result] = measure<>::execution(alg, v);

    std::cout << "std::reduce (parallel-unsequenced execution):\n"
              << "Result: " << result << "\n"
              << "Time: " << time << " us\n"
              << "Atomic Count: " << count.load() << std::endl;
    
    return 0;
}