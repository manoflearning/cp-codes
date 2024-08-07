#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 998244353;

int n, vi[5050];
vector<int> adj[5050];
vector<vector<ll>> dp[5050];

void dfs(int v) {
	vi[v] = 1;
	auto& ret = dp[v];
	ret.resize(2, vector<ll>(2));
	
	ret[0][0] = 1;
	ret[1][1] = 1;
	
	for (auto& i : adj[v]) {
		if (vi[i]) continue;
		
		dfs(i);

		auto& arr = dp[i];

		vector<vector<ll>> tmp(sz(ret) + sz(arr) - 1, vector<ll>(2));

		for (int j = 0; j < sz(ret); j++) {
			for (int k = 0; k < sz(arr); k++) {
				tmp[j + k][0] += ret[j][0] * (arr[k][0] + arr[k][1]);
				tmp[j + k][0] %= MOD;
				tmp[j + k][1] += ret[j][1] * arr[k][0];
				tmp[j + k][1] %= MOD;
				if (j + k == 0) continue;
				tmp[j + k - 1][1] += ret[j][1] * arr[k][1];
				tmp[j + k - 1][1] %= MOD;
			}
		}

		ret = tmp;
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1);
	
	for (int i = 1; i <= n; i++) {
		cout << (dp[1][i][0] + dp[1][i][1]) % MOD << '\n';
	}
}