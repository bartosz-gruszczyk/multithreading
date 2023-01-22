#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main() {
    // TODO: Implement your solution :)
    std::vector<std::thread> threads;
    constexpr size_t threadNumber{20};
    threads.reserve(threadNumber);
    std::cout << "size: " << threads.size() << '\n';
    for (size_t i = 0; i < threadNumber; ++i) {
        threads.emplace_back([](size_t n){
            std::this_thread::sleep_for(1s);
            std::string str{std::to_string(n) + '\n'};
            std::cout << str;
            // std::cout << n << '\n';
        }, i);
    }

    for (size_t i = 0; i < threads.size(); ++i) {
        threads[i].join();
    }
    return 0;
}
