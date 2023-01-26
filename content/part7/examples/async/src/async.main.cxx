#include <algorithm>
#include <chrono>
#include <concepts>
#include <execution>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
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

template<std::random_access_iterator I, std::sentinel_for<I> S, std::movable A>
auto parallel_sum(I first, S last, A init) -> A
{
    auto middle = first + ((last - first) / 2);
    
    /// Launch async sum on last half of the values 
    auto future = std::async(std::launch::async, parallel_sum<I, S, A>, middle, last, A{});
    
    /// Sum first half of the range locally.
    auto result = parallel_sum(first, middle, init);

    /// Obtain the future and sum with the result
    return result + future.get();
}

auto main() -> int
{
    auto v1 = std::vector<double>(999, 0.1);
    auto v2 = std::vector<double>(100'000'007, 0.1);

    std::cout << std::fixed << std::setprecision(5);

    auto [acc_time_v1, acc_result_v1] = measure<>::execution([](const auto& rng){ return std::accumulate(rng.begin(), rng.end(), 0.0); }, v1);
    std::cout << "std::accumulate : [v1 - 999 elements]\n";
    std::cout << "Time: " << acc_time_v1 << " us\n";
    std::cout << "Result: " << acc_result_v1 << std::endl;

    auto [reduce_time_v1, reduce_result_v1] = measure<>::execution([](const auto& rng){ return std::reduce(std::execution::par, rng.begin(), rng.end(), 0.0); }, v1);
    std::cout << "std::reduce(std::execution::par) : [v1 - 999 elements]\n";
    std::cout << "Time: " << reduce_time_v1 << " us\n";
    std::cout << "Result: " << reduce_result_v1 << std::endl;

    auto [par_time_v1, par_result_v1] = measure<>::execution([](const auto& rng){ return std::accumulate(rng.begin(), rng.end(), 0.0); }, v1);
    std::cout << "parallel_sum : [v1 - 999 elements]\n";
    std::cout << "Time: " << par_time_v1 << " us\n";
    std::cout << "Result: " << par_result_v1 << std::endl;

    std::cout << "------------------------------------------------------\n";

    auto [acc_time_v2, acc_result_v2] = measure<>::execution([](const auto& rng){ return std::accumulate(rng.begin(), rng.end(), 0.0); }, v2);
    std::cout << "std::accumulate : [v2 - 100'000'007 elements]\n";
    std::cout << "Time: " << acc_time_v2 << " us\n";
    std::cout << "Result: " << acc_result_v2 << std::endl;

    auto [reduce_time_v2, reduce_result_v2] = measure<>::execution([](const auto& rng){ return std::reduce(std::execution::par, rng.begin(), rng.end(), 0.0); }, v2);
    std::cout << "std::reduce(std::execution::par) : [v2 - 100'000'007 elements]\n";
    std::cout << "Time: " << reduce_time_v2 << " us\n";
    std::cout << "Result: " << reduce_result_v2 << std::endl;

    auto [par_time_v2, par_result_v2] = measure<>::execution([](const auto& rng){ return std::accumulate(rng.begin(), rng.end(), 0.0); }, v2);
    std::cout << "parallel_sum : [v2 - 100'000'007 elements]\n";
    std::cout << "Time: " << par_time_v2 << " us\n";
    std::cout << "Result: " << par_result_v2 << std::endl;

    return 0;
}