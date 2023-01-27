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
        -> typename time_t::rep
    {
        auto start = std::chrono::system_clock::now();
        std::invoke(func, std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<time_t>(std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

template<typename T>
auto operator<< 
(std::ostream& os, const std::vector<T>& v) -> std::ostream&
{
    os << "[ ";
    for (auto i { v.size() }; const auto& e : v)
        if (--i > (v.size() - 3))
            os << e << ", ";

    auto last = v.end() - 3;
    os << "..., " << *++last << ", ";
    os << *++last << " ]";
    return os;
}

auto main() -> int
{
    auto v = std::vector<double>(100'000'007, 0.1);
    auto r = std::vector<double>(100'000'007, 0.0);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::fixed << std::setprecision(1);
    
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;
    std::cout << "|      Algorithm      | Exec Policy | Binary-Op |  Type  |    Time    |                    Result                     |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "|  std::partial_sum   |   Serial    |     +     | double | ";
    auto scan_time = measure<>::execution([](const auto& v, auto& r){ std::partial_sum(v.begin(), v.end(), r.begin()); }, v, r);
    std::cout << std::setw(7) << scan_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::exclusive_scan | Sequencial  |     +     | double | ";
    auto seq_time = measure<>::execution([](const auto& v, auto& r){ std::exclusive_scan(std::execution::seq, v.begin(), v.end(), r.begin(), 0.0); }, v, r);
    std::cout << std::setw(7) << seq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::exclusive_scan |  Parallel   |     +     | double | ";
    auto par_time = measure<>::execution([](const auto& v, auto& r){ std::exclusive_scan(std::execution::par, v.begin(), v.end(), r.begin(), 0.0); }, v, r);
    std::cout << std::setw(7) << par_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::exclusive_scan | Unsequenced |     +     | double | ";
    auto unseq_time = measure<>::execution([](const auto& v, auto& r){ std::exclusive_scan(std::execution::unseq, v.begin(), v.end(), r.begin(), 0.0); }, v, r);
    std::cout << std::setw(7) << unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;

    std::cout << "| std::exclusive_scan |  Par-Unseq  |     +     | double | ";
    auto par_unseq_time = measure<>::execution([](const auto& v, auto& r){ std::exclusive_scan(std::execution::par_unseq, v.begin(), v.end(), r.begin(), 0.0); }, v, r);
    std::cout << std::setw(7) << par_unseq_time << " us | " << r << " |" << std::endl;
    std::cout << "+---------------------+-------------+-----------+--------+------------+-----------------------------------------------+" << std::endl;
    
    return 0;
}