#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 9090909;

ll fac[MAXN], inv[MAXN], facInv[MAXN];

ll binom(int n, int r) {
    if (n < r) return 0;
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

ll powxy(ll x, ll y) { 
    if (y == 0) return 1;
    if (y == 1) return x;

    ll res = powxy(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    // Preprocessing in O(N)
	fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fac[i] = i * fac[i - 1] % MOD;

		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		cout << "Case #" << tt << ": ";

        ll n, k;
        cin >> n >> k;
       
        ll c, w;
        cin >> c >> w;

        ll small = 0, same = 0, sum = 0;
        for (int i = 0; i < n - 1; i++) {
            ll x, y;
            cin >> x >> y;
            if (y < w) small += x;
            if (y == w) same += x;
            sum += x;
        }

        if (small + same + c <= k) {
            cout << 0 << '\n';
            continue;
        }
        
        ll p = binom(small + same + c, k + 1) - binom(small, k + 1);
        ll q = binom(sum + c, k + 1);
        
        p = (p + MOD) % MOD;
        q = (q + MOD) % MOD;
        
        p = (p * c) % MOD;
        q = (q * (same + c)) % MOD;
        
        cout << (p * powxy(q, MOD - 2) % MOD + MOD) % MOD << '\n';
	}

	return 0;
}