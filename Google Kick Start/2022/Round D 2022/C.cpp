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
vt<int> a, b;
int dist[2525][2525];

void init() {
    n = m = 0;
    a.clear();
    b.clear();
    FOR(2525) FOR(j, 2525) dist[i][j] = -1;
}

void input() {
    cin >> n;
    a.resize(n);
    EACH(i, a) cin >> i;
        
    cin >> m;
    b.resize(m);
    EACH(i, b) cin >> i;
}

/*int f(int aidx, int bidx) {
    int& ret = dp[aidx][bidx];
    if (ret != -1) return ret;
    if (aidx == n - 1) return ret = 0;

    ret = INF;

    int naidx = aidx;
    FOR(i, bidx, m) {
        if (naidx + 1 < n && b[i] == a[naidx + 1]) {
            naidx++;
            ret = min(ret, f(naidx, i) + abs(i - bidx));
            i--;
        }
    }

    naidx = aidx;
    FOR(i, bidx, 0, -1) {
        if (naidx + 1 < n && b[i] == a[naidx + 1]) {
            naidx++;
            ret = min(ret, f(naidx, i) + abs(i - bidx));
            i++;
        }
    }

    return ret;
}*/

/*int dist(int st) {
    int ret = 0, idx = st;
    FOR(i, 1, n) {
        int res = lower_bound(all(loc[a[i]]), idx) - loc[a[i]].begin();
        if (res > 0 && abs(loc[a[i]][res] - idx) > abs(loc[a[i]][res - 1] - idx)) res--;
        ret += abs(loc[a[i]][res] - idx);
        idx = loc[a[i]][res];
    }
    return ret;
}*/

struct ab {
    int aidx, bidx;
};

int bfs() {
    queue<ab> q;
    FOR(m) {
        if (b[i] == a[0]) {
            q.push({ 0, i });
            dist[0][i] = 0;
        }
    }

    while (sz(q)) {
        
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

	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        cout << "Case #" << tt << ": ";
        
        init();

        input();

        cout << bfs() << '\n';
    }

	return 0;
}