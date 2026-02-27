#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

constexpr ll INF = 4e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<ll> a(n), d(n);
        for (auto &i : a) cin >> i;
        for (auto &i : d) cin >> i;

        vector<ll> l(m);
        for (auto &i : l) cin >> i;

        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            return d[i] > d[j];
        });

        ll ub = INF;
        vector<pll> st;
        for (int i : ord) {
            const ll lb = min(ub, d[i]) - a[i];
            st.push_back({lb, a[i]});
            ub = lb;
        }

        reverse(all(st));

        ll now = 0;
        vector<ll> res;
        int j = 0;
        for (int i = 0; i < m; i++) {
            while (j < n && now + l[i] > st[j].first) {
                now = now + st[j].second;
                j++;
            }

            res.push_back(now + l[i]);
            now += l[i];
        }

        while (q--) {
            ll t; cin >> t;

            const int ans = upper_bound(all(res), t) - res.begin();
            cout << ans << ' ';
        }
        cout << '\n';
    }
}
