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
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

struct idxop {
    int idx; char op;
    bool operator<(const idxop& rhs) const {
        return idx < rhs.idx;
    }
};
struct ridxop {
    int idx; char op;
    bool operator<(const ridxop& rhs) const {
        return idx > rhs.idx;
    }
};

int n, m, k, q;
vt<idxop> r[303030], c[303030];
vt<ridxop> rr[303030], rc[303030];
pll ans[4][303030];

void init() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 303030; j++) {
            ans[i][j] = { -1, -1 };
        }
    }
}

void input() {
    cin >> n >> m >> k >> q;
    for (int i = 0; i < k; i++) {
        int y, x; char op;
        cin >> y >> x >> op;
        r[y].push_back({ x, op });
        c[x].push_back({ y, op });
        rr[y].push_back({ x, op });
        rc[x].push_back({ y, op });
    }
}

void pre() {
    for (int i = 0; i < 303030; i++) {
        sort(all(r[i]));
        sort(all(c[i]));
        sort(all(rr[i]));
        sort(all(rc[i]));
    }
}

pll query(int y, int x, int d, ll len) {
    if (d == 0) {
        idxop du = { x, '*' };
        int p = upper_bound(all(r[y]), du) - r[y].begin();
        if (p == sz(r[y])) return { 0, 0 };

        auto it = r[y][p];
        int nx = it.idx;
        if (it.op == '!') {
            pll res = query(y, nx, d, len + abs(nx - x));
            return { res.fr + 1, len + abs(nx - x) + res.sc };
        }
        else if (it.op == '\\') {
            return query(y, nx, 2, len + abs(nx - x));
        }
        else if (it.op == '/') {
            return query(y, nx, 3, len + abs(nx - x));
        }
    }
    else if (d == 1) {
        ridxop du = { x, '*' };
        int p = upper_bound(all(rr[y]), du) - rr[y].begin();
        if (p == sz(rr[y])) return { 0, 0 };

        auto it = rr[y][p];
        int nx = it.idx;
        if (it.op == '!') {
            pll res = query(y, nx, d, len + abs(nx - x));
            return { res.fr + 1, len + abs(nx - x) + res.sc };
        }
        else if (it.op == '\\') {
            return query(y, nx, 3, len + abs(nx - x));
        }
        else if (it.op == '/') {
            return query(y, nx, 2, len + abs(nx - x));
        }
    }
    else if (d == 2) {
        idxop du = { y, '*' };
        int p = upper_bound(all(c[x]), du) - c[x].begin();
        if (p == sz(c[x])) return { 0, 0 };

        auto it = c[x][p];
        int ny = it.idx;
        if (it.op == '!') {
            pll res = query(ny, x, d, len + abs(ny - y));
            return { res.fr + 1, len + abs(ny - y) + res.sc };
        }
        else if (it.op == '\\') {
            return query(ny, x, 0, len + abs(ny - y));
        }
        else if (it.op == '/') {
            return query(ny, x, 1, len + abs(ny - y));
        }
    }
    else if (d == 3) {
        ridxop du = { y, '*' };
        int p = upper_bound(all(rc[x]), du) - rc[x].begin();
        if (p == sz(rc[x])) return { 0, 0 };

        auto it = rc[x][p];
        int ny = it.idx;
        if (it.op == '!') {
            pll res = query(ny, x, d, len + abs(ny - y));
            return { res.fr + 1, len + abs(ny - y) + res.sc };
        }
        else if (it.op == '\\') {
            return query(ny, x, 1, len + abs(ny - y));
        }
        else if (it.op == '/') {
            return query(ny, x, 0, len + abs(ny - y));
        }
    }
}

int opidx(char op) {
    if (op == 'U') return 0;
    else if (op == 'D') return 1;
    else if (op == 'L') return 2;
    else if (op == 'R') return 3;
}

void solve() {
    while (q--) {
        char op; int st;
        cin >> op >> st;
        
        auto& it = ans[opidx(op)][st];
        if (it.fr != -1) {
            cout << it.fr << ' ' << it.sc << '\n';
            continue;
        }

        pll res = { 0, 0 };
        if (op == 'D') res = query(n + 1, st, 3, 0);
        if (op == 'U') res = query(0, st, 2, 0);
        if (op == 'L') res = query(st, 0, 0, 0);
        if (op == 'R') res = query(st, m + 1, 1, 0);

        it = res;
        cout << it.fr << ' ' << it.sc << '\n';
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();

	input();

    pre();

    solve();

	return 0;
}