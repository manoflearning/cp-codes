#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

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

        vector<ll> a(n), b(n), c(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i] >> c[i];
            if (b[i] > a[i] + c[i]) b[i] = a[i] + c[i];
        }

        ll cnt_div1 = 0;
        for (int i = 0; i < n; i++) {
            if (b[i] > c[i]) {
                ll res = min(a[i], b[i] - c[i]);
                cnt_div1 += res;
                a[i] -= res;
                b[i] -= res;
            }
        }

        ll div2_ub = 0;
        for (int i = 0; i < n; i++) {
            div2_ub += min(b[i], c[i]);
        }

        if (div2_ub <= cnt_div1) {
            cout << div2_ub << '\n';
            continue;
        }

        ll l = cnt_div1, r = n * (ll)1e9;
        while (l < r) {
            ll mid = (l + r + 1) >> 1;

            ll div1 = cnt_div1;
            vector<ll> tmp_b = b;

            for (int i = 0; i < n; i++) {
                ll res = min({a[i], tmp_b[i], mid - div1});
                div1 += res;
                tmp_b[i] -= res;
            }

            ll div2 = 0;
            for (int i = 0; i < n; i++) {
                div2 += min({tmp_b[i], c[i]});
            }

            if (div1 == mid && div1 <= div2) l = mid;
            else r = mid - 1;
        }

        cout << l << '\n';
    }
}
