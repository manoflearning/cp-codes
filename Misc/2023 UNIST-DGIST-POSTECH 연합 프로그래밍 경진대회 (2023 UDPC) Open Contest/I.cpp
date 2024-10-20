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

struct wv { ll w; int v; };
struct Edge { ll w; int u, v; };

int n, m;
vector<wv> adj[202020];
vector<Edge> edge;

ll f2(int v, int b1, int b2) {
    ll ret = 0;
    for (int i = 0; i < min(3, sz(adj[v])); i++) {
        int u = adj[v][i].v;
        if (u != b1 && u != b2)
            ret = max(ret, adj[v][i].w);
    }
    return ret;
}

ll f(int u, int v) {
    ll ret = 0;
    for (int i = 0; i < min(3, sz(adj[u])); i++) {
        int now = adj[u][i].v;
        if (now == v) continue;
        ret = max(ret, adj[u][i].w + f2(v, u, now));
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

	cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
        edge.push_back({ w, u, v });
    }

    sort(edge.begin(), edge.end(), [&](const Edge& lhs, const Edge& rhs) {
        return lhs.w > rhs.w;
    });

    if (m == 0) {
        cout << 0;
        return 0;
    }
    if (m == 1) {
        cout << edge[0].w;
        return 0;
    }
    if (m == 2) {
        cout << edge[0].w + edge[1].w;
        return 0;
    }

    for (int v = 1; v <= n; v++) {
        sort(adj[v].begin(), adj[v].end(), [&](const wv& lhs, const wv& rhs) {
            return lhs.w > rhs.w;
        });
    }

    ll ans = edge[0].w + edge[1].w;
    for (auto& i : edge) {
        ans = max(ans, i.w + f(i.u, i.v));
    }

    cout << ans;

	return 0;
}