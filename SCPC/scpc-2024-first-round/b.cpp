// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        int n; cin >> n;
        vector<int> a(n);
        for (auto& i : a) cin >> i;

        sort(all(a));

        ll ans = 0;
        for (int i = 0; i < n / 4; i++) {
            ans += a[n - i - 1] - a[i];
        }

        cout << 2 * ans << '\n';

        cout << flush;
    }
}