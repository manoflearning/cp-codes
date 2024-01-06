#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const double EPS = 1e-8;

struct Fraction {
    __int128_t n, d; // represent n/d

    Fraction(__int128_t N, __int128_t D) { n = N, d = D; reduce(); }
    Fraction(__int128_t N) { n = N, d = 1; }
    Fraction() { n = 0, d = 1; }

    __int128_t gcd(__int128_t a, __int128_t b) {
        if (b == 0) return a;
        else return gcd(b, a % b);
    }
    void reduce() {
        __int128_t g = gcd(n, d);
        n /= g, d /= g;
        if (d < 0) n *= -1, d *= -1;
    }

    bool operator<(const Fraction& rhs) const {
        return n * rhs.d < rhs.n * d;
    }
};

struct point {
	ll x, y;
	bool operator<(const point& rhs) const {
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
};

struct line {
    __int128_t a, b, c;
    int idx1, idx2;
    Fraction dist(const point& p) {
        Fraction ret;
        ret.n = (a * p.x + b * p.y + c) * (a * p.x + b * p.y + c);
        ret.d = (a * a + b * b);
        ret.reduce();
        return ret;
    }
};

int N;
vector<point> p;
vector<int> st;
vector<line> li;

void init() {
    p.clear();
    st.clear();
    li.clear();
}

void input() {
    cin >> N;
    if (N == 0) exit(0);
    p.resize(N);
    for (auto& i : p)
        cin >> i.x >> i.y;
}

ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
ll dist(const point& p1, const point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool cmp(const point& p1, const point& p2) {
    return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}
void grahamScan() {
	sort(p.begin(), p.end());
	sort(p.begin() + 1, p.end(), cmp);
	st.push_back(0);
	st.push_back(1);
	for (int next = 2; next < N; next++) {
		while (st.size() >= 2) {
			int first = st.back();
			st.pop_back();
			int second = st.back();
			if (ccw(p[second], p[first], p[next]) > 0) {
				st.push_back(first);
				break;
			}
		}
		st.push_back(next);
	}
}

void getLines() {
    for (int i = 0; i < sz(st); i++) {
        point u = p[st[i]], v = p[st[(i + 1) % sz(st)]];
        __int128_t a, b, c;
        a = (__int128_t)v.y - u.y, b = (__int128_t)u.x - v.x;
        c = -(a * u.x + b * u.y);
        li.push_back({ a, b, c, st[i], st[(i + 1) % sz(st)]});
    }
}

Fraction solve() {
    Fraction ret(5e8, 1);
    for (auto& i : st) {
        point v = p[i];
        for (auto& j : li) {
            if (j.idx1 == i || j.idx2 == i) continue;
            Fraction res = j.dist(v);
            if (res < ret) ret = res;
        }
    }
    return ret;
}

void print(Fraction res, int tt) {
    res.n *= 10'000;
    res.reduce();

    ll l = 0, r = 5e6;
    while (l < r) {
        ll mid = (l + r) / 2;

        if (mid * mid * res.d < res.n) l = mid + 1;
        else r = mid;
    }
    
    assert(l - sqrt((double)res.n / res.d) < 1);

    cout << fixed;
    cout.precision(2);
    cout << "Case " << tt << ": ";
    cout << (double)l / 100 + EPS << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int tt = 1; ; tt++) {
        init();

        input();

        grahamScan();

        getLines();

        Fraction res = solve();
        
        print(res, tt);
    }
}