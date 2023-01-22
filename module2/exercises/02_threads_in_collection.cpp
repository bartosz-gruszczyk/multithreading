#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <vector>
#include <thread>
using namespace std;

// Secure your code so that each thread can safely enter its full text into the stream.
// lepiej zrobic mutex nie globalny
// mutex workMutex; 

void do_work(int id, mutex& workMutex) {
    this_thread::sleep_for(100ms); // do not block sleep! without sense!
    // lock_guard<std::mutex> lock(workMutex);
    // od c++17 mozna robic bez podawania typu
    // zamiast skladac strumien w cout moze lepiej tak:
    stringstream ss;
    lock_guard lock(workMutex);
    ss << "Thread [" << id << "]: " << "Job done!" << endl;
    // cout << "Thread [" << id << "]: " << "Job done!" << endl;
    cout << ss.rdbuf();
}

// bez lock guarda
// void do_work(int id) {
//     this_thread::sleep_for(100ms); // do not block sleep! without sense!
//     workMutex.lock();
//     cout << "Thread [" << id << "]: " << "Job done!" << endl;
//     workMutex.unlock();
// }

int main() {
    mutex m;
    vector<thread> threads;
    for (int i = 0; i < 20; i++) {
        threads.emplace_back(thread(do_work, i, std::ref(m)));
    }
    for (auto && t : threads) {
        t.join();
    }
    return 0;
}
