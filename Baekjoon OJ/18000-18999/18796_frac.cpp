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
const ll INF = 1e15 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct frac {
    ll a, b;

    ll gcd(ll x, ll y) {
	    if (y == 0) return x;
	    else return gcd(y, x % y);
    }
    void trim() {
        ll g = gcd(a, b);
        a /= g, b /= g;
        if (b < 0) a *= -1, b *= -1;
    }
};

bool operator<(frac x, frac y) {
    x.trim(); y.trim();
    return x.a * y.b < y.a * x.b;
}
bool operator<=(frac x, frac y) {
    x.trim(); y.trim();
    return x.a * y.b <= y.a * x.b;
}
bool operator>(frac x, frac y) {
    x.trim(); y.trim();
    return x.a * y.b > y.a * x.b;
}
bool operator<(frac x, int y) {
    x.trim();
    return x.a < y * x.b;
}
frac operator+(frac x, frac y) {
    x.trim(); y.trim();
    frac ret;
    ret.b = x.b * y.b;
    ret.a = y.b * x.a + x.b * y.a;
    ret.trim();
    return ret;
}
frac operator*(frac x, frac y) {
    x.trim(); y.trim();
    frac ret;
    ret.b = x.b * y.b;
    ret.a = x.a * y.a;
    ret.trim();
    return ret;
}
frac operator*(int x, frac y) {
    y.trim();
    frac ret;
    ret.b = y.b;
    ret.a = x * y.a;
    ret.trim();
    return ret;
}

int n, m;
vt<ll> a, b;
vt<frac> r, c;

void input() {
    cin >> n >> m;
    a.resize(n + 1);
    b.resize(m + 1);
    EACH(i, a) cin >> i;
    EACH(i, b) cin >> i;
}

void makingRC() {
    r.resize(n + 1);
    c.resize(m + 1);
    r[0] = c[0] = { 0, 1 };
    FOR(n) r[n - i] = { a[i] - a[i + 1], 1 };
    FOR(m) c[i + 1] = { b[i + 1] - b[i], 1 };
}

struct point {
    ll x, y;
    int idx;
    bool operator<(const point& O) const {
		return x < O.x;
	}
};

ll ccw(point& a, point& b, point& c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

void convexHull(vt<frac>& a) {
    vt<ll> psum(sz(a));
    FOR(i, 1, sz(psum))
        psum[i] = a[i].a + psum[i - 1];

    vt<point> p;
    p.push_back({ 0, 0, 0 });
    FOR(i, 1, sz(psum))
        p.push_back({ i, psum[i], i });

    vt<int> st;
    st.push_back(0);
    st.push_back(1);

    FOR(i, 2, sz(p)) {
        while (sz(st) >= 2) {
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

    vt<frac> aa;
    aa.push_back({ 0, 1 });
    
    FOR(i, 1, sz(st)) {
        int now = p[st[i]].idx, prv = p[st[i - 1]].idx;
        ll val = psum[now] - psum[prv];
        
        FOR(j, now - prv)
            aa.push_back({ val, now - prv });
    }
    a = aa;
}

ll f() {
    vt<frac> psumr(sz(r));
    psumr[0] = { 0, 1 };
    FOR(i, 1, sz(psumr))
        psumr[i] = r[i] + psumr[i - 1];

    frac res = { 0, 1 }, zero = { 0, 1 };
    
    int prv = n;
    FOR(x, 1, n + 1) {
        if (r[x] + c[1] > zero) {
            prv = x - 1; break;
        }
    }
    res = res + psumr[prv] + prv * c[1];
    
    FOR(y, 2, m + 1) {
        FOR(x, prv, 0, -1) {
            if (r[x] + c[y] <= zero) { 
                prv = x; break;
            }
        }
        if (prv > 0 && r[prv] + c[y] > zero) prv = 0;
        
        res = res + psumr[prv] + prv * c[y];
    }

    return n * b[0] + m * a[n] + res.a / res.b;
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

    makingRC();

    convexHull(r);
    convexHull(c);

    cout << f();

	return 0;
}