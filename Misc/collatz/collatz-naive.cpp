#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <chrono>

uint64_t f(uint64_t x) {
    if (x == 1) return 1;

    if (x & 1) return 1 + f(3 * x + 1);
    else return 1 + f(x / 2);
}

int main() {
    freopen("collatz-data-large-x.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    auto t0 = std::chrono::steady_clock::now();

    int n; std::cin >> n;
    while (n--) {
        uint64_t x; std::cin >> x;
        std::cout << f(x) << '\n';
    }

    auto t1 = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    std::cout << "Took " << diff << " µs\n";
}
