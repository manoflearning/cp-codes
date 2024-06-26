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

struct Point {
    int x, y;
    ll c;
};

int n;
vt<Point> p;
ll w;

void init() {

}

void input() {
    cin >> n >> w;
    p.resize(n);
    for (auto& i : p)
        cin >> i.x >> i.y >> i.c;
}

vt<int> per;
int vi[11];

ll cal() {
    for (int i = 0; i + 1 < sz(per); i++) {
        int u = per[i], v = per[i + 1];
        if (p[u].y < p[v].y) return 0;
    }

    ll ret = 0;

    ll x = 0, bit = 1;
    for (int i = 0; i < sz(per); i++) {
        auto it = p[per[i]];
        if (x < it.x && !bit) {
            bit = !bit, ret -= w;
        }
        else if (it.x < x && bit) {
            bit = !bit, ret -= w;
        }
        x = it.x;
        ret += it.c;
    }

    return ret;
}

ll f() {
    if (sz(per) == n) return cal();

    ll ret = cal();
    for (int i = 0; i < n; i++) {
        if (vi[i]) continue;
        
        vi[i] = 1;
        per.push_back(i);
        
        ret = max(ret, f());

        vi[i] = 0;
        per.pop_back();
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

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
		cout << "Case #" << tt << ": ";

        init();

        input();
        
        cout << f() << '\n';
	}

	return 0;
}