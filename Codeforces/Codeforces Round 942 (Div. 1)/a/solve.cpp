#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; ll k;
        cin >> n >> k;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        ll l = 1, r = (ll)2e12;
        while (l < r) {
            ll mid = (l + r + 1) >> 1;
            
            ll acc = 0;
            for (auto &i : a) {
                if (i < mid) acc += mid - i;
            }

            if (acc <= k) l = mid;
            else r = mid - 1;
        }

        ll acc = 0;
        for (auto &i : a) {
            if (i < l) {
                acc += l - i;
                i = l;
            }
        }

        ll cnt_lp1 = 0;
        for (auto &i : a) {
            if (l < i) cnt_lp1++;
        }
        cnt_lp1 += (k - acc);

        ll ans = (l - 1) * n + 1 + cnt_lp1;
        cout << ans << '\n';
    }
}
