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
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
vector<int> adj[5050];

void input() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

int vi[5050], dep[5050], isLeaf[5050], par[5050];
vector<int> bydep[5050], t[5050];

void dfs(int v, int d) {
	if (v != 1 && sz(adj[v]) == 1) isLeaf[v] = 1;
	vi[v] = 1;
	dep[v] = d;
	bydep[d].push_back(v);
	for (auto& i : adj[v]) {
		if (!vi[i]) {
			dfs(i, d + 1);
			par[i] = v;
			t[v].push_back(i);
		}
	}
}

ll dp[5050][5050];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	if (n == 1) {
		cout << 1;
		return 0;
	}

	par[1] = 0;
	dfs(1, 1);

	ll ans = 0;
	for (int d = n; d >= 1; d--) {
		for (auto& v : bydep[d]) {
			if (isLeaf[v]) dp[v][1] = 1;
			else {
				ll res = 1;
				for (auto& u : t[v]) {
					res = res * (1 + dp[u][1]) % MOD;
				}
				dp[v][1] = (dp[v][1] + res) % MOD;
			}
			cout << v << ' ' << dp[v][1] << '\n';
			ans = (ans + dp[v][1]) % MOD;
		}
	}

	cout << ans;

	return 0;
}