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

constexpr int MAXN = 202020;

ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
  return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

  // Preprocessing in O(N)
  fac[0] = fac[1] = inv[1] = 1;
  facInv[0] = facInv[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    fac[i] = i * fac[i - 1] % MOD;
    inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
    if (inv[i] < 0) inv[i] += MOD;
    facInv[i] = facInv[i - 1] * inv[i] % MOD;
  }

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);

        int sum = 0;
        bool violate0 = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sum += a[i];
            if ((n - 1) / 2 < i && a[i]) violate0 = 1;
        }

        if (violate0 || (sum != n)) {
            cout << 0 << '\n';
            continue;
        }

        ll ans = 1;

        int rem = ((n & 1) ? 1 : 2);
        for (int i = (n - 1) / 2; i >= 0; i--) {
            // cout << i << ' ' << rem << '\n';
            if (rem < a[i]) {
                ans = 0;
                break;
            }

            ans = (ans * binom(rem, a[i])) % MOD;
            rem -= a[i];

            if (i > 0) rem += 2;
        }

        cout << ans << '\n';
    }
}
