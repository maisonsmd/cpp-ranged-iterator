#include <iostream>
#include "ranged_iterator.h"

int main() {
    // output: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
    for (const auto i : range(10)) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    // output: 0, 2, 4, 6, 8,
    for (const auto i : range(10).step(2)) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    // output: -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    for (const auto i : range(-10, 10)) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    // output: 0, 3, 6, 9,
    for (const auto i : range(0, 10, 3)) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    // output: 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9,
    for (const auto i : range(1.0f, 2.0f, 0.1f)) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    // output: 0, 100000000000, 200000000000, 300000000000, 400000000000, 500000000000, 600000000000, 700000000000, 800000000000, 900000000000,
    for (const auto i : range<size_t>(0, 1000000000000).step(100000000000)) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

    return 0;
}