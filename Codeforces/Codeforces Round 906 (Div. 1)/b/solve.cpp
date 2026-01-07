#pragma GCC optimize("O3")
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

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    int tc; cin >> tc;
    while (tc--) {
        int n; ll c;
        cin >> n >> c;

        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        ll acc = a[1];
        vector<bool> vis(n + 1);
        int ans = n - 1;

        vector<int> ord(n - 1);
        iota(all(ord), 2);
        sort(all(ord), [&](int i, int j) {
            return a[i] - i * c > a[j] - j * c;
        });

        while (1) {
            bool is_modified = 0;
            for (int i : ord) {
                if (vis[i]) continue;
                if (acc + a[i] >= i * c) {
                    acc += a[i];
                    vis[i] = 1;
                    ans--;
                    is_modified = 1;
                }
            }
            if (!is_modified)  break;
        }
        cout << (ans == 0 ? "Yes" : "No") << '\n';
    }
}