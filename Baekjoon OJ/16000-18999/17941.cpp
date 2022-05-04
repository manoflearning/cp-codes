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

struct Seg {
	int flag;  // array size
	vector<ll> t;

	void build(int N, vt<int>& a) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);

		for (int i = flag; i < flag + N; i++) t[i] = a[i - flag + 1];
		for (int i = flag - 1; i >= 1; i--) t[i] = max(t[i << 1], t[i << 1 | 1]);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r) {
		return query(l, r, 1, 1, flag);
	}
	ll query(int l, int r, int n, int nl, int nr) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg[505][2];

int n, m;
vt<vt<int>> a;

void input() {
    cin >> n >> m;
    a.resize(n + 1, vt<int>(m + 1));
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            cin >> a[i][j];
        }
    }
}

void makingSeg() {
    FOR(i, 1, n + 1) {
        seg[i][0].build(m, a[i]);
    }
    FOR(i, 1, m + 1) {
        vt<int> b;
        FOR(j, n + 1) b.push_back(a[j][i]);
        seg[i][1].build(n, b);
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

    makingSeg();

    int q; cin >> q;

    // O(q * k * (log(max(n, m)) + log(k)))
    while (q--) {
        int x, y, r, c, k, d;
        cin >> x >> y >> r >> c >> k >> d;

        multiset<int> s;

        int res = 0;
        if (d == 1) {
            FOR(i, x, x + r) {
                s.insert(seg[i][0].query(y, y + c - 1));
            }

            res = *(--s.end());

            FOR(i, k - 1) {
                s.insert(seg[x + r + i][0].query(y, y + c - 1));
                s.erase(seg[x + i][0].query(y, y + c - 1));
                res ^= *(--s.end());
            }
        }
        if (d == 2) {
            FOR(i, x, x + r) {
                s.insert(seg[i][0].query(y, y + c - 1));
            }

            res = *(--s.end());

            FOR(i, k - 1) {
                s.insert(seg[x - i - 1][0].query(y, y + c - 1));
                s.erase(seg[x + r - i - 1][0].query(y, y + c - 1));
                res ^= *(--s.end());
            }
        }
        if (d == 3) {
            FOR(i, y, y + c) {
                s.insert(seg[i][1].query(x, x + r - 1));
            }

            res = *(--s.end());

            FOR(i, k - 1) {
                s.insert(seg[y + c + i][1].query(x, x + r - 1));
                s.erase(seg[y + i][1].query(x, x + r - 1));
                res ^= *(--s.end());
            }
        }
        if (d == 4) {
            FOR(i, y, y + c) {
                s.insert(seg[i][1].query(x, x + r - 1));
            }

            res = *(--s.end());

            //cout << *(--s.end()) << '\n';

            FOR(i, k - 1) {
                s.insert(seg[y - i - 1][1].query(x, x + r - 1));
                s.erase(seg[y + c - i - 1][1].query(x, x + r - 1));
                res ^= *(--s.end());
                //cout << *(--s.end()) << '\n';
            }
        }

        cout << res << '\n';
    }

	return 0;
}