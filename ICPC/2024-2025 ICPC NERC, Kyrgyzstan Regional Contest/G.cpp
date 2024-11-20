#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll bs(ll s, ll d, ll t, ll e, ll mxd) {
    ll l = 0, r = mxd;
    while (l < r) {
        ll mid = (l + r + 1) >> 1;
        ll op1 = mxd - mid, op2 = mid / 2;
        ll res = s + op1 * d + op2 * d;
        if (res >= e) l = mid;
        else r = mid - 1;
    }
    ll op1 = mxd - l, op2 = l;
    return op1 * 4 * t + op2 * t;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll s1, s2, d1, d2, t1, t2, e;
    cin >> s1 >> s2 >> d1 >> d2 >> t1 >> t2 >> e;

    ll mxd = max({(e - s1 + d1 - 1) / d1, (e - s2 + d2 - 1) / d2, 0ll});

    ll ans = 0;
    ans += bs(s1, d1, t1, e, mxd);
    ans += bs(s2, d2, t2, e, mxd);

    cout << mxd << '\n' << ans;
}
