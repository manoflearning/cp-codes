#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 998'244'353;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;

        vector<int> v(n);
        for (auto &i : v) cin >> i;

        ll ans = 1;
        for (int i = 0; i < k; i++) {
            ans = ans * (i + 1) % MOD;
        }
        for (int i = k; i < n; i++) {
            if (v[i - k] == -1) ans = ans * (i + 1) % MOD;
            if (v[i - k] == +0) ans = ans * (k + 1) % MOD;
        }

        if (v[0] != -1 && v[0] != 0) ans = 0;
        for (int i = n - k; i < n; i++)
            if (v[i] != -1 && v[i] != 0) ans = 0;

        cout << ans << '\n';
    }
}
