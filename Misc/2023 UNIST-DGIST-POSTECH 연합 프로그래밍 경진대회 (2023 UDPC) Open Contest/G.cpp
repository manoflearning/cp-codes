//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, vi[202020], st, ban1, ban2, dep[202020];
vector<int> adj[202020];

void dfs1(int v, int d) {
    dep[v] = min(dep[v], d);
    vi[v] = 1;
    for (auto& i : adj[v]) {
        if (!vi[i]) dfs1(i, d + 1);
    }
}

int dfs(int v, int d) {
    vi[v] = 1;

    if (sz(adj[v]) == 1) return 1;
    
    int ret = 0;
    for (auto& i : adj[v]) {
        if (!vi[i] && d + 1 < dep[i]) ret |= dfs(i, d + 1);
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

    // initialize
    for (int i = 0; i < 202020; i++) dep[i] = INF;

	cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> st >> ban1 >> ban2;
    
    dfs1(ban1, 0);
    memset(vi, 0, sizeof(vi));
    dfs1(ban2, 0);
    memset(vi, 0, sizeof(vi));

    cout << (dfs(st, 0) ? "YES" : "NO");

	return 0;
}