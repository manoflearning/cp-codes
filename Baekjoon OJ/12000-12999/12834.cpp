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
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const ll INF = 1e18;
const int MAXV = 1010;

int N, V, E;
int A, B;
vector<int> H;
ll adj[MAXV][MAXV];

void init() {
	for (int i = 0; i < MAXV; i++) {
		for (int j = 0; j < MAXV; j++) {
			adj[i][j] = INF;
		}
	}
}

void input() {
    cin >> N >> V >> E;
    cin >> A >> B;
    H.resize(N);
    for (auto& i : H) cin >> i;
    for (int i = 0; i < E; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u][v] = min(adj[u][v], w);
        adj[v][u] = min(adj[v][u], w);
    }
}

void floyd() {
	for (int i = 1; i <= V; i++) adj[i][i] = 0;
	for (int k = 1; k <= V; k++) {
		for (int u = 1; u <= V; u++) {
			for (int v = 1; v <= V; v++) {
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	init();
    input();
    floyd();

    ll ans = 0;
    for (auto& i : H) {
        ans += (adj[i][A] == INF ? -1 : adj[i][A]);
        ans += (adj[i][B] == INF ? -1 : adj[i][B]);
    }

    cout << ans;

	return 0;
}