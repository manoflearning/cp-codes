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

const int MAX = 101010, MAXD = 16;  // 2^MAXD = 65536

int n, m, t;
set<pii> s;
vector<int> adj[MAX];
int dep[MAX], par[MAX][MAXD + 1];

inline int Hash(int y, int x) {
    return y * m + x + 1;
}

void input() {
    cin >> n >> m >> t;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            if (x) {
                s.insert({ Hash(i, j), Hash(i + 1, j) });
                s.insert({ Hash(i + 1, j), Hash(i, j) });
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            int x; cin >> x;
            if (x) {
                s.insert({ Hash(i, j), Hash(i, j + 1) });
                s.insert({ Hash(i, j + 1), Hash(i, j) });
            }
        }
    }
}

void buildGraph() {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            for (int i = 0; i < 4; i++) {
                int ny = y + dy[i], nx = x + dx[i];
                if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
                if (s.count({ Hash(y, x), Hash(ny, nx) })) continue;
                adj[Hash(y, x)].push_back(Hash(ny, nx));
            }
        }
    }
}

void dfs(int now, int prv) {
	par[now][0] = prv;
	dep[now] = dep[prv] + 1;
	for (auto i : adj[now]) {
		if (i == prv) continue;
		dfs(i, now);
	}
}
void buildSparseTable() {
	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= n * m; v++) {
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

    input();

    buildGraph();
    dfs(1, 0);
	buildSparseTable();

    vector<ll> psum(t + 100);

    int k; cin >> k;
    while (k--) {
        ll s, e, y1, x1, y2, x2, v;
        cin >> s >> e >> y1 >> x1 >> y2 >> x2 >> v;
        
        ll w = dep[Hash(y1, x1)] + dep[Hash(y2, x2)] - 2 * dep[lca(Hash(y1, x1), Hash(y2, x2))] + 1;

        psum[s] += w * v;
        psum[e + 1] -= w * v;
    }

    for (int i = 1; i <= t; i++) {
        psum[i] += psum[i - 1];
        cout << psum[i] << '\n';
    }

	return 0;
}