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
        t.resize(flag << 1);
    }
    void modify(int p, ll val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

struct Query {
    ll op, x, y;
};

int n, m;
vt<ll> a, c;
vt<Query> q;

void input() {
    cin >> n >> m;
    a.resize(n + 1);
    FOR(n) cin >> a[i + 1];
    q.resize(m);
    EACH(i, q) {
        cin >> i.op >> i.x;
        if (i.op ^ 4) cin >> i.y;
    }
}

int Hash(ll x) {
    return lower_bound(all(c), x) - c.begin() + 1;
}

void cc() {
    vt<ll> b = a;
    FOR(i, 1, n + 1)
        c.push_back(b[i]);
    
    EACH(i, q) {
        if (i.op == 1) {
            b[i.x] += i.y;
            c.push_back(b[i.x]);
        }
        else if (i.op == 2) {
            b[i.x] -= i.y;
            c.push_back(b[i.x]);
        }
        else if (i.op == 3) {
            c.push_back(i.x);
            c.push_back(i.y);
        }
    }

    sort(all(c));
    c.erase(unique(all(c)), c.end());
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

    cc();

    seg.build(sz(c));
    
    FOR(i, 1, n + 1)
        seg.modify(Hash(a[i]), 1);

    EACH(i, q) {
        if (i.op == 1) {
            seg.modify(Hash(a[i.x]), -1);
            a[i.x] += i.y;
            seg.modify(Hash(a[i.x]), 1);
        }
        else if (i.op == 2) {
            seg.modify(Hash(a[i.x]), -1);
            a[i.x] -= i.y;
            seg.modify(Hash(a[i.x]), 1);
        }
        else if (i.op == 3) {
            cout << seg.query(Hash(i.x), Hash(i.y)) << '\n';
        }
        else if (i.op == 4) {
            int l = 1, r = sz(c);
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (seg.query(mid, sz(c)) < i.x) r = mid - 1;
                else l = mid;
            }
            cout << c[l - 1] << '\n';
        }
    }

	return 0;
}