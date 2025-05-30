//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll a, x, MOD;

ll powuv(ll u, ll v) {
    if (v == 0) return 1;
    if (v == 1) return u % MOD;
    ll res = powuv(a, v / 2) % MOD;
    return res * res % MOD * (v & 1 ? u : 1) % MOD;
}

ll f(ll A, ll X) {
    if (X == 1) return 1;
    ll res = f(A, X / 2);
    ll ret = (res + res * powuv(A, X / 2)) % MOD;
    if (X & 1) {
        ret += powuv(A, X - 1);
        ret %= MOD;
    }
    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> a >> x >> MOD;
    cout << f(a, x) % MOD;

	return 0;
}