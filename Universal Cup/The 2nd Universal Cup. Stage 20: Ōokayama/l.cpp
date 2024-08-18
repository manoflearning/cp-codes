#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const char MATCH[] = { '*', 'T', 'T', 'P', 'C' };

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
	if (U.sc == -1 || V.sc == -1) return { -1, -1 };
	if (U.sc == 1) return V;
	if (V.sc == 1) return U;
	ll g = gcd(U.sc, V.sc);
	ll l = U.sc * V.sc / g;
	// (U and V have a solution) iff (U.fr = U.sc (mod gcd(U.sc,V.sc)))
	// also the solution is unique in the range [0, lcm(U.sc,V.sc)).
	if ((V.fr - U.fr) % g) return { -1, -1 };

	ll u = U.sc / g, v = V.sc / g;
	ll mul = (V.fr - U.fr) / g;
	mul = mul * minv(u % v, v) % v;
	
	pll ret = { mul * U.sc + U.fr, l };
	ret.fr %= ret.sc, ret.fr = (ret.fr + ret.sc) % ret.sc;
	return ret;
}

ll n;
string s[5];
vector<pll> eqs[5], peqs[8];

void get_peqs(int i, int j, int k, ll x) {
    for (auto& eq1 : peqs[i]) {
        for (auto& eq2 : peqs[j]) {
            auto res = crt(eq1, eq2);
            if (res.fr == -1) continue;
            if (x < res.fr) continue;
            peqs[k].push_back(res);
        }
    }
    peqs[i].clear();
    peqs[i].shrink_to_fit();
    peqs[j].clear();
    peqs[j].shrink_to_fit();
}

ll f(ll x) {
    peqs[5].clear();
    peqs[6].clear();
    peqs[7].clear();
    for (int i = 1; i <= 4; i++)
        for (auto& j : eqs[i])
            if (j.fr <= x) peqs[i].push_back(j);

    get_peqs(1, 2, 5, x);
    get_peqs(3, 4, 6, x);
    get_peqs(5, 6, 7, x);

    ll ret = 0;
    for (auto& [p, q] : peqs[7]) {
        if (x < p) continue;
        ll cnt = (x - p) / q + 1;
        ret += cnt;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    cin >> s[1] >> s[2] >> s[3] >> s[4];

    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < sz(s[i]); j++) {
            if (s[i][j] == MATCH[i])
                eqs[i].push_back({ j, sz(s[i]) });
        }
    }

    ll l = 0, r = 1e18;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (f(mid) < n) l = mid + 1;
        else r = mid;
    }
    if (f(l) != n) { cout << -1; return 0; }
    cout << l + 1;
}