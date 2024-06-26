#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vs vector<string>
#define vvs vector<vector<string>>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

const int MAX = 5e5 + 5;

int n;
ll c[MAX], sz[MAX], dp[MAX];
vi adj[MAX];

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void dfs(int v, int prv) {
	sz[v] = 1;
	for (auto& u : adj[v]) {
		if (u == prv) continue;
		dfs(u, v);
		sz[v] += sz[u];
	}
}

void f(int v, int prv) {
	vector<pll> a;
	for (auto& u : adj[v]) {
		if (u == prv) continue;
		f(u, v);
		a.push_back({ dp[u] - 2 * sz[u], u });
	}
	
	sort(a.rbegin(), a.rend());

	dp[v] = c[v];

	ll sum = 0;
	for (auto& i : a) {
		dp[v] = max(dp[v], 1 + dp[i.sc] + sum);
		sum += 2 * sz[i.sc];
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	dfs(1, -1);

	f(1, -1);

	/*for (int i = 1; i <= n; i++) {
		cout << "dp[" << i << "] = " << dp[i] << '\n';
	}*/

	ll ans = max(2 * (n - 1) + c[1], dp[1]);
	cout << ans;

	return 0;
}