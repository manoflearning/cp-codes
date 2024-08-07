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

int r, c, a[255][255];
int dist[255][255];

int bfs() {
    FOR(255) FOR(j, 255) dist[i][j] = -1;

    queue<pii> q;
    FOR(r) FOR(j, c) {
        if (a[i][j]) {
            q.push({ i, j });
            dist[i][j] = 0;
        }
    }

    int ret = 0;

    while (sz(q)) {
        int y = q.front().fr, x = q.front().sc;
        q.pop();

        ret = max(ret, dist[y][x]);

        FOR(4) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || r <= ny || nx < 0 || c <= nx) continue;
            if (dist[ny][nx] != -1) continue;
            q.push({ ny, nx });
            dist[ny][nx] = dist[y][x] + 1;
        }
    }

    return ret;
}

int isP(int d) {
    int mxSum = -INF, mnSum = INF, mxDiff = -INF, mnDiff = INF;
    FOR(r) FOR(j, c) {
        if (dist[i][j] > d) {
            mxSum = max(mxSum, i + j);
            mnSum = min(mnSum, i + j);
            mxDiff = max(mxDiff, i - j);
            mnDiff = min(mnDiff, i - j);
        }
    }

    FOR(r) FOR(j, c) {
        int res = 0;
        res = max(res, abs(mxSum - (i + j)));
        res = max(res, abs(mnSum - (i + j)));
        res = max(res, abs(mxDiff - (i - j)));
        res = max(res, abs(mnDiff - (i - j)));
        if (res <= d) return 1;
    }
    return 0;
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

	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        cout << "Case #" << tt << ": ";

        cin >> r >> c;
        FOR(r) {
            string s; cin >> s;
            FOR(j, c) a[i][j] = s[j] - '0';
        }

        int l = 0, r = bfs();
        while (l < r) {
            int mid = (l + r) >> 1;
            if (isP(mid)) r = mid;
            else l = mid + 1;
        }

        cout << l << '\n';
    }

	return 0;
}