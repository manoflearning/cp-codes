// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const ll INF = 1e18;

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        int n; cin >> n;

        vector<ll> a(n + 1);
        vector<ll> ps0(n + 1), ps1(n + 1), ps2(n + 1);
        vector<ll> pps0(n + 1), pps1(n + 1), pps2(n + 1);

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            
            ps0[i] = a[i] - 1 + ps0[i - 1];
            ps1[i] = ps0[i] - 1;
            ps2[i] = ps0[i] - 2;
            
            pps0[i] = abs(ps0[i]) + pps0[i - 1];
            pps1[i] = abs(ps1[i]) + pps1[i - 1];
            pps2[i] = abs(ps2[i]) + pps2[i - 1];
        }

        ll ans = 0;
        if (ps0[n] == 0) {
            ans = pps0[n];
        } else if (ps0[n] == 1) {
            ll opt = INF;
            for (int i = 0; i < n; i++) {
                opt = min(opt, pps0[i] - pps1[i]);
            }
            ans = pps1[n] + opt;
        } else if (ps0[n] == 2) {
            ll opt = INF;

            ll mn = 0;
            for (int i = 1; i < n; i++) {
                opt = min(opt, pps1[i] - pps2[i] + mn);
                mn = min(mn, pps0[i] - pps1[i]);
            }

            ans = pps2[n] + opt;
        }

        cout << ans << '\n';

        cout << flush;
    }
}