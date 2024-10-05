#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    freopen("subsonic_subway_input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ": ";

        int n; cin >> n;
        vector<ll> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i] >> b[i];

        ll x = 0, y = 1;
        for (int i = 1; i <= n; i++) {
            if (x * b[i] < y * i) {
                x = i, y = b[i];
            }
        }

        bool is_valid = 1;
        for (int i = 1; i <= n; i++) {
            if (i * y < x * a[i] || x * b[i] < i * y) is_valid = 0;
        }

        cout << fixed;
        cout.precision(8);

        if (is_valid) cout << (double)x / y << '\n';
        else cout << -1 << '\n';
    }
}
