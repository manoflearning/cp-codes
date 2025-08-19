#include <iostream>
#include <cstdint>
#include <chrono>
#include <algorithm>
#include <unordered_map>
#include <queue>

const size_t CAP = 100'000;

class Cache {
private:
    std::unordered_map<int64_t, int64_t> _dp;
    std::queue<int64_t> _qu;

public:
    bool is_hit(int64_t x) { return _dp.count(x); }
    int64_t get(int64_t x) { return _dp[x]; }
    void put(int64_t x, int64_t y) {
        if (_dp.count(x)) return;

        if (_dp.size() == CAP) {
            auto v = _qu.front();
            _qu.pop();

            _dp.erase(v);
        }

        _dp[x] = y;
        _qu.push(x);
    }
} cache;

int64_t f(int64_t x) {
    if (x == 0) return 0;
    if (cache.is_hit(x)) return cache.get(x);

    int64_t ret = std::max(x, f(x / 2) + f(x / 3) + f(x / 4));
    cache.put(x, ret);
    return ret;
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
