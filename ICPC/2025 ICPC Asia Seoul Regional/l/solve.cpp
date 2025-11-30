#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int N = 2020202;
constexpr int Q = 2020202;
constexpr ll INF = 1e18;

int n, q;
ll l[N], r[N], y[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> q;

    ll mnr = INF, mxl = -INF;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i] >> y[i];
        mxl = max(mxl, l[i]);
        mnr = min(mnr, r[i]);
    }

    for (int i = 1; i <= q; i++) {
        ll p; cin >> p;

        ll ans = max({0ll, p - mnr, mxl - p});

        cout << ans << '\n';
    }
}