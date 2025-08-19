#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <random>

int main() {
    freopen("data-large-x.txt", "w", stdout);

    static std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<int64_t> dist(1, 1e6);

    int n = 2e4;
    std::cout << n << '\n';
    while (n--) {
        int64_t x = dist(rng);
        std::cout << x << ' ';
    }
}
