#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int m; cin >> m;

        int mx = 0;
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            mx = max(mx, x);
        }

        a[i] = m, b[i] = mx;
    }

    ll mx = 0;
    for (auto &i : b) mx = max(mx, i);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] != mx) {
            ans += (mx - b[i]) * a[i];
        }
    }

    cout << ans;
}