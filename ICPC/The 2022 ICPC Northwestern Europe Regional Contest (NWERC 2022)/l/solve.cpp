#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

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

    int g, l;
    cin >> g >> l;

    const int n = g - 1;
    vector<string> s(n), t(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i];
    }

    vector<int> lb(26, 0), ub(26, l);
    vector<vector<bool>> no(l, vector<bool>(26));
    for (int i = 0; i < n; i++) {
        vector<int> cnt(26);
        for (int j = 0; j < l; j++) {
            const int x = s[i][j] - 'a';
            if (t[i][j] == 'Y' || t[i][j] == 'B') no[j][x] = 1;
            if (t[i][j] == 'G') {
                for (int y = 0; y < 26; y++) if (y != x) no[j][y] = 1;
            }
            if (t[i][j] == 'Y' || t[i][j] == 'G') cnt[x]++;
        }

        for (int x = 0; x < 26; x++) lb[x] = max(lb[x], cnt[x]);

        for (int j = 0; j < l; j++) {
            const int x = s[i][j] - 'a';
            if (t[i][j] == 'B') lb[x] = ub[x] = cnt[x];
        }
    }

    Dinic dinic(26 + l + 3);

    int sum_lb{};
    const int st = 26 + l + 1, en = 26 + l + 2;
    const int stp = 26 + l;

    for (int x = 0; x < 26; x++) {
        sum_lb += lb[x];
        if (lb[x]) dinic.addEdge(st, x, lb[x]);
        if (lb[x] < ub[x]) dinic.addEdge(stp, x, ub[x] - lb[x]);
    }
    dinic.addEdge(st, stp, l - sum_lb);
    
    for (int i = 0; i < l; i++) {
        for (int x = 0; x < 26; x++) {
            if (!no[i][x]) dinic.addEdge(x, 26 + i, 1);
        }
        dinic.addEdge(26 + i, en, 1);
    }

    const ll flow = dinic.calc(st, en);
    assert(flow == l);

    string ans(l, '.');
    for (int x = 0; x < 26; x++) {
        for (auto &e : dinic.adj[x]) {
            if (e.to < 26 || 26 + l <= e.to) continue;
            if (e.flow() == 1) {
                ans[e.to - 26] = (x + 'a');
            }
        }
    }

    cout << ans << '\n';
}
