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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        sort(all(a));
        a.erase(unique(all(a)), a.end());

        vector<bool> dp(sz(a) + 1);
        dp[sz(a)] = 0;
        for (int i = sz(a) - 1; i >= 0; i--) {
            if (a[i] - (i == 0 ? 0 : a[i - 1]) > 1) dp[i] = 1;
            else dp[i] = !dp[i + 1];
        }

        cout << (dp[0] ? "Alice" : "Bob") << '\n';
    }
}
