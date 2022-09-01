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

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

ll a, as, ae;
ll b, bs, be;
ll c, cs, ce;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> a >> as >> ae;
    cin >> b >> bs >> be;
    cin >> c >> cs >> ce;

    ll g = lcm(a, lcm(b, c));

    ll ans = -1;
    for (ll x = 0; x < g; ) {
        ll ma = x % a, mb = x % b, mc = x % c;
        
        ll nxt = 1;
        int bit = 1;

        if (ma < as) nxt = max(nxt, as - ma), bit = 0;
        if (ae < ma) nxt = max(nxt, a - ma + as), bit = 0;
        if (mb < bs) nxt = max(nxt, bs - mb), bit = 0;
        if (be < mb) nxt = max(nxt, b - mb + bs), bit = 0;
        if (mc < cs) nxt = max(nxt, cs - mc), bit = 0;
        if (ce < mc) nxt = max(nxt, c - mc + cs), bit = 0;

        if (bit) {
            ans = x;
            break;
        }

        x += nxt;
    }

    cout << ans;

	return 0;
}

/*#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

ll a, as, ae;
ll b, bs, be;
ll c, cs, ce;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> a >> as >> ae;
    cin >> b >> bs >> be;
    cin >> c >> cs >> ce;

    ll g = lcm(a, lcm(b, c));

    ll ans = -1;
    for (ll x = 0; x < g; x += a) {
        for (ll y = as; y <= ae; ) {
            ll val = x + y;
            bool res = 1;

            ll mb = val % b, mc = val % c, mx = 1;
            if (mb < bs) mx = max(mx, bs - mb);
            else if (be < mb) mx = max(mx, b - mb + bs);
            else if (mc < cs) mx = max(mx, cs - mc);
            else if (ce < mc) mx = max(mx, c - mc + cs);
            else {
                ans = val, x = g;
                break;
            }

            y += mx;
        }
    }

    cout << ans;

	return 0;
}*/