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
const int UB = 30;

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

        vector<ll> a(n), d(n);
        for (auto &i : a) cin >> i;

        ll ans = INF;

        int vis_cnt = 0;

        set<pair<ll, int>> st;
        for (int i = 0; i < n; i++) {
            d[i] = a[i] - a[(i + 1) % n];
            if (d[i] > 0) st.insert({d[i], i});
            ans = min(ans, a[i]);
        }

        while (!st.empty()) {
            if (st.rbegin()->fr == 0) break;
            if (ans == 0) break;

            auto [w, now] = *st.rbegin();

            cout << now << '\n';
            for (int i = 0; i < n; i++)
                cout << a[i] << ' ';
            cout << '\n';
            for (int i = 0; i < n; i++)
                cout << d[i] << ' ';
            cout << '\n';
            cout << '\n';

            int prv = (now + n - 1) % n;
            int pprv = (prv + n - 1) % n;
            int nxt = (now + 1) % n;

            st.erase({d[pprv], pprv});
            st.erase({d[prv], prv});
            st.erase({d[now], now});

            ll op_cnt = (w + 1) / 2;
            a[prv] = max(0ll, a[prv] - op_cnt);
            a[now] = max(0ll, a[now] - 2 * op_cnt);
            ans = min(ans, a[prv]);
            ans = min(ans, a[now]);

            d[pprv] = a[pprv] - a[prv];
            d[prv] = a[prv] - a[now];
            d[now] = a[now] - a[nxt];

            if (d[pprv] > 0) st.insert({d[pprv], pprv});
            if (d[prv] > 0) st.insert({d[prv], prv});
            if (d[now] > 0) st.insert({d[now], now});
        }

        ans = min(ans, a[0]);

        cout << ans << '\n';
    }
}
