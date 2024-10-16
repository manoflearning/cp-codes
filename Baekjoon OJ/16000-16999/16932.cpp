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

int n, m;
int a[1010][1010];
int num[1010][1010], numCnt = 1;
int vi[1010][1010], siz[1010 * 1010];

int dfs(int y, int x) {
    int ret = 1;
    num[y][x] = numCnt;
    vi[y][x] = 1;
    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
        if (!a[ny][nx] || vi[ny][nx]) continue;
        ret += dfs(ny, nx);
    }
    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    bool is0 = 0;
	cin >> n >> m;
    FOR(n) FOR(j, m) {
        cin >> a[i][j];
        if (!a[i][j]) is0 = 1;
    }

    if (!is0) {
        cout << n * m - 1;
        return 0;
    }

    int ans = 0;

    FOR(n) FOR(j, m) {
        if (a[i][j] && !vi[i][j]) {
            siz[numCnt] = dfs(i, j); 
            ans = max(ans, siz[numCnt]);
            numCnt++;
        }
    }
    
    FOR(n) FOR(j, m) {
        if (a[i][j]) continue;

        vt<int> res;
        FOR(k, 4) {
            int ny = i + dy[k], nx = j + dx[k];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
            if (!a[ny][nx]) continue;
            res.push_back(num[ny][nx]);
        }

        //cout << i << ' ' << j << ' ' << sz(res) << '\n';

        sort(all(res));
        res.erase(unique(all(res)), res.end());

        int sum = 1;
        EACH(k, res) sum += siz[k];

        ans = max(ans, sum);
    }

    cout << ans;

	return 0;
}