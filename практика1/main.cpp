#include <iostream>
#include <stack>
#include <vector>
#include <chrono>
#include <iomanip>
#include <utility>

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
    auto start_time = std::chrono::high_resolution_clock::now();

    auto result = func(std::forward<Args>(args)...);

    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    return std::make_pair(result, duration.count());
}


bool find_in_stack(std::stack<int> s, int value) {
    while (!s.empty()) {
        if (s.top() == value)
            return true;
        s.pop();
    }
    return false;
}

size_t calculate_memory(int n) {
    return n * sizeof(int);
}

int main() {

    setlocale(LC_ALL, "Russian");
    std::vector<int> sizes = {
        10, 100, 1000, 10000, 100000,
        200000, 400000, 600000, 800000, 1000000
    };

    std::vector<double> times_ms;     
    std::vector<double> memory_kb;

    std::cout << "Размер int: " << sizeof(int) << " байт\n\n";

    std::cout << std::setw(12) << "n"
        << std::setw(20) << "Время (мс)"
        << std::setw(20) << "Память (байт)"
        << std::setw(20) << "Память (КБ)"
        << "\n";

    for (int n : sizes) {

        std::stack<int> s;
        for (int i = 0; i < n; ++i)
            s.push(i);

        int crah = -1; // худший случай

        auto [result, time] = measure_execution_time(find_in_stack, s, crah);

        size_t memory = calculate_memory(n);

        std::cout << std::setw(12) << n
            << std::setw(20) << time
            << std::setw(20) << memory
            << std::setw(20) << memory / 1024.0
            << "\n";
    }

  

    return 0;
}