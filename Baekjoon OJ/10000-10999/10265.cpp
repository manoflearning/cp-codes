#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

const int MAXN = 1e3 + 5;

int n, k, adj[MAXN], a[MAXN], b[MAXN];
int isCyc[MAXN], cNum = 1, cSz[MAXN], allSz[MAXN];
int dp[MAXN][MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            dp[i][j] = -1;
        }
    }
}

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> adj[i];
    }
}

void dfs(int v) {
    a[v] = 1;
    
    int u = adj[v];
    if (a[u] && !b[u]) {
        int sz = 0;
        for (int i = u; i != v; i = adj[i]) {
            isCyc[i] = cNum, sz++;
        }
        isCyc[v] = cNum, sz++;
        
        allSz[cNum] = cSz[cNum] = sz;
        cNum++;
    }
    if (!a[u]) dfs(u);
    
    b[v] = 1;
}

void findCyc() {
    for (int i = 1; i <= n; i++) {
        if (!a[i]) dfs(i);
    }
}

void dfs2(int v) {
    a[v] = 1;
    
    if (isCyc[v]) return;
    
    int u = adj[v];
    if (!a[u]) dfs2(adj[v]);
    
    if (isCyc[u]) b[u] = isCyc[u];
    if (a[u] && b[u]) {
        b[v] = b[u], allSz[b[v]]++;
    }
}

void findAll() {
    for (int i = 1; i <= n; i++) {
        if (!a[i]) dfs2(i);
    }
}

int f(int idx, int mx) {
    int& ret = dp[idx][mx];
    if (ret != -1) return ret;
    if (idx == cNum) return ret = 0;
    
    ret = max(ret, f(idx + 1, mx));
    
    for (int i = cSz[idx]; i <= min(mx, allSz[idx]); i++) {
        ret = max(ret, i + f(idx + 1, mx - i));
    }
    
    return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	findCyc();
	
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	
	findAll();
	
	/*for (int i = 1; i < cNum; i++) {
	    cout << i <<' ' << cSz[i] << ' '<<allSz[i]<<'\n';
	}*/
	cout << f(1, k);

	return 0;
}
