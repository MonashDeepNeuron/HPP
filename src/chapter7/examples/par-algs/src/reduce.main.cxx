#include <algorithm>
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
    auto v = std::vector<double>(100'000'007, 0.1);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;
    std::cout << "|    Algorithm    | Exec Policy | Binary-Op |  Type  |    Time    |     Result     |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::accumulate |   Serial    |     +     | double | ";
    auto [acc_time, acc_result] = measure<>::execution([](const auto& v){ return std::accumulate(v.begin(), v.end(), 0.0); }, v);
    std::cout << std::setw(7) << acc_time << " us |  " << acc_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "|   std::reduce   | Sequencial  |     +     | double | ";
    auto [seq_time, seq_result] = measure<>::execution([](const auto& v){ return std::reduce(std::execution::seq, v.begin(), v.end(), 0.0); }, v);
    std::cout << std::setw(7) << seq_time << " us |  " << seq_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "|   std::reduce   |  Parallel   |     +     | double | ";
    auto [par_time, par_result] = measure<>::execution([](const auto& v){ return std::reduce(std::execution::par, v.begin(), v.end(), 0.0); }, v);
    std::cout << std::setw(7) << par_time << " us |  " << par_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "|   std::reduce   | Unsequenced |     +     | double | ";
    auto [unseq_time, unseq_result] = measure<>::execution([](const auto& v){ return std::reduce(std::execution::unseq, v.begin(), v.end(), 0.0); }, v);
    std::cout << std::setw(7) << unseq_time << " us |  " << unseq_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;

    std::cout << "|   std::reduce   |  Par-Unseq  |     +     | double | ";
    auto [par_unseq_time, par_unseq_result] = measure<>::execution([](const auto& v){ return std::reduce(std::execution::par_unseq, v.begin(), v.end(), 0.0); }, v);
    std::cout << std::setw(7) << par_unseq_time << " us |  " << par_unseq_result << "  |" << std::endl;
    std::cout << "+-----------------+-------------+-----------+--------+------------+----------------+" << std::endl;
    
    return 0;
}