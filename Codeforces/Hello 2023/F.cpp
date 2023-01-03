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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, a[202020], bit[202020], sub[202020], all;
vector<int> adj[202020];
int vv = -1;
vector<pii> res;

void dfs(int v, int prv) {
	sub[v] = 1;
	bit[v] = a[v];
	for (auto& i : adj[v]) {
		if (i == prv) continue;
		dfs(i, v);
		sub[v] += sub[i];
		bit[v] ^= bit[i];
	}

	if ((sub[v] & 1) && bit[v] == 0) vv = v;
	if (!(sub[v] & 1)) {
		res.push_back({ bit[v], v });
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
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		all ^= a[i];
	}
	for (int v = 2; v <= n; v++) {
		int u; cin >> u;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	if (n & 1) {
		dfs(1, 0);
		if (vv != -1) {
			cout << 3 << '\n';
			cout << vv << ' ' << 1 << ' ' << 1;
			return 0;
		}
		
		for (int i = 0; i < sz(res); i++) {
			if (res[i].fr == all) {
				cout << 4 << '\n';
				cout << res[i].sc << ' ' << res[i].sc << ' ' << 1 << ' ' << 1;
				return 0;
			}
			for (int j = i + 1; j < sz(res); j++) {
				if (res[i].fr ^ res[j].fr == all) {
					cout << 6 << '\n';
					cout << res[i].sc << ' ' << res[i].sc << ' ' << res[j].sc << ' ' << res[j].sc << ' ' << 1 << ' ' << 1;
					return 0;
				}
			}
		}
		cout << -1;
		return 0;
	}
	else {
		cout << 2 << '\n';
		cout << 1 << ' ' << 1;
	}

	return 0;
}