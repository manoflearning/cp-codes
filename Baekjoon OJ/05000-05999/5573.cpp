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
const int dy[] = { 1, 0 };
const int dx[] = { 0, 1 };

int n, r, c;
int a[1010][1010]; 
int ind[1010][1010];
ll dp[1010][1010];

void buildGraph() {
    FOR(r) FOR(j, c) {
        if (i > 0 && j > 0) ind[i][j] = 2;
        else if (i > 0) ind[i][j] = 1;
        else if (j > 0) ind[i][j] = 1;
    }
}

void topologicalSort() {
	queue<pii> q;
	q.push({ 0, 0 });
    dp[0][0] = n;

	while (sz(q)) {
		int y = q.front().fr, x = q.front().sc;
        q.pop();

        if (y == r || x == c) continue;

        vt<ll> w;
        w.resize(2);
        w[0] = (a[y][x] ? dp[y][x] / 2 : (dp[y][x] + 1) / 2);
		w[1] = (a[y][x] ? (dp[y][x] + 1) / 2 : dp[y][x] / 2);

		FOR(2) {
            int ny = y + dy[i], nx = x + dx[i];
            dp[ny][nx] += w[i];
            ind[ny][nx]--;
			if (ind[ny][nx] == 0) q.push({ ny, nx });
		}
	}
}

void getAns() {
    int y = 0, x = 0;
    while (y < r && x < c) {
        int idx = -1;
        if (dp[y][x] & 1) idx = a[y][x];
        else idx = !a[y][x];
        y += dy[idx], x += dx[idx];
    }

    cout << y + 1 << ' ' << x + 1 << '\n';
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

	cin >> r >> c >> n;
    FOR(r) FOR(j, c) cin >> a[i][j];

    buildGraph();

    topologicalSort();

    getAns();

	return 0;
}