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
	if (U.sc == -1 || V.sc == -1) return { -1, -1 };
	if (U.sc == 1) return V;
	if (V.sc == 1) return U;
	ll g = gcd(U.sc, V.sc);
	ll l = U.sc * V.sc / g;
	if ((V.fr - U.fr) % g) return { -1, -1 };

	ll u = U.sc / g, v = V.sc / g;
	ll mul = (V.fr - U.fr) / g;
	mul = mul * minv(u % v, v) % v;
	
	pll ret = { mul * U.sc + U.fr, l };
	ret.fr %= ret.sc, ret.fr = (ret.fr + ret.sc) % ret.sc;
	return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	while (tc--) {
		int m, n, x, y;
		cin >> m >> n >> x >> y;
		pll ans = crt({ x - 1, m }, { y - 1, n });
		cout << (ans.fr == -1 ? ans.fr : ans.fr + 1) << '\n';
	}
}