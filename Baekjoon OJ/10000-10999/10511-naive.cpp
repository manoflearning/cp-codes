// TIME COMPLEXITY: O(mq) for each test case

#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> uf(1010, -1);
int find(int x) {
	if (uf[x] < 0) return x;
	return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
	int U = find(u), V = find(v);
	if (U == V) return;
	uf[U] = V;
}

struct Edge {
	ll w; int u, v;
	bool operator<(const Edge& rhs) const {
		return w < rhs.w;
	}
};

int n, m;
vector<Edge> e;
vector<ll> ans;

void init() {
	e.clear();
	ans.clear();
}

void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; ll w;
		cin >> u >> v >> w;
		e.push_back({ w, u , v });
	}
}

ll mst(ll lb, ll ub) {
	uf.clear();
	uf.resize(1010, -1);
	ll ret = 0;
	for (auto& i : e) {
		if (i.w < lb || ub < i.w) continue;

		if (find(i.u) != find(i.v)) {
			merge(i.u, i.v);
			ret += i.w;
		}
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

	int tc; cin >> tc;
	while (tc--) {
		init();

		input();

		sort(e.begin(), e.end());

		int q; cin >> q;
		ans.resize(q);
		for (int i = 0; i < q; i++) {
			ll lb, ub;
			cin >> lb >> ub;
			if (i > 0) lb -= ans[i - 1], ub -= ans[i - 1];
			ans[i] = mst(lb, ub);
		}

		for (int i = 0; i < q; i++)
			cout << ans[i] << '\n';
	}
}