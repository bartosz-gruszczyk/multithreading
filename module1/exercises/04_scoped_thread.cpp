#include <thread>
#include <stdexcept>
#include <chrono>
#include <iostream>
using namespace std;

class scoped_thread {
public:
    // TODO: Your implementation goes here
    explicit scoped_thread(std::thread th) : th_{std::move(th)} { //explicit zeby nie bylo niejawnych konwersji
        if (!th_.joinable()) {
            throw std::logic_error("Cannot create an empty thread...");
        } 
    }

    // scoped_thread(std::thread th) {
    //     // joinable?
    //     th_ = std::move(th);
    // }
    // ::::: PERFECT FORWARDING :::::
    template <typename Function, typename... Args>
    scoped_thread(Function&& f, Args&&... args) : th_{std::forward<Function>(f), std::forward<Args>(args)...} {}
    // scoped_thread(Function f, Args... args) : th_{f, args...} {}

    scoped_thread(const scoped_thread&) = delete; // const bo kopia?
    scoped_thread(scoped_thread&& other) {
        th_ = other.get();
    }
    scoped_thread& operator=(const scoped_thread&) = delete;
    scoped_thread& operator=(scoped_thread&& ohter) {
        th_ = ohter.get();
        return *this;
    }

    ~scoped_thread() {
        if (th_.joinable()) {
            th_.join();
        }
    }

    std::thread get() {
        return std::move(th_);
    } 

private:
    std::thread th_;
};

void do_sth(int) {
    this_thread::sleep_for(1s);
    cout << this_thread::get_id() << '\n';
}

void do_sth_unsafe_in_current_thread() {
    throw runtime_error("Whoa!");
}

int main() try {
    // TODO: Uncomment
    scoped_thread st(std::thread(do_sth, 42));
    // auto st2 = st; // copying not allowed
    [[maybe_unused]] auto st3 = move(st);
    scoped_thread st4(do_sth, 42);
    // scoped_thread(std::thread{}); // a try to create an empty thread
    do_sth_unsafe_in_current_thread();
    return 0;
} catch (const exception & e) {
    cout << e.what() << endl;
    return -1;
} // thread is safely destroyed
