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

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll n, a[202020];

// Fermat’s little theorem
// A / B = A * B^{p - 2} (mod p)
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

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];

		ll p = -1, q = n * (n - 1) / 2 % MOD;

		ll cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i] == 0) cnt++; 
		}

		ll res = 0;
		for (int i = 1; i <= cnt; i++) {
			if (a[i] == 1) res++;
		}

		p = res * res % MOD;

		cout << p * powxy(q, MOD - 2) % MOD << '\n';
	}

	return 0;
}