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

ll n, cnt[55];
vt<pll> a;

ll cal() {
    ll ret = 1;
    for (int i = 0; i < sz(a); i++) {
        for (int j = 0; j < cnt[i]; j++) {
            ret *= a[i].fr;
        }
    }
    return ret;
}

// Find phi(x) in sqrt(x).
ll phi(ll x) {
    vector<pll> p;

    // Factorization in O(sqrt(x)).
    for (ll i = 2; i <= sqrt(x); i++) {
        ll res = 1;
        while (x % i == 0) {
            x /= i, res *= i;
        }
        if (res > 1) p.push_back({ res, i });
    }
    if (x > 1) p.push_back({ x, x });

    // Find phi(x).
    // phi(p^k) = p^{k-1} * (p - 1) for any prime number p.
    ll ret = 1;
    for (auto& i : p) {
        ret *= (i.fr / i.sc) * (i.sc - 1);
    }

    return ret;
}

ll bt(int idx) {
    if (idx == sz(a)) {
        ll val = cal();
        //cout << val << ' ' << phi(val) << '\n';
        if (val * phi(val) == n) return val;
        else return INF;
    }

    ll ret = INF;
    for (int i = 0; i <= a[idx].sc; i++) {
        cnt[idx] = i;
        ret = min(ret, bt(idx + 1));
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

	cin >> n;

    ll x = n;
    for (int i = 2; i <= sqrt(x); i++) {
        ll cnt = 0;
        while (x % i == 0) {
            x /= i, cnt++;
        }
        if (cnt > 0) a.push_back({ i, cnt });
    }
    if (x > 1) a.push_back({ x, 1 });

    ll ans = bt(0);
    if (ans == INF) cout << -1;
    else cout << ans;

	return 0;
}