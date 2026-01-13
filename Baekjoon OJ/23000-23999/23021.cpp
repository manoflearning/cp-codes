#pragma GCC optimize("Ofast")
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

constexpr int MOD = 1e9 + 7;
constexpr int N = 18, M = 18;

ll fac[N + 1];

int n, m;
ll x, lb, ub;
vector<ll> a, b;

vector<ll> dp_n[N + 1], dp_m[M + 1];

void init() {
    for (int i = 0; i <= N; i++) {
        dp_n[i].clear();
        dp_m[i].clear();
    }
}

void input() {
    cin >> n >> m >> x >> lb >> ub;
    a.assign(n, 0);
    b.assign(m, 0);
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    fac[0] = fac[1] = 1;
    for (int i = 2; i <= N; i++) {
        fac[i] = i * fac[i - 1] % MOD;
    }

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        for (int bit = 0; bit < (1 << n); bit++) {
            ll sum = 0;
            for (int i = 0; i < n; i++) {
                if (bit & (1 << i)) sum += a[i];
            }
            dp_n[__popcount(bit)].push_back(sum);
        }
        for (int bit = 0; bit < (1 << m); bit++) {
            ll sum = 0;
            for (int i = 0; i < m; i++) {
                if (bit & (1 << i)) sum += b[i];
            }
            dp_m[__popcount(bit)].push_back(sum);
        }
        for (int i = 0; i <= N; i++) {
            // sort(all(dp_n[i]));
            sort(all(dp_m[i]));
        }

        ll ans = 0;

        for (int p = 0; p <= n; p++) {
            for (const auto &k_n : dp_n[p]) {
                for (int q = max(0, p - 1); q <= min(m, p + 1); q++) {
                    const ll dist = k_n + (p + q - 1) * x;
                    if (dist > ub) continue;

                    ll psum = 0;
                    int idx_r = upper_bound(all(dp_m[q]), ub - dist) - dp_m[q].begin();

                    if (idx_r == 0) continue;
                    idx_r--;
                    psum += idx_r;

                    int idx_l = lower_bound(all(dp_m[q]), lb - dist) - dp_m[q].begin();
                    psum -= idx_l - 1;

                    ll cnt = 1;
                    cnt = cnt % MOD * fac[p] % MOD;
                    cnt = cnt * psum % MOD * fac[q] % MOD;
                    cnt = cnt * (p == q ? 2 : 1) % MOD;

                    ans = (ans + cnt) % MOD;
                }
            }
        }

        cout << ans << '\n';
    }
}
