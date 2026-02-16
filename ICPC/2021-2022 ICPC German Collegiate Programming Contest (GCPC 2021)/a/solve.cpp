#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int D = 62;

bool is_valid(ll n) {
    assert(n & 1);
    if (n == 1 || n == 3) return 1;
    
    if (~((1 + n) / 2) & 1) return 0;
    else return is_valid((1 + n) / 2);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    // TEST
    // for (ll n = 3; n <= 10'000'000; n += 2) {
    //     if (is_valid(n) != (__builtin_popcount(n - 1) == 1)) {
    //         cout << "n = " << n << '\n';
    //     }
    // }

    // for (ll n = 1; n <= 100'000; n += 2) {
    // cout << "n = " << n << ", ";

    auto fucking_popcount = [](const ll n) -> int {
        int ret = 0;
        for (int i = 0; i < 62; i++) {
            if ((1ll << i) & n) ret++;
        }
        return ret;
    };

    ll n; cin >> n;

    if (n == 1) {
        cout << 1 << '\n';
    } else {
        if (fucking_popcount(n - 1) == 1) {
            cout << 1 << '\n';
        } else {
            bool yes = 0;
            for (int i = 1; (1ll << i) < n; i++) {
                const ll rem = n - (1ll << i) - 1;
                if (fucking_popcount(rem) == 1) {
                    yes = 1;
                    cout << (1ll << i) + 1 << '\n';
                    break;
                }
            }
            if (!yes) cout << "impossible\n";
        }
    }
    // }
    
}