#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 202020;
constexpr int M = 202020;

int n, m;
ll l, x, y;
ll s[N], t[N];
ll p[M];

ld ans[M];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> l >> x >> y;
    for (int i = 1; i <= n; i++)
        cin >> s[i] >> t[i];
    for (int i = 1; i <= m; i++)
        cin >> p[i];
    
    vector<int> ord_n(n), ord_m(m);
    iota(all(ord_n), 1);
    iota(all(ord_m), 1);
    
    sort(all(ord_n), [&](int i, int j) {
        return s[i] < s[j];
    });
    sort(all(ord_m), [&](int i, int j) {
        return p[i] < p[j];
    });

    ld mn = 1e18;

    int j = 0;
    for (int i : ord_m) {
        while (j < sz(ord_n) && s[ord_n[j]] <= p[i]) {
            int idx = ord_n[j++];
            mn = min(mn, (ld)(t[idx] - s[idx]) / x + (ld)(l - t[idx]) / y);
        }

        ans[i] = min((ld)(l - p[i]) / y, mn);
    }

    cout << fixed;
    cout.precision(10);

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
}