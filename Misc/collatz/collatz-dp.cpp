#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <chrono>

std::unordered_map<uint64_t, uint64_t> dp;

uint64_t f(uint64_t x) {
    auto &ret = dp[x];
    if (ret != 0) return ret;
    if (x == 1) return ret = 1;

    if (x & 1) return ret = 1 + f(3 * x + 1);
    else return ret = 1 + f(x / 2);
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
