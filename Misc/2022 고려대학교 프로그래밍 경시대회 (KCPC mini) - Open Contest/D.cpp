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
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll n, k, a, b;

ll binom(int n, int r) {
    if (r < 0 || n < r) return 0;

	r = min(r, n - r);
	ll ret = 1;
	for (ll i = 1; i <= r; i++) {
		ret *= n + 1 - i;
		ret /= i;
	}
	return ret;
}

ll cal(ll x) {
    ll ret = 0;

    ll cnt = 0;
    for (int i = 60; i >= 0; i--) {
        ll bit1 = n & (1ll << i);
        ll bit2 = x & (1ll << i);
        
        if (bit2) {
            if (bit1 == 0) ret += binom(i, k - cnt);
            else ret += binom(i, k - cnt - 1);
        }

        if (bit1 ^ bit2) cnt++;
    }
    if (cnt == k) ret++;

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
    
	cin >> n >> k >> a >> b;
    cout << cal(b) - cal(a - 1);
    
	return 0;
}