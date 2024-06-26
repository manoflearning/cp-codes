#define _USE_MATH_DEFINES
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

struct vw {
    ll v, w;
};  

ll n, m, k;
vt<vw> a;

ll f(int idx) {
    if (idx == -1) return 0;

    ll x = (1ll << idx);

    vt<pll> res;
    FOR(n) {
        if (a[i].v & x) res.push_back({ a[i].w, i });
        else res.push_back({ x - a[i].v % x + a[i].w, i });
    }

    sort(all(res));

    ll cnt = 0;
    FOR(k) cnt += res[i].fr;
    
    if (cnt <= m) {
        EACH(i, res) {
            ll add = i.fr - a[i.sc].w;
            a[i.sc].v += add;
            a[i.sc].w += add;
        }

        return x + f(idx - 1);
    }
    else return f(idx - 1);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    a.resize(n);
    EACH(i, a) cin >> i.v;
    
    cout << f(32);

	return 0;
}