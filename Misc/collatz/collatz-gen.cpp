#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <random>
using namespace std;

unordered_map<int64_t, int64_t> dp;

int64_t f(int64_t x) {
    auto &ret = dp[x];
    if (ret == 0) return ret;
    if (x == 1) return ret = 1;

    if (x & 1) return ret = 1 + f(3 * x + 1);
    else return ret = 1 + f(x / 2);
}

int main() {
    freopen("collatz-data-large-x.txt", "w", stdout);

    static std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<int64_t> dist(1, 1e18);

    int n = 2e5;
    cout << n << '\n';
    while (n--) {
        int64_t x = dist(rng);
        cout << x << ' ';
    }
}
