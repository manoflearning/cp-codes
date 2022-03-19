#include <iostream>
#include <vector>
#define ll long long
#define vvl vector<vector<ll>>
using namespace std;

const int MOD = 1e9 + 7;

int N;
vvl adj;

vvl f(int x);
vvl mul(vvl& a, vvl& b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int M;
	cin >> N >> M;

	adj.resize(N + 1, vector<ll>(N + 1));

	while (M--) {
		int u, v;
		cin >> u >> v;
		adj[u][v] = adj[v][u] = 1;
	}

	int D; cin >> D;
	vvl ans = f(D);

	cout << ans[1][1] << '\n';

	return 0;
}

vvl f(int x) {
	if (x == 1) return adj;
	vvl prv = f(x >> 1);
	vvl ret = mul(prv, prv);
	if (x & 1) ret = mul(ret, adj);
	return ret;
}

vvl mul(vvl& a, vvl& b) {
	vvl ret(N + 1, vector<ll>(N + 1));
	for (int i = 1; i <= N; i++) {
		for (int l = 1; l <= N; l++) {
			for (int k = 1; k <= N; k++) {
				ret[i][l] = (ret[i][l] + a[i][k] * b[k][l]) % MOD;
			}
		}
	}
	return ret;
}