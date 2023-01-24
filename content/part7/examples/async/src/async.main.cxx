#include <algorithm>
#include <concepts>
#include <iostream>
#include <iterator>
#include <thread>

template<std::random_access_iterator I, std::sentinel_for<I> S, typename Acc>
auto parallel_sum(I first, S last, Acc init) -> I
{
    if (first == last)
        return first;
    
    auto length { last - first };
    if (length < 1000)
    {
        for (; first != last; ++first)
            init += *first;
        
        return
    }

    auto middle = first + (length / 2);

}

auto main() -> int
{
        

    return 0;
}