#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 998'244'353;
constexpr int N = 202020;
constexpr int D = 17;

array<ll, N> lb{}, dep{};

ll power(ll x, ll y) {
    if (!y) return 1;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

ll ncr(int n, int r) {
    if (r < 0 || n < r) return 0;
    r = min(r, n - r);
    ll ret = 1;
    for (int i = 1; i <= r; i++) {
        ret = ret * (n - r + i) % MOD * power(i, MOD - 2) % MOD;
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    for (int i = 1; i < N; i++) {
        ll lowbit = 1;
        while (!(lowbit & i)) lowbit <<= 1;

        lb[i] = lowbit;
    }

    for (int i = N - 1; i >= 1; i--) {
        int j = i + lb[i];
        if (N <= j) continue;
        dep[i] = dep[j] + 1;
    }

    int tc; cin >> tc;
    while (tc--) {
        int n;
        ll cnt;
        cin >> n >> cnt;

        vector<ll> b(n + 1);
        for (int i = 1; i <= n; i++) cin >> b[i];

        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++) {
            ll acc = 0;
            for (int j = i - lb[i] + 1; j < i; j++) {
                int delta = dep[j] - dep[i];
                acc += a[j] * ncr(delta + cnt - 1, delta) % MOD;
                acc %= MOD;
            }

            a[i] = (b[i] - acc + MOD) % MOD;

            cout << a[i] << ' ';
        }
        cout << '\n';
    }
}
