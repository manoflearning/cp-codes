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

ll a, b, c;
ll x, y, z;

void cal(ll& ans, ll& u, ll& v) {
    ll mn = min(u, v);
    ans += mn;
    u -= mn, v -= mn;
}

void cal2(ll& ans, ll& u, ll& v) {
    ll mn = min(u, v / 3);
    ans += mn;
    u -= mn, v -= 3 * mn;
}

void cal3(ll& ans, ll& u, ll& v) {
    ll mn = min(u, v / 9);
    ans += mn;
    u -= mn, v -= 9 * mn;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> a >> b >> c;
    cin >> x >> y >> z;

    ll ans = 0;

    cal(ans, a, x);
    cal(ans, b, y);
    cal(ans, c, z);

    cal2(ans, b, x);
    cal2(ans, c, y);
    cal2(ans, a, z);

    cal3(ans, c, x);
    cal3(ans, a, y);
    cal3(ans, b, z);

    cout << ans;

	return 0;
}