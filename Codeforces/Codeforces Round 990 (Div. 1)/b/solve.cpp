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

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        int smin = a[n - 1], nmin = INF;

        vector<bool> vis(n);
        for (int i = n - 1; i >= 0; i--) {
            if (smin < a[i]) {
                a[i]++;
                vis[i] = 1;
                nmin = min(nmin, a[i]);
            } else {
                smin = min(smin, a[i]);
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            if (!vis[i] && nmin < a[i]) {
                a[i]++;
            }
        }

        sort(all(a));

        for (auto &i : a)
            cout << i << ' ';
        cout << '\n';
    }
}
