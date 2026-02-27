#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

ll ts2(ll b, ll c, ll ab, ll bc, ll ac, ll abc, const ll k, const ll used) {
    ll ret = 0;

    auto fuck = [&](ll &sum, ll &rem) {
        if (sum % k == 0) return;
        const ll both = min(k - sum % k, rem);
        sum += both, rem -= both;
    };

    ll l = 0, r = ab;
    while (l + 3 < r) {
        const ll mid1 = (2 * l + r) / 3;
        const ll mid2 = (l + 2 * r) / 3;

        ll sum_b1 = ab - mid1, sum_c1 = ac - (used - mid1);
        ll sum_b2 = ab - mid2, sum_c2 = ac - (used - mid2);
        if (sum_c1 < abc) {
            l = mid1;
            continue;
        }

        ll sum_left1 = abc, sum_left2 = abc;
        if (sum_c1 < 0) {
            sum_left1 += sum_c1;
            sum_c1 = 0;
        }
        if (sum_c2 < 0) {
            sum_left2 += sum_c2;
            sum_c2 = 0;
        }
        
        sum_b1 += b, sum_b2 += b;
        sum_c1 += c, sum_c2 += c;

        fuck(sum_b1, sum_left1);
        fuck(sum_c1, sum_left1);
        fuck(sum_b2, sum_left2);
        fuck(sum_c2, sum_left2);

        const ll res1 = (sum_b1 + k - 1) / k + (sum_c1 + k - 1) / k + (sum_left1 + k - 1) / k;
        const ll res2 = (sum_b2 + k - 1) / k + (sum_c2 + k - 1) / k + (sum_left1 + k - 1) / k;

        if (res1 >= res2) l = mid1;
        else r = mid2;
    }

    ll opt = INF;
    for (ll mid1 = l; mid1 <= r; mid1++) {
        ll sum_b1 = ab - mid1, sum_c1 = ac - (used - mid1);
        if (sum_c1 < abc) { continue; }

        ll sum_left1 = abc, sum_left2 = abc;
        if (sum_c1 < 0) {
            sum_left1 += sum_c1;
            sum_c1 = 0;
        }
        
        sum_b1 += b;
        sum_c1 += c;

        fuck(sum_b1, sum_left1);
        fuck(sum_c1, sum_left1);

        const ll res1 = (sum_b1 + k - 1) / k + (sum_c1 + k - 1) / k + (sum_left1 + k - 1) / k;
        opt = min(opt, res1);
    }

    return opt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        ll k; cin >> k;

        ll a, b, c, ab, bc, ac, abc;
        cin >> a >> b >> c >> ab >> bc >> ac >> abc;

        ll ans = 0;
        ans += a / k, a %= k;
        ans += b / k, b %= k;
        ans += c / k, c %= k;

        ll l = a, r = a + ab + ac + abc;
        while (l + 3 < r) {
            const ll mid1 = (2 * l + r) / 3;
            const ll mid2 = (l + 2 * r) / 3;

            const ll res1 = ts2(b, c, ab, bc, ac, abc, k, mid1 - a) + (mid1 + k - 1) / k;
            const ll res2 = ts2(b, c, ab, bc, ac, abc, k, mid2 - a) + (mid2 + k - 1) / k;
            if (res1 > res2) l = mid1;
            else r = mid2;
        }

        ll opt = INF;
        for (ll mid1 = l; mid1 <= r; mid1++) {
            const ll res1 = ts2(b, c, ab, bc, ac, abc, k, mid1 - a) + (mid1 + k - 1) / k;
            opt = min(opt, res1);
        }
        cout << opt + ans << '\n';
    }
}
