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
int a[111][111];

int cnt, vi[111][111], num[111][111];
vt<int> adj[10101];
vt<pii> arr;
vt<vt<pii>> com(1);

void dfs(int y, int x) {
    vi[y][x] = 1;
    num[y][x] = cnt;
    arr.push_back({ y, x });

    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 1 || n < ny || nx < 1 || m < nx) continue;
        if (vi[ny][nx]) continue;
        if (a[y][x] != a[ny][nx]) continue;
        dfs(ny, nx);
    }
}

int bfs(int st) {
    queue<int> q;
    vt<int> dist(cnt + 1, -1);

    q.push(st);
    dist[st] = 0;
    
    int ret = 0;
    while (sz(q)) {
        int v = q.front();
        q.pop();
        
        ret = max(ret, dist[v]);

        for (auto& i : adj[v]) {
            if (dist[i] == -1) {
                dist[i] = dist[v] + 1;
                q.push(i);
            }
        }
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

	cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!vi[i][j]) {
                cnt++;
                arr.clear();
                dfs(i, j);
                com.push_back(arr);
            }
        }
    }

    for (int v = 1; v <= cnt; v++) {
        set<int> s;
        for (auto& i : com[v]) {
            for (int j = 0; j < 4; j++) {
                int ny = i.fr + dy[j], nx = i.sc + dx[j];
                if (ny < 1 || n < ny || nx < 1 || m < nx) continue;
                
                if (a[i.fr][i.sc] != a[ny][nx]) {
                    s.insert(num[ny][nx]);
                }
            }
        }
        for (auto& i : s) {
            adj[v].push_back(i);
        }
    }

    int ans = INF;
    for (int v = 1; v <= cnt; v++) {
        int res = bfs(v);

        ans = min(ans, res);
    }

    cout << ans;

	return 0;
}