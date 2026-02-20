#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#include <bits/extc++.h>

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
	struct edge {
		int from, to, rev;
		ll cap, cost, flow;
	};
	int N;
	vector<vector<edge>> ed;
	vi seen;
	vector<ll> dist, pi;
	vector<edge*> par;

	MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		if (from == to) return;
		ed[from].push_back(edge{ from,to,sz(ed[to]),cap,cost,0 });
		ed[to].push_back(edge{ to,from,sz(ed[from])-1,0,-cost,0 });
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end())
						its[e.to] = q.push({ -dist[e.to], e.to });
					else
						q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);

			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		rep(i,0,N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
		return {totflow, totcost/2};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
			  for (edge& e : ed[i]) if (e.cap)
				  if ((v = pi[i] + e.cost) < pi[e.to])
					  pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

int _hash(int x, int y, const int m, const int type) { return (x + y * m) * 4 + type; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int m, n, s;
    cin >> m >> n >> s;

    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            a[i][j] = s[j] - '0';
            a[i][j]--;
        }
    }

    MCMF mcmf(4 * m * n + 10);

    const int st = 4 * m * n + 8;
    const int en = 4 * m * n + 9;

    ll sum_a = 0;
    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            if (a[x][y] >= 0) {
                sum_a += a[x][y];
                if (a[x][y] > 0) mcmf.addEdge(_hash(x, y, m, 1), _hash(x, y, m, 2), a[x][y], -1);
                if (8 - a[x][y] > 0) mcmf.addEdge(_hash(x, y, m, 1), _hash(x, y, m, 2), 8 - a[x][y], +1);
            }
        }
    }

    ll sum_h{}, sum_v{};
    for (int i = 0; i < s; i++) {
        char op; int x, y, val;
        cin >> op >> x >> y >> val;
        x--, y--;
        
        if (op == 'H') {
            for (int j = y + 1; j < n && a[x][j] >= 0; j++) val--;
            sum_h += val;

            const int now = _hash(x, y, m, 3);
            mcmf.addEdge(st, now, val, 0);
            for (int j = y + 1; j < n && a[x][j] >= 0; j++) {
                mcmf.addEdge(now, _hash(x, j, m, 1), INF, 0);
            }
        } else {
            for (int j = x + 1; j < m && a[j][y] >= 0; j++) val--;
            sum_v += val;

            const int now = _hash(x, y, m, 4);
            mcmf.addEdge(now, en, val, 0);
            for (int j = x + 1; j < m && a[j][y] >= 0; j++) {
                mcmf.addEdge(_hash(j, y, m, 2), now, INF, 0);
            }
        }
    }

    if (sum_h != sum_v) {
        cout << "IMPOSSIBLE\n";
        exit(0);
    }

    mcmf.setpi(st);

    const auto [flow, cost] = mcmf.maxflow(st, en);
    if (flow != sum_h) {
        cout << "IMPOSSIBLE\n";
        exit(0);
    }

    cout << cost + sum_a << '\n';
}
