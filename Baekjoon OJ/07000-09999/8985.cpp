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

int flag;  // array size
struct Seg {  // 1-based
	vector<ll> t;

	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);

		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

const int MAX = 500001;

struct Point {
    ll x, y;
};

int n, k, mxx;
ll psum[505050];
vt<Point> point;
vt<pii> line[505050];

void input() {
    cin >> n;
    point.resize(n);
    EACH(i, point) {
        cin >> i.x >> i.y;
        i.x++, i.y++;
        mxx = max<ll>(mxx, i.x);
    }
    cin >> k;
    FOR(k) {
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        sx++, sy++, ex++, ey++;
        psum[sx]++;
    }
}

pair<double, ll> dc(int nl, int nr, int prvHeight) {
    pair<double, ll> ret;

    int holeCnt = psum[nr] - psum[nl - 1];
    int currHeight = seg.query(nl, nr);

    if (holeCnt > 0) ret.fr += (double)(currHeight - prvHeight) * (nr - nl + 1) / holeCnt;
    else ret.sc += (ll)(currHeight - prvHeight) * (nr - nl + 1);
    
    vt<pii> currLine(lower_bound(all(line[currHeight]), pii(nl, 0)), lower_bound(all(line[currHeight]), pii(nr + 1, 0)));
    // debugging
    /*cout << "At [" << nl - 1 << ", " << nr << "),\n";
    cout << "We have " << holeCnt << " holes,\n" << "and minimum y is " << currHeight - 1 << '\n';
    if (holeCnt == 0) cout << "we have (" << ret.sc << " + x) water left (x >= 0)\n";
    cout << '\n';
    cout << "Intervals\n";
    EACH(i, currLine) cout << "[" << i.fr - 1 <<  ", " << i.sc - 1 << ")\n";
    cout << "are floor";
    cout << '\n' << '\n';*/

    vt<pii> next;
    FOR(i, sz(currLine)) {
        if (i == 0) {
            next.push_back({ nl, currLine[i].fr - 1 });
        }
        else {
            next.push_back({ currLine[i].sc, currLine[i].fr - 1 });
        }
    }
    if (sz(currLine)) next.push_back({ currLine.back().sc, nr });

    pair<double, ll> res;
    EACH(i, next) {
        if (i.fr > i.sc) continue;
        pair<double, ll> res2 = dc(i.fr, i.sc, currHeight);
        res.fr = max(res.fr, res2.fr);
        res.sc += res2.sc;
    }
    ret.fr += res.fr, ret.sc += res.sc;
    return ret;
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

    FOR(i, 1, mxx + 1)
        psum[i] += psum[i - 1];

    seg.build(mxx);

    FOR(i, sz(point) - 1) {
        if (point[i].y == point[i + 1].y) {
            FOR(j, point[i].x, point[i + 1].x) seg.modify(j, point[i].y);
            line[point[i].y].push_back({ point[i].x, point[i + 1].x });
        }
    }

    pair<double, ll> ans = dc(1, mxx - 1, 1);

    cout << fixed;
    cout.precision(2);
    cout << ans.fr << '\n' << ans.sc;

	return 0;
}