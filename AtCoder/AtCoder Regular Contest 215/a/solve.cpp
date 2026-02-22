#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n;
        ll k, l;
        cin >> n >> k >> l;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        sort(all(a));

        vector<ll> b;
        for (int i = 0; i + 1 < n; i++) {
            if (a[i] < a[i + 1]) b.push_back(a[i + 1] - a[i]);
        }
        sort(b.rbegin(), b.rend());

        ll ans = 0;

        ll lm = a.front(), rm = l - a.back();
        
        ans = max(ans, max(lm, rm) + (k - 1) * (lm + rm));
        
        ll acc = 0;
        for (int i = 0; i < sz(b); i++) {
            if (i + 1 > k) break;

            const ll w = b[i] / 2;

            lm += w, rm += w, acc += w;

            ll res = 0;
            res += acc;
            res += (k - i - 1 > 0 ? max(lm, rm) : 0);
            res += (k - i - 2 > 0 ? (k - i - 2) * (lm + rm) : 0);

            ans = max(ans, res);
        }

        cout << ans << '\n';
    }

    return 0;
}
