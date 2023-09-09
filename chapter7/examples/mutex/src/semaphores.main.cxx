#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

using namespace std::literals;

auto toMain     = std::binary_semaphore{ 0 };
auto fromMain   = std::binary_semaphore{ 0 };

auto work = []()
{ 
    fromMain.acquire();

    std::cout << "[thread]: Got signal" << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << "[thread]: Sent signal" << std::endl;

    toMain.release();
};

auto main() -> int
{    
    auto th = std::thread{ work };

    std::cout << "[Main]: Sent signal" << std::endl;
    fromMain.release();
    toMain.acquire();
    std::cout << "[Main]: Got signal" << std::endl;

    th.join();

    return 0;
}