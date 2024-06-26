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

struct Kyo {
    char op;
    ll p, q;
};

int n, m;
int sy, sx, ey, ex, mxk;
vt<string> a;
vt<Kyo> kyo;

void init() {

}

void input() {
    cin >> n >> m;
    a.resize(n);
    EACH(i, a) cin >> i;

    FOR(n) FOR(j, m) {
        auto it = a[i][j];
        if (it == 'A') sy = i, sx = j;
        else if (it == 'B') ey = i, ex = j;
        else if ('0' <= it && it <= '9') mxk = max(mxk, it - '0');
    }
        
    kyo.resize(mxk + 1);
    EACH(i, kyo) {
        int du;
        cin >> du >> i.op >> i.p >> i.q;
    }
}

struct wyx {
    ll w, y, x;
    bool operator<(const wyx& rhs) const {
        return w > rhs.w;
    }
};

int dist[25][25];

int bfs() {
    FOR(25) FOR(j, 25) dist[i][j] = INF;

    queue<pii> q;
    q.push({ sy, sx });
    dist[sy][sx] = 0;

    while (sz(q)) {
        int y = q.front().fr, x = q.front().sc;
        q.pop();

        if (y == ey && x == ex) return dist[y][x];

        FOR(4) {
            int ny = y + dy[i], nx = x + dx[i];
            if ()
        }
    }

    return INF;
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

	while (1) {
        init();

        input();

        int ans = bfs();
        if (ans == INF) cout << "impossible\n";
        else cout << ans << '\n';
    }

	return 0;
}