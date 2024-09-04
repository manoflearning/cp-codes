#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int n;
vector<pll> a;

ll ternary_search(ll l, ll r, ll u_max, ll d_max) {
    while (r - l >= 3) {
        ll mid1 = (2 * l + r) / 3;
        ll mid2 = (l + 2 * r) / 3;

        ll res1 = max(u_max - 2 * mid1, d_max + 2 * mid1);
        ll res2 = max(u_max - 2 * mid2, d_max + 2 * mid2);

        if (res1 <= res2) r = mid2;
        else l = mid1;
    }
    int ret = -1;
    ll opt_val = INF;
    for (ll i = l; i <= r; i++) {
        ll res = max(u_max - 2 * i, d_max + 2 * i);
        if (res < opt_val) {
            ret = i;
            opt_val = res;
        }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.fr >> i.sc;
    }

    vector<ll> ys;
    for (auto& i : a)
        ys.push_back(i.sc);

    sort(all(ys));
    ys.erase(unique(all(ys)), ys.end());

    ll ans = INF;

    for (int i = 0; i < sz(ys); i++) {
        vector<pll> d, u;
        for (auto& j : a) {
            if (j.sc < ys[i]) d.push_back(j);
            else u.push_back(j);
        }

        ll u_max = -INF, d_max = -INF, ud_max = -INF;
        for (int i = 0; i < sz(d); i++) {
            for (int j = i + 1; j < sz(d); j++) {
                ll res = abs(d[i].fr - d[j].fr);
                res -= d[i].sc + d[j].sc;
                d_max = max(d_max, res);
            }
        }
        for (int i = 0; i < sz(u); i++) {
            for (int j = i + 1; j < sz(u); j++) {
                ll res = abs(u[i].fr - u[j].fr);
                res += u[i].sc + u[j].sc;
                u_max = max(u_max, res);
            }
        }
        for (int i = 0; i < sz(d); i++) {
            for (int j = 0; j < sz(u); j++) {
                ll res = abs(d[i].fr - u[j].fr);
                res += u[j].sc - d[i].sc;
                ud_max = max(ud_max, res);
            }
        }

        if (u_max != -INF && d_max != -INF) {
            ll h = ternary_search(ys[i - 1] + 1, ys[i], u_max, d_max);
            ans = min(ans, max({ u_max - 2 * h, d_max + 2 * h, ud_max }));
        }
        else if (u_max != -INF) {
            ans = min(ans, max(u_max - 2 * ys[i], ud_max));
        }
        else if (d_max != -INF) {
            ans = min(ans, max(d_max + 2 * (ys[i - 1] + 1), ud_max));
        }
        else ans = min(ans, ud_max);
    }

    cout << ans;
}