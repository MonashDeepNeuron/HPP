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
    auto v1 = std::vector<double>(100'000'007, 0.145);
    auto v2 = std::vector<double>(100'000'007, 0.524);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(4);
    
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;
    std::cout << "|       Algorithm       | Exec Policy | Binary-Ops |  Type  |    Time    |     Result     |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "|  std::inner_product   |   Serial    | (*) -> (+) | double | ";
    auto [in_prod_time, in_prod_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << in_prod_time << " us | " << in_prod_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::transform_reduce | Sequencial  | (*) -> (+) | double | ";
    auto [seq_time, seq_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::transform_reduce(std::execution::seq, v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << seq_time << " us | " << seq_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::transform_reduce |  Parallel   | (*) -> (+) | double | ";
    auto [par_time, par_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::transform_reduce(std::execution::par, v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << par_time << " us | " << par_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::transform_reduce | Unsequenced | (*) -> (+) | double | ";
    auto [unseq_time, unseq_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::transform_reduce(std::execution::unseq, v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << unseq_time << " us | " << unseq_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    std::cout << "| std::transform_reduce |  Par-Unseq  | (*) -> (+) | double | ";
    auto [par_unseq_time, par_unseq_result] = measure<>::execution([](const auto& v1, const auto& v2){ return std::transform_reduce(std::execution::par_unseq, v1.begin(), v1.end(), v2.begin(), 0.0); }, v1, v2);
    std::cout << std::setw(7) << par_unseq_time << " us | " << par_unseq_result << " |" << std::endl;
    std::cout << "+-----------------------+-------------+------------+--------+------------+----------------+" << std::endl;

    return 0;
}