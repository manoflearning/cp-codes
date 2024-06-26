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

int n, m, deg[202020], vi[202020];
vector<int> adj[202020];

void dfs(int v) {
    vi[v] = 1;
    for (auto& i : adj[v])
        if (!vi[i]) dfs(i);
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
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }

    if (m != n - 1) {
        cout << "No";
        return 0;
    }

    int cnt1 = 0, cnt2 = 0, com = 0;
    for (int v = 1; v <= n; v++) {
        if (deg[v] == 1) cnt1++;
        if (deg[v] == 2) cnt2++;

        if (!vi[v]) { dfs(v); com++; }
    }

    if (cnt1 == 2 && cnt2 == n - 2 && com == 1) {
        cout << "Yes";
    }
    else cout << "No";

	return 0;
}