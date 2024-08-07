#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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

int n, a[1010], w[1010], visited[1010][505];
vt<int> adj[1010];

void init() {
    FOR(1010) {
        a[i] = w[i] = 0;
        memset(visited[i], 0, sizeof(visited[i]));
        adj[i].clear();
    }
}

void input() {
    FOR(i, 1, n + 1) {
        char c; cin >> c;
        
        if (c == 'E') a[i] = 0;
        else if (c == 'L') a[i] = 1;
        else if (c == 'T') a[i] = 2;

        cin >> w[i];

        while (1) {
            int v; cin >> v;
            if (!v) break;
            adj[i].push_back(v);
        }
    }
}

int dfs(int v, int c) {
    visited[v][c] = 1;
    if (v == n) return 1;

    int ret = 0;
    EACH(i, adj[v]) {
        if (a[i] == 0) {
            if (visited[i][c]) continue;
            ret |= dfs(i, c);
        }
        if (a[i] == 1) {
            if (visited[i][max(w[i], c)]) continue;
            ret |= dfs(i, max(w[i], c));
        }
        if (a[i] == 2 && w[i] <= c) {
            if (visited[i][c - w[i]]) continue;
            ret |= dfs(i, c - w[i]);
        }
    }

    return ret;
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

        cin >> n;
        if (!n) break;

        input();
        
        if (a[1] != 2 && dfs(1, (a[1] == 1 ? w[1] : 0))) cout << "Yes\n";
        else cout << "No\n";
    }
    
	return 0;
}