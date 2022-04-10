#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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
const ll INF = 1e18 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct point {
	ll x, px, idx; //px, py는 기준점에서의 상대적인 위치
    double y, py;
	point() : point(0, 0, 0, 0, 0) {}
	point(ll sx, double sy, int sidx) : point(sx, sy, 0, 0, sidx) {}
    point(ll sx, double sy, ll spx, double spy, int sidx) : x(sx), y(sy), px(spx), py(spy), idx(sidx) {}
};

struct valh {
    double val;
    ll h;
};

int n, m;
vt<ll> a, b;
vt<valh> r, c;
double psumR[505050], psumC[505050];

void input();
void makingRC();
ll ccw(point& a, point& b, point& c);
void convex(vt<valh>& a);
ll f();

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
    
    makingRC();
    
    if (sz(r) > 2) convex(r);
    if (sz(c) > 2) convex(c);
    
    cout << f();    

	return 0;
}

void input() {
    cin >> n >> m;
    a.resize(n + 1);
    b.resize(m + 1);
    EACH(i, a) cin >> i;
    EACH(i, b) cin >> i;
}

void makingRC() { // cost[x, y] := r[x] + c[y]
    r.resize(n + 1);
    c.resize(m + 1);

    FOR(n) r[n - i].val = a[i] - a[i + 1];
    FOR(m) c[i + 1].val = b[i + 1] - b[i];
}

ll ccw(point& a, point& b, point& c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

void convex(vt<valh>& a) {
    vt<double> psum(sz(a));
    FOR(i, 1, sz(psum))
        psum[i] = a[i].val + psum[i - 1];

    vt<point> p;
    FOR(i, 1, sz(a))
        p.push_back({ i, psum[i], i });

    //
    FOR(i, 1, sz(p)) {
		p[i].px = p[i].x - p[0].x;
		p[i].py = p[i].y - p[0].y;
	}

    vt<int> st;
    st.push_back(0);
    st.push_back(1);
    FOR(i, 2, sz(p)) {
		while (st.size() >= 2) {
			int first = st.back();
			st.pop_back();
			int second = st.back();
			if (ccw(p[second], p[first], p[i]) > 0) {
				st.push_back(first);
				break;
			}
		}
		st.push_back(i);
	}

    //
    vt<valh> aa;
    
    FOR(sz(st)) {
        int j = st[i];

        aa.push_back({ 0, 0 });
        
        FOR(k, p[j].idx, (j < sz(st) - 1 ? p[st[j + 1]].idx : sz(a))) {
            aa.back().val += a[k].val;
            aa.back().h++;
        }
    }

    EACH(i, a) cout << i.val << ' ';
    cout << '\n';
    
    a.clear();
    a.push_back({ 0, 1 });
    EACH(i, aa) {
        double x = i.val / i.h;
        
        while (i.h) {
            a.push_back({ x, 1 });
            i.h--;
        }
    }

    EACH(i, a) cout << i.val << ' ';
    cout << '\n';
}

ll f() {
    FOR(i, 1, n + 1)
        psumR[i] = r[i].val + psumR[i - 1];
    FOR(i, 1, m + 1)
        psumC[i] = c[i].val + psumC[i - 1];
    
    double res = 0;
    int prv = n;
    FOR(i, 1, n + 1) {
        if (r[i].val + c[1].val > 0) {
            prv = i - 1;
            break;
        }
    }
    //cout << r[1].val + c[1].val << ' ';
    res += psumR[prv] + prv * c[1].val;
    //cout << prv << ' ' << psumR[prv] + prv * c[1].val << '\n';

    FOR(y, 2, m + 1) {
        FOR(x, prv, 0, -1) {
            if (r[x].val + c[y].val <= 0) {
                prv = x;
                break;
            }
        }
        if (prv > 0 && r[prv].val + c[y].val > 0) prv = 0;
        res += psumR[prv] + prv * c[y].val;
        //cout << prv << ' ' << psumR[prv] + prv * c[y].val << '\n';
    }
    
    return n * b[0] + m * a[n] + (ll)res;
}