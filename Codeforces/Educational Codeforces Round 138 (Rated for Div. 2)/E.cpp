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
vt<string> a, ans;
vt<vt<int>> dp;

void init() {
    n = m = 0;
    a.clear();
    ans.clear();
    dp.clear();
}

void input() {
    cin >> n >> m;

    a.resize(n);
    EACH(i, a) cin >> i;

    dp.resize(n + 10, vt<int>(m + 10, -1));
}

bool near(int y, int x) {
    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
        
        if (a[ny][nx] == '#') return 1;
    }
    return 0;
}

int f(int y, int x) {
    int& ret = dp[y][x];
    if (ret != -1) return ret;

    if (near(y, x)) return ret = INF;

    ret = (a[y][x] == '#' ? 0 : 1);

    if (x == m - 1) return ret;

    int res = INF;
    if (y > 0) res = min(res, f(y - 1, x + 1));
    if (y + 1 < n) res = min(res, f(y + 1, x + 1));

    ret += res;
    if (ret > INF) ret = INF;
    return ret;
}

void track(int y, int x) {
    ans[y][x] = '#';
    assert(f(y, x) < INF);
    if (x == m - 1) return;

    if (y == n - 1) track(y - 1, x + 1);
    else if (y == 0) track(y + 1, x + 1);
    else {
        if (f(y - 1, x + 1) <= f(y + 1, x + 1)) track(y - 1, x + 1);
        else track(y + 1, x + 1);
    }
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
        init();

        input();

        int bit = 0, mn = INF, idx = -1;
        FOR(n) {
            if (f(i, 0) < m * n) {
                bit = 1;
                if (mn > f(i, 0)) {
                    mn = f(i, 0);
                    idx = i;
                }
            }
        }
        
        if (!bit) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        
        ans = a;
        track(idx, 0);

        EACH(i, ans)
            cout << i << '\n';
	}

	return 0;
}