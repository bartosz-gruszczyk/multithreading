#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

// four threads, show id n-times and sleep for some time
void doSth(int n) {
    for (int i = 0; i < n; ++i) {
        // std::string str{"thread " std::this_thread::get_id() + '\n'};
        std::cout << "thread " << std::this_thread::get_id() << '\n';
    }
    std::this_thread::sleep_for(2s);
}

int main() {
    constexpr int THREADS_NUMBER = 4;
    std::vector<std::thread> threads;
    threads.reserve(THREADS_NUMBER);
    for (int i = 0; i < THREADS_NUMBER; ++i) {
        threads.emplace_back(doSth, 4);
    }

    for (auto & th : threads) {
        th.join();
    }


}