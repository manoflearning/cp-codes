#include <iostream>
#include <cstdint>
#include <chrono>
#include <algorithm>

int64_t f(int64_t x) {
    if (x == 0) return 0;
    return std::max(x, f(x / 2) + f(x / 3) + f(x / 4));
}

int main() {
    freopen("data-large-x.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    auto t0 = std::chrono::steady_clock::now();

    int32_t n; std::cin >> n;
    while (n--) {
        int64_t x; std::cin >> x;
        std::cout << f(x) << '\n';
    }

    auto t1 = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    std::cout << "Took " << diff << " µs\n";
}
