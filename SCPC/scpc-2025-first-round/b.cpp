#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        int n; ll l;
        cin >> n >> l;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        sort(all(a));

        cout << "Case #" << tt << endl;

        if (n == 1) {
            cout << a[0] + min(a[0], l - a[0]) << endl;
            continue;
        }

        vector<ll> psum(n), ssum(n + 1);
        psum[0] = 2 * a[0];
        for (int i = 1; i < n; i++) {
            psum[i] = 2 * a[i] + psum[i - 1];
        }
        ssum[n - 1] = 2 * (l - a[n - 1]);
        for (int i = n - 2; i >= 0; i--) {
            ssum[i] = 2 * (l - a[i]) + ssum[i + 1];
        }

        ll ans = psum[n - 1];
        for (int i = 0; i < n; i++) {
            ll res = 0;
            if (i - 1 >= 0) res += psum[i - 1];
            res += l;
            if (i + 1 < n) res += ssum[i + 1];
            ans = min(ans, res);
        }

        cout << ans << endl;
    }
}
