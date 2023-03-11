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

int n, m;
vector<int> adj[404040];
int vi[404040];

int isCycle = 0;

void dfs(int v, int prv) {
    vi[v] = 1;
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        if (vi[i]) isCycle = 1;
        else dfs(i, v);
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    for (int v = 1; v <= n; v++) {
        adj[v << 1].push_back(v << 1 | 1);
        adj[v << 1 | 1].push_back(v << 1);
    }

    for (int i = 0; i < m; i++) {
        int u, v; char x, y;
        cin >> u >> x >> v >> y;
        if (x == 'R') u = u * 2;
        else u = u * 2 + 1;
        if (y == 'R') v = v * 2;
        else v = v * 2 + 1;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans1 = 0, ans2 = 0;
    for (int v = 1; v <= n; v++) {
        if (!vi[v << 1]) {
            isCycle = 0;
            dfs(v << 1, -1);
            if (isCycle) ans1++;
            else ans2++;
        }
    }

    cout << ans1 << ' ' << ans2;

	return 0;
}