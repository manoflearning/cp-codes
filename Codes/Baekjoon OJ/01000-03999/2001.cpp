//bit masking + dp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

const int MAXN = 105;

struct wv {
    int w, v;
};

int n, m, a;
int dp[MAXN][15][1 << 14];
int Hash[15], hCnt;
vector<wv> adj[MAXN];
int visited[MAXN], canGo[MAXN][MAXN][15];

void init() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < 15; j++) {
            memset(dp[i][j], -1, sizeof(dp[i][j]));
        }
    }
}

void input() {
    cin >> n >> m >> a;
    
    for (int i = 0; i < a; i++) {
        int x; cin >> x;
        Hash[i] = x;
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dfs(int st, int v, int c) {
    visited[v] = canGo[st][v][c] = 1;
    
    for (auto& i : adj[v]) {
        if (visited[i.v] || i.w < c) continue;
        dfs(st, i.v, c);
    }
}

int f(int v, int c, int b) {
    int& ret = dp[v][c][b];
    if (ret != -1) return ret;
    
    ret = 0;
    
    if (canGo[v][1][c]) ret = max(ret, c);
    if (canGo[v][1][c + 1]) ret = max(ret, c + 1);

    for (int i = 0; i < a; i++) {
        if (b & (1 << i)) continue;
        
        int u = Hash[i];
        if (canGo[v][u][c]) ret = max(ret, f(u, c, b | (1 << i)));
        if (canGo[v][u][c + 1]) ret = max(ret, f(u, c + 1, b | (1 << i)));
    }
    
    return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	for (int i = 1; i <= n; i++) {
	    for (int j = 0; j < 15; j++) {
	        memset(visited, 0, sizeof(visited));
	        dfs(i, i, j);
	    }
	}
	
	int ans = 0;
	for (int i = 0; i < a; i++) {
	    int u = Hash[i];
	    if (canGo[1][u][0]);
	        ans = max(ans, f(u, 0, 1 << i));
	}
	
	cout << ans;
	
	return 0;
}
