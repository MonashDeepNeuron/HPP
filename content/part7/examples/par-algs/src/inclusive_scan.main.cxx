#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

template <typename time_t = std::chrono::microseconds>
struct measure
{
  template <typename F, typename... Args>
  static auto execution(F func, Args&&... args) -> typename time_t::rep
  {
    using namespace std::chrono;
    auto start = system_clock::now();
    func(std::forward<Args>(args)...);
    auto duration = duration_cast<time_t>(system_clock::now() - start);
    return duration.count();
  }
};

auto main() -> int
{
    auto dv = std::vector<double>(100'000'007, 0.1);
    
    std::cout << "std::accumulate | + | doubles | ";
    auto acc_time = measure<>::execution([](const auto& v){ std::accumulate(v.begin(), v.end(), 0.0); }, dv);
    std::cout << "Took: " << acc_time << " us" << std::endl;
    
    return 0;
}