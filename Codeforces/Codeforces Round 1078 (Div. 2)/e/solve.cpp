#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 1e18;

vector<int> DominatorTree(const vector<vector<int>>& g, int src) { // 0-based
	const int n = g.size();
	vector<vector<int>> rg(n), buf(n);
	vector<int> r(n), val(n), idom(n, -1), sdom(n, -1), par(n), u(n), o;
	iota(r.begin(), r.end(), 0), iota(val.begin(), val.end(), 0);
	for (int i = 0; i < n; i++) for (auto j : g[i]) rg[j].push_back(i);
	auto Find = [&](int v, auto&& Find) -> int {
		if (v == r[v]) return v;
		int ret = Find(r[v], Find);
		if (sdom[val[v]] > sdom[val[r[v]]]) val[v] = val[r[v]];
		return r[v] = ret;
	};
	auto DFS = [&](int v, auto&& DFS) -> void {
		sdom[v] = o.size(); o.push_back(v);
		for (auto i : g[v]) if (sdom[i] == -1) par[i] = v, DFS(i, DFS);
	};
	DFS(src, DFS), reverse(o.begin(), o.end());
	for (auto& i : o) {
		if (sdom[i] == -1) continue;
		for (auto j : rg[i]) {
			if (sdom[j] == -1) continue;
			int x = val[Find(j, Find), j];
			if (sdom[i] > sdom[x]) sdom[i] = sdom[x];
		}
		buf[o[o.size() - sdom[i] - 1]].push_back(i);
		for (auto j : buf[par[i]]) u[j] = val[Find(j, Find), j];
		buf[par[i]].clear();
		r[i] = par[i];
	}
	idom[src] = src, reverse(o.begin(), o.end());
	for (auto i : o) { // WARNING : if different, takes idom
		if (i != src) idom[i] = sdom[i] == sdom[u[i]] ? sdom[i] : idom[u[i]];
	}
	for (auto i : o) if (i != src) idom[i] = o[idom[i]];
	return idom; // unreachable -> ret[i] = -1
}

int _hash(int i, int j, const int m) { return m * i + j; }

ll get_opt(const int stx, const int sty, const int n, const int m, const vector<vector<ll>> &a, vector<vector<ll>> dp) {
    for (int i = stx; i < n; i++) {
        for (int j = sty; j < m; j++) {
            dp[i][j] = (i == 0 && j == 0 ? a[0][0] : -INF);
            if (i > 0) dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i][j]);
            if (j > 0) dp[i][j] = max(dp[i][j], dp[i][j - 1] + a[i][j]);
        }
    }
    return dp[n - 1][m - 1];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<ll>> a(n, vector<ll>(m));
        for (auto &i : a) for (auto &j : i) cin >> j;

        vector<vector<ll>> dp(n, vector<ll>(m, -INF));
        vector<vector<int>> g(n * m);
        dp[0][0] = a[0][0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i > 0) dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i][j]);
                if (j > 0) dp[i][j] = max(dp[i][j], dp[i][j - 1] + a[i][j]);

                if (i > 0 && dp[i][j] == a[i][j] + dp[i - 1][j]) {
                    g[_hash(i - 1, j, m)].push_back(_hash(i, j, m));
                }
                if (j > 0 && dp[i][j] == a[i][j] + dp[i][j - 1]) {
                    g[_hash(i, j - 1, m)].push_back(_hash(i, j, m));
                }
            }
        }

        const auto res = DominatorTree(g, 0);

        const ll base = get_opt(0, 0, n, m, a, dp);

        ll ans = base;

        vector<pii> b;
        int now = _hash(n - 1, m - 1, m);
        while (1) {
            const int x = now / m, y = now % m;
            if (a[x][y] > 0) b.push_back({x, y});
            if (now == 0) break;
            now = res[now];
        }

        sort(all(b), [&](const pii &i, const pii &j) {
            if (i == pii{0, 0}) return true;
            if (j == pii{0, 0}) return false;
            if (i == pii{n - 1, m - 1}) return true;
            if (j == pii{n - 1, m - 1}) return false;
            return a[i.first][i.second] > a[j.first][j.second];
        });

        for (const auto &[x, y] : b) {
            if (ans <= base - 2 * a[x][y]) continue;
            a[x][y] *= -1;
            ans = min(ans, get_opt(x, y, n, m, a, dp));
            a[x][y] *= -1;
        }

        cout << ans << '\n';
    }

    return 0;
}
