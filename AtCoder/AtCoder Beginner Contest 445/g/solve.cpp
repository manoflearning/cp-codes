#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int dx[] = {1, 1, -1, -1};
constexpr int dy[] = {1, -1, 1, -1};

void dfs(int x, int y, int co, vector<vector<int>> &is_l, const int n, const int a, const int b) {
    is_l[x][y] = co;

    for (int d = 0; d < 8; d++) {
        const int nx = x + dx[d % 4] * (d / 4 ? a : b);
        const int ny = y + dy[d % 4] * (d / 4 ? b : a);
        if (nx < 0 || n <= nx || ny < 0 || n <= ny) continue;
        
        if (is_l[nx][ny] == -1) {
            dfs(nx, ny, !co, is_l, n, a, b);
        } else {
            assert(is_l[x][y] == !is_l[nx][ny]);
        }
    }
}

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, a, b;
    cin >> n >> a >> b;

    vector<string> s(n);
    for (auto &i : s) cin >> i;

    vector<vector<int>> is_l(n, vector<int>(n, -1));
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (is_l[x][y] == -1) {
                dfs(x, y, 1, is_l, n, a, b);
            }
        }
    }

    // DEBUG
    // for (int x = 0; x < n; x++) {
    //     for (int y = 0; y < n; y++) {
    //         cout << is_l[x][y] << ' ';
    //     }
    //     cout << '\n';
    // }

    vector<vector<int>> _hash(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            _hash[i][j] = i * n + j;
        }
    }

    Dinic flow(n * n + 2);
    const int st = n * n, en = n * n + 1;

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (s[x][y] == '#') continue;

            if (is_l[x][y]) {
                flow.addEdge(st, _hash[x][y], 1);
                for (int d = 0; d < 8; d++) {
                    const int nx = x + dx[d % 4] * (d / 4 ? a : b);
                    const int ny = y + dy[d % 4] * (d / 4 ? b : a);
                    if (nx < 0 || n <= nx || ny < 0 || n <= ny) continue;
                    if (s[nx][ny] == '#') continue;

                    flow.addEdge(_hash[x][y], _hash[nx][ny], 1);
                }
            } else {
                flow.addEdge(_hash[x][y], en, 1);
            }
        }
    }

    flow.calc(st, en);

    auto ans = s;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (s[x][y] == '#') continue;

            bool yes = 0;
            yes |= (is_l[x][y] && flow.leftOfMinCut(_hash[x][y]));
            yes |= (!is_l[x][y] && !flow.leftOfMinCut(_hash[x][y]));
            if (yes) ans[x][y] = 'o';
        }
    }

    for (auto &i : ans) cout << i << '\n';

    return 0;
}
