#include <iostream>
#include <chrono>
#include <vector>

constexpr int ARRAY_SIZE = 100000;
constexpr int ITERATIONS = 100;

// No-inline functions
__attribute__((noinline)) int multiply_regular(int a, int b) {
    return a * b;
}

__attribute__((noinline)) int complex_calc_regular(int x, int y) {
    return multiply_regular(x + y, 2) + x + 3;
}

// Inline functions
__attribute__((always_inline)) inline int multiply_inline(int a, int b) {
    return a * b;
}

__attribute__((always_inline)) inline int complex_calc_inline(int x, int y) {
    return multiply_inline(x + y, 2) + x + 3;
}

double measure_time(std::string name, auto (*func)(const std::vector<int>&), const std::vector<int>& data) {
    auto start = std::chrono::steady_clock::now();
    volatile long long result = func(data);
    auto end = std::chrono::steady_clock::now();
    
    double duration = std::chrono::duration<double>(end - start).count();
    std::cout << name << ": " << duration << "s\n";
    return duration;
}

long long test_regular(const std::vector<int>& data) {
    long long sum = 0;
    for (int iter = 0; iter < ITERATIONS; ++iter) {
        for (int i = 0; i < ARRAY_SIZE - 1; ++i) {
            sum += complex_calc_regular(data[i], data[i + 1]);
        }
    }
    return sum;
}

long long test_inline(const std::vector<int>& data) {
    long long sum = 0;
    for (int iter = 0; iter < ITERATIONS; ++iter) {
        for (int i = 0; i < ARRAY_SIZE - 1; ++i) {
            sum += complex_calc_inline(data[i], data[i + 1]);
        }
    }
    return sum;
}

int main() {
    std::vector<int> data(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        data[i] = i % 100 + 1;
    }
    
    double regular_time = measure_time("Regular", test_regular, data);
    double inline_time = measure_time("Inline ", test_inline, data);
    
    double improvement = ((regular_time - inline_time) / regular_time) * 100.0;
    std::cout << "Improvement: " << improvement << "%\n";
    
    return 0;
}