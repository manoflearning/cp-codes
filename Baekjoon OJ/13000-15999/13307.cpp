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

struct point {
    ll x, y;
    bool operator<(const point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

int n;
point p[3030], p2[3030];
pll ans[1010];

void input() {
    cin >> n;
    FOR(3 * n) {
        ll x, y;
        cin >> x >> y;
        p[i].x = x, p[i].y = y;
    }
}

ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

bool cmp(const int& a, const int& b) { return p[a] < p[b]; }

//point o = { 0, 0 };
bool cmp2(const int& a, const int& b){
    //return ccw(o, p[a], p[b]) < 0;
    return p2[b].x * p2[a].y < p2[a].x * p2[b].y;
}

int getB(vt<int>& a) {
    sort(all(a), cmp);

    // calculate lower hull
    vt<int> dh;
	dh.push_back(a[0]);
	dh.push_back(a[1]);
	for (int next = 2; next < sz(a); next++) {
		while (dh.size() >= 2) {
			int first = dh.back();
			dh.pop_back();
			int second = dh.back();
			if (ccw(p[second], p[first], p[a[next]]) > 0) {
				dh.push_back(first);
				break;
			}
		}
		dh.push_back(a[next]);
	}

	// calculate upper hull
    vt<int> uh;
	uh.push_back(a[sz(a) - 1]);
	uh.push_back(a[sz(a) - 2]);
	for (int next = sz(a) - 3; next >= 0; next--) {
		while (uh.size() >= 2) {
			int first = uh.back();
			uh.pop_back();
			int second = uh.back();
			if (ccw(p[second], p[first], p[a[next]]) > 0){
				uh.push_back(first);
				break;
			}
		}
		uh.push_back(a[next]);
	}

    int ret = 0, x = -1;
    EACH(i, dh) if (i < n) { ret = 1; x = i; }
    EACH(i, uh) if (i < n) { ret = 1; x = i; }

    if (ret) {
        FOR(sz(a)) {
            if (a[i] == x) { swap(a[0], a[i]); break; }
        }
    }

    return ret;
}

void dc(vt<int>& a) {
    if (a.empty()) return;

    int bit = getB(a);
    FOR(i, 1, sz(a)) {
        p2[a[i]].x = p[a[i]].x - p[a[0]].x;
        p2[a[i]].y = p[a[i]].y - p[a[0]].y;
    }
    //o = p[a[0]];
    sort(a.begin() + 1, a.end(), cmp2);
    //EACH(i, a) cout << i << ' ';
    //cout << '\n';
    if (bit) {
        int res = 0, idx1 = -1, idx2 = -1;
        FOR(i, 1, sz(a)) {
            if (a[i] < n) res += 2;
            else res -= 1;
            
            if (res == -1 && idx1 == -1) idx1 = i;
            if (res == -2 && idx2 == -1) idx2 = i;
        }
        
        ans[a[0]] = { a[idx1], a[idx2] };

        vt<int> b, c, d;
        FOR(i, 1, idx1) b.push_back(a[i]);
        FOR(i, idx1 + 1, idx2) c.push_back(a[i]);
        FOR(i, idx2 + 1, sz(a)) d.push_back(a[i]);

        dc(b); dc(c); dc(d);
    }
    else {
        int res = 0, idx = -1;
        FOR(i, sz(a)) {
            if (a[i] < n) res += 2;
            else res -= 1;
            
            if (res == 0 && idx == -1) idx = i;
        }

        vt<int> b, c;
        for (int i = 0; i < sz(a); i++) {
            if (1 <= i && i <= idx) b.push_back(a[i]);
            else c.push_back(a[i]);
        }
        assert(sz(a) > sz(b));
        assert(sz(a) > sz(c));
        dc(b); dc(c);
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

    vt<int> a;
    FOR(3 * n) a.push_back(i);
    dc(a);

    FOR(i, n) cout << ans[i].fr - n + 1 << ' ' << ans[i].sc - n + 1 << '\n';

	return 0;
}