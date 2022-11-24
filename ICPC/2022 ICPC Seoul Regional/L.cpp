#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define fr first
#define sc second

vector<int> uf(101010, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int u = find(u), v = find(v);
    if (u == v) return;
    uf[u] += uf[v];
    uf[v] = u;
}

int n, in[101010], out[101010], dep[101010], dp[101010];
vector<int> adj[101010];
vector<pii> cy[101010];

void dfs(int v, int prv, int d) {
    in[v] = 1;
    dep[v] = d;
    dp[v] = prv;
    for (auto& i : adj[v]) {
        if (in[i]) {
            if (out[i]) continue;
            int len = dep[v] - dep[i] + 1;
            cy[len].push_back({ i, v });
        }
        else dfs(i, v, d + 1);
    }
    out[v] = 1;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    for (int i = 0; i < 2 * n - 3; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        merge(u, v);
    }

    vector<int> arr;
    for (int v = 1; v <= n; v++) {
        arr.push_back(find(v));
    }

    sort(all(arr));
    arr.erase(unique(all(arr)), arr.end());

    for (int i = 0; i + 1 < arr.size(); i++) {
        int u = arr[i], v = arr[i + 1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0, 1);

    for (int i = 3; i < 101010; i++) {
        if (sz(cy[i]) <= 1) continue;
    }

	return 0;
}