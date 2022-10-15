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
vt<int> cy;
ll w;
vt<vt<pll>> yy;

vt<vt<vt<ll>>> dp;

void init() {
    n = 0;
    p.clear();
    cy.clear();
    w = 0;
    yy.clear();
    dp.clear();
}

void input() {
    cin >> n >> w;
    p.resize(n);
    EACH(i, p)
        cin >> i.x >> i.y >> i.c;
}

void cc() {
    cy.push_back(-INF);

    EACH(i, p) {
        cy.push_back(i.y);
    }

    sort(all(cy));
    cy.erase(unique(all(cy)), cy.end());

    EACH(i, p) {
        i.y = lower_bound(all(cy), i.y) - cy.begin();
    }
}

ll f(int y, int idx, int dir) {
    ll& ret = dp[y][idx][dir];
    if (ret != -1) return ret;
    if (y == 0) return ret = 0;

    ret = yy[y][idx].sc;
    ll c = yy[y][idx].sc;
    
    if (idx + 1 < sz(yy[y]) && dir == 1) {
        ret = max(ret, c + f(y, idx + 1, 1));
    }
    if (idx > 0 && dir == 0) {
        ret = max(ret, c + f(y, idx - 1, 0));
    }

    int x = yy[y][idx].fr;

    int nidx = sz(yy[y - 1]) - 1;
    int nx = yy[y - 1][nidx].fr;
    if (x == nx) {
        ret = max(ret, c + f(y - 1, nidx, dir));
        ret = max(ret, c + f(y - 1, nidx, !dir) - w);
    }
    if (x < nx) {
        if (dir) {
            ret = max(ret, c + f(y - 1, nidx, 1));
            ret = max(ret, c + f(y - 1, nidx, 0) - w);
        }
        else {
            ret = max(ret, c + f(y - 1, nidx, 1) - w);
            ret = max(ret, c + f(y - 1, nidx, 0) - 2 * w);
        }
    }
    if (nx < x) {
        if (!dir) {
            ret = max(ret, c + f(y - 1, nidx, 0));
            ret = max(ret, c + f(y - 1, nidx, 1) - w);
        }
        else {
            ret = max(ret, c + f(y - 1, nidx, 0) - w);
            ret = max(ret, c + f(y - 1, nidx, 1) - 2 * w);
        }
    }
    
    nidx = 0;
    nx = yy[y - 1][nidx].fr;
        
    if (x == nx) {
        ret = max(ret, c + f(y - 1, nidx, dir));
        ret = max(ret, c + f(y - 1, nidx, !dir) - w);
    }
    if (x < nx) {
        if (dir) {
            ret = max(ret, c + f(y - 1, nidx, 1));
            ret = max(ret, c + f(y - 1, nidx, 0) - w);
        }
        else {
            ret = max(ret, c + f(y - 1, nidx, 1) - w);
            ret = max(ret, c + f(y - 1, nidx, 0) - 2 * w);
        }
    }
    if (nx < x) {
        if (!dir) {
            ret = max(ret, c + f(y - 1, nidx, 0));
            ret = max(ret, c + f(y - 1, nidx, 1) - w);
        }
        else {
            ret = max(ret, c + f(y - 1, nidx, 0) - w);
            ret = max(ret, c + f(y - 1, nidx, 1) - 2 * w);
        }
    }

    //cout << y << ' ' << idx << ' ' << dir << '\n';
    //cout << ret << '\n';
    
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

        cc();

        yy.resize(sz(cy) + 1);
        yy[0].push_back({ -INF, 0 });
        yy[0].push_back({ INF, 0 });
        yy[sz(cy)].push_back({ 0, 0 });

        EACH(i, p) {
            yy[i.y].push_back({ i.x, i.c });
        }

        dp.resize(sz(cy) + 1);
        //dp[0].resize(2, vt<vt<ll>>(2, vt<ll>(2, -1)));
        //dp[sz(cy)].resize(1, vt<vt<ll>>(2, vt<ll>(2, -1)));

        FOR(sz(cy) + 1) {
            sort(all(yy[i]));
            dp[i].resize(sz(yy[i]), vt<ll>(2, -1));
        }

        cout << f(sz(cy), 0, 1) << '\n';
	}

	return 0;
}

/*
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
vt<int> cy;
ll w;
vt<vt<pll>> yy;

vt<vt<vt<vt<ll>>>> dp;

void init() {
    n = 0;
    p.clear();
    cy.clear();
    w = 0;
    yy.clear();
    dp.clear();
}

void input() {
    cin >> n >> w;
    p.resize(n);
    EACH(i, p)
        cin >> i.x >> i.y >> i.c;
}

void cc() {
    cy.push_back(-INF);

    EACH(i, p) {
        cy.push_back(i.y);
    }

    sort(all(cy));
    cy.erase(unique(all(cy)), cy.end());

    EACH(i, p) {
        i.y = lower_bound(all(cy), i.y) - cy.begin();
    }
}

ll f(int y, int idx, int dir, int turn) {
    ll& ret = dp[y][idx][dir][turn];
    if (ret != -1) return ret;
    if (y == 0) return ret = 0;

    ret = yy[y][idx].sc;
    ll c = yy[y][idx].sc;

    if (idx + 1 < sz(yy[y])) {
        if (dir) ret = max(ret, c + f(y, idx + 1, 1, turn));
        if (!dir && !turn) ret = max(ret, c + f(y, idx + 1, 1, 1) - w); 
    }
    if (idx > 0) {
        if (!dir) ret = max(ret, c + f(y, idx - 1, 0, turn));
        if (dir && !turn) ret = max(ret, c + f(y, idx - 1, 0, 1) - w);
    }

    int x = yy[y][idx].fr;
    pll du = { x, -INF };
    int nidx = lower_bound(all(yy[y - 1]), du) - yy[y - 1].begin();
    
    if (nidx < sz(yy[y - 1])) {
        int nx = yy[y - 1][nidx].fr;
        if (x == nx) ret = max(ret, c + f(y - 1, nidx, dir, 0));
        if (x < nx) {
            if (dir) ret = max(ret, c + f(y - 1, nidx, 1, 0));
            else ret = max(ret, c + f(y - 1, nidx, 1, 0) - w);
        }
    }
    
    if (nidx > 0) {
        nidx--;
        int nx = yy[y - 1][nidx].fr;
        
        if (!dir) ret = max(ret, c + f(y - 1, nidx, 0, 0));
        else ret = max(ret, c + f(y - 1, nidx, 0, 0) - w);
    }

    cout << y << ' ' << idx << ' ' << dir << ' ' << turn << '\n';
    cout << ret << '\n';
    
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

        cc();

        yy.resize(sz(cy) + 1);
        yy[0].push_back({ 0, 0 });
        yy[0].push_back({ INF, 0 });
        yy[sz(cy)].push_back({ 0, 0 });

        EACH(i, p) {
            yy[i.y].push_back({ i.x, i.c });
        }

        dp.resize(sz(cy) + 1);
        //dp[0].resize(2, vt<vt<ll>>(2, vt<ll>(2, -1)));
        //dp[sz(cy)].resize(1, vt<vt<ll>>(2, vt<ll>(2, -1)));

        FOR(sz(cy) + 1) {
            sort(all(yy[i]));
            dp[i].resize(sz(yy[i]), vt<vt<ll>>(2, vt<ll>(2, -1)));
        }

        if (tt == 2) {
            //cout << f(4, 0, 1, 0) << '\n';
            //cout << f(3, 0, 1, 0) << '\n';
            //cout << f(3, 1, 1, 0) << '\n';
            //cout << f(2, 1, 1, 0) << '\n';
        }
        cout << f(sz(cy), 0, 1, 0) << '\n';
	}

	return 0;
}*/