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

int flag;
struct Seg {
    vt<ll> t;

    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);

        for (int i = flag; i < flag + n; i++) cin >> t[i];
        for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void modify(int p, ll val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

struct Query1 {
    ll x, y;
};

struct Query2 {
    int l, r, idx;
};

int n, m;
vt<Query1> q1(1);
vt<Query2> q2[101010];
vt<pll> ans;

void input() {
    cin >> n;
    seg.build(n);

    cin >> m;
    FOR(m) {
        int op, x, y, z;
        cin >> op >> x >> y;
        if (op == 1) {
            q1.push_back({ x, y });
        }
        if (op == 2) {
            cin >> z;
            q2[x].push_back({ y, z, i });
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();    

    EACH(i, q2[0]) {
        ans.push_back({ i.idx, seg.query(i.l, i.r) });
    }

    FOR(i, 1, sz(q1)) {
        auto& it = q1[i];

        seg.modify(it.x, it.y);

        EACH(j, q2[i]) {
            ans.push_back({ j.idx, seg.query(j.l, j.r) });
        }
    }

    sort(all(ans));

    EACH(i, ans) cout << i.sc << '\n';

	return 0;
}