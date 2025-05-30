#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}
ll minv(ll x, ll y) {
    if (x == 0 && y == 1) return 0;
    if (x == 1) return 1;
    return y - minv(y % x, x) * y / x;
}

// x = U.fr (mod U.sc)
// x = V.fr (mod V.sc)
// returns solutions as x = ret.fr (mod ret.sc)
// if no solution, returns { -1, -1 }
pll crt(pll U, pll V) {
    if (U.sc == -1 || V.sc == -1) return {-1, -1};
    if (U.sc == 1) return V;
    if (V.sc == 1) return U;
    ll g = gcd(U.sc, V.sc);
    ll l = U.sc * V.sc / g;
    // (U and V have a solution) iff (U.fr = U.sc (mod gcd(U.sc,V.sc)))
    // also the solution is unique in the range [0, lcm(U.sc,V.sc)).
    if ((V.fr - U.fr) % g) return {-1, -1};

    ll u = U.sc / g, v = V.sc / g;
    ll mul = (V.fr - U.fr) / g;
    mul = mul * minv(u % v, v) % v;

    pll ret = {mul * U.sc + U.fr, l};
    ret.fr %= ret.sc, ret.fr = (ret.fr + ret.sc) % ret.sc;
    return ret;
}
pll solvingSystemOfLinearCongruence(const vector<pll> &a) {
    if (a.size() == 1) return a[0];
    pll ret = crt(a[0], a[1]);
    for (int i = 2; i < a.size(); i++) ret = crt(ret, a[i]);
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll n, x, y, u_x, u_y;
        cin >> n >> x >> y >> u_x >> u_y;

        {
            ll g = gcd(u_x, u_y);
            u_x /= g, u_y /= g;
        }
        
        ll g_x = gcd(u_x, n);
        ll g_y = gcd(u_y, n);
        if (-x % g_x || -y % g_y) {
            cout << -1 << '\n';
            continue;
        }

        ll n_x = n / g_x, n_y = n / g_y;

        auto [t, _] = solvingSystemOfLinearCongruence({
            {-(x / g_x) * minv((u_x / g_x), n_x), n_x}, 
            {-(y / g_y) * minv((u_y / g_y), n_y), n_y}
        });

        if (t == -1) {
            cout << -1 << '\n';
            continue;
        }

        ll t_x = (x + u_x * t) / n, t_y = (y + u_y * t) / n;

        ll ans = 0;
        ans += t_x - 1;
        ans += t_y - 1;
        ans += (t_x + t_y) / 2;
        ans += abs(t_x - t_y) / 2;

        cout << ans << '\n';
    }
}
