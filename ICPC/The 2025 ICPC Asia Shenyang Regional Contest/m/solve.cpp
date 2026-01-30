#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

array<int, 8> a{}, b{};
array<int, 16> t{};

ld bt(int i) {
    if (i == 0) return t[1] == 0;

    ld ret = 0;

    const int u = t[i << 1], v = t[i << 1 | 1];

    t[i] = u;
    ret += bt(i - 1) * a[u] / (a[u] + b[v]);
    t[i] = v;
    ret += bt(i - 1) * b[v] / (a[u] + b[v]);

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    for (int i = 0; i < 8; i++) cin >> a[i] >> b[i];

    // ll fac8 = 1;
    // for (int i = 2; i <= 8; i++) fac8 = i * fac8;

    vector<int> ord(8);
    iota(all(ord), 0);

    ld ans{};
    do {
        for (int i = 8; i <= 15; i++) t[i] = ord[i - 8];
        ld res = bt(7);
        ans = max(ans, res);
    } while (next_permutation(all(ord)));

    cout << fixed;
    cout.precision(10);

    cout << ans << '\n';
}
