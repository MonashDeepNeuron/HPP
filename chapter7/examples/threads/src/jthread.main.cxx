#include <atomic>
#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

using namespace std::literals;

auto job = [](std::stop_token tkn) 
{
    for (auto i { 10 }; i; --i) 
    {
        std::this_thread::sleep_for(150ms);

        if (tkn.stop_requested()) 
        {
            std::cout << "  The job has be requested to stop\n";
            return;
        }

        std::cout << " Continuing with job\n";
    }
};

auto stop_job = [](std::stop_source source) 
{
    std::this_thread::sleep_for(500ms);
    std::cout << "Request stop for worker via source\n";
    source.request_stop();
};

auto main() -> int
{
    auto worker = std::jthread(job);
 
    std::cout << "\nPass source to other thread:\n";
 
    std::stop_source stop_source = worker.get_stop_source();
    auto stopper = std::thread(stop_job, stop_source);
    stopper.join();
    
    std::this_thread::sleep_for(250ms);

    return 0;
}