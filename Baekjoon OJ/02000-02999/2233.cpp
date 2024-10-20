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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXD = 16;

int n, x, y, cnt = 0;
vector<int> adj[2020];
int par[2020][MAXD + 1], node[2020], dep[2020], in[2020], out[2020], vi[2020];
string s;

void dfs(int now, int prv) {
	dep[now] = dep[prv] + 1;
	for (auto i : adj[now]) {
		if (i == prv) continue;
		dfs(i, now);
	}
}

void buildSparseTable() {
	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= n; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
		}
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int diff = dep[u] - dep[v];
	for (int i = MAXD; i >= 0; i--)
		if (diff & (1 << i)) u = par[u][i];
	if (u == v) return u;
	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> s;
    cin >> x >> y;

    int now = 0;
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == '0') {
            int nxt = ++cnt;

            adj[now].push_back(nxt);
            adj[nxt].push_back(now);
            par[nxt][0] = now;
            now = nxt;
            
            node[i] = now;
			in[now] = i;
        }
        else {
            node[i] = now;
			out[now] = i;
            
            now = par[now][0];
        }
    }

    x = node[x - 1], y = node[y - 1];

    dfs(1, 0);
    buildSparseTable();

    int v = lca(x, y);
	cout << in[v] + 1 << ' ' << out[v] + 1;

	return 0;
}