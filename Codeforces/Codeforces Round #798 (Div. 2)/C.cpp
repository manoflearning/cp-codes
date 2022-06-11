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

int n, vi[303030], dp[303030];
vt<int> adj[303030], chd[303030];

void dfs(int now, int prv) {
    EACH(i, adj[now]) {
        if (i == prv) continue;
        chd[now].push_back(i);
        dfs(i, now);
    }
}

int dfs2(int now) {
    int& ret = dp[now];
    ret = INF;
    EACH(i, chd[now]) {
        if (sz(adj[now]) - 1 == 2) ret = min(ret, dfs2(i));
        else dfs2(i);
    }
    if (ret == INF) ret = 0;
    ret += (sz(adj[now]) == 1 ? 1 : 2);
    return ret;
}

void init() {
    FOR(i, 1, n + 1) {
        dp[i] = vi[i] = 0;
        adj[i].clear();
        chd[i].clear();
    }
    n = 0;
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

    while (tc--) {
        cin >> n;
        FOR(n - 1) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0);
        dfs2(1);

        int cnt = 0;
        queue<int> q;
        q.push(1);
        vi[1] = 1;
        while (sz(q)) {
            int now = q.front();
            q.pop();
            
            int mx = -1, mxidx = -1;
            EACH(i, chd[now]) {
                vi[i] = 1;
                if (dp[i] > mx) {
                    mx = dp[i], mxidx = i;
                }
            }
            //cout << now << ' ' << mx << ' ' << mxidx << '\n';
            EACH(i, chd[now]) {
                if (i == mxidx) continue;
                q.push(i);
            }
        }

        int ans = n;
        FOR(i, 1, n + 1) {
            //cout << i << ' ' << vi[i] << '\n';
            //cout << i << ' ' << dp1[i] << ' ' << dp2[i] << '\n';
            ans -= vi[i];
        }

        cout << ans << '\n';

        init();
    }

	return 0;
}

/*#define _USE_MATH_DEFINES
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

int n, vi[303030], dp1[303030], dp2[303030];
vt<int> adj[303030], chd[303030];

int dfs(int now, int prv) {
    int& ret = dp1[now];
    ret = (now != 1 && sz(adj[now]) <= 2 ? 0 : INF);
    EACH(i, adj[now]) {
        if (i == prv) continue;
        chd[now].push_back(i);
        ret = min(ret, dfs(i, now) + 1);
    }
    return ret;
}

int dfs2(int now) {
    int& ret = dp2[now];
    ret = (dp1[now] == 0 ? 1 : 0);
    EACH(i, chd[now]) {
        if (dp1[i] + 1 == dp1[now]) ret += dfs2(i);
        else dfs2(i);
    }
    return ret;
}

void init() {
    FOR(i, 1, n + 1) {
        dp1[i] = dp2[i] = vi[i] = 0;
        adj[i].clear();
        chd[i].clear();
    }
    n = 0;
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

    while (tc--) {
        cin >> n;
        FOR(n - 1) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, 0);
        dfs2(1);

        int cnt = 0;
        queue<int> q;
        q.push(1);
        vi[1] = 1;
        while (sz(q)) {
            int now = q.front();
            q.pop();
            
            int mx1 = 0, mx2 = 0, mxidx = -1;
            EACH(i, chd[now]) {
                vi[i] = 1;
                if (dp1[i] > mx1 || (dp1[i] == mx1 && dp2[i] > mx2)) {
                    mx1 = dp1[i], mx2 = dp2[i], mxidx = i;
                }
            }

            EACH(i, chd[now]) {
                if (i == mxidx) continue;
                q.push(i);
            }
        }

        int ans = n;
        FOR(i, 1, n + 1) {
            //cout << i << ' ' << vi[i] << '\n';
            //cout << i << ' ' << dp1[i] << ' ' << dp2[i] << '\n';
            ans -= vi[i];
        }

        cout << ans << '\n';

        init();
    }

	return 0;
}*/