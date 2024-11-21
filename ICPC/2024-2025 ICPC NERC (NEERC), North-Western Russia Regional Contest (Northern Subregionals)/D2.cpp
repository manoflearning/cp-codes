#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;
const int UB = 100;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll ans = INF;
        for (auto &i : a) ans = min(ans, i);

        for (int cyc = 0; cyc < UB; cyc++) {
            for (int i = n - 1; i >= 0; i--) {
                ll w = a[i] - a[(i + 1) % n];
                int now = i;
                if (w <= 0) continue;
                if (ans == 0) { cyc = UB, i = n; break; }

                int prv = (now + n - 1) % n;
                int pprv = (prv + n - 1) % n;

                ll op_cnt = (w + 1) / 2;
                a[prv] = max(0ll, a[prv] - op_cnt);
                a[now] = max(0ll, a[now] - 2 * op_cnt);
                ans = min(ans, a[prv]);
                ans = min(ans, a[now]);
            }

            ll mna = INF, mxa = -INF;
            for (int i = 0; i < n; i++) {
                mna = min(mna, a[i]);
                mxa = max(mxa, a[i]);
            }
            if (mna == mxa) break;

            if (cyc == UB - 1) ans = 0;
        }

        cout << ans << '\n';
    }
}
