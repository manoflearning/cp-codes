#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<ll> p(252525, -1);

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    p[U] += p[V];
    p[V] = U;
}

int n, q, par[252525];
vector<int> adj[252525];

void dfs(int v, int prv) {
    par[v] = prv;
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        dfs(i, v);
    }
}

int m;
vector<int> arr;
int vi[252525];

void init() {
    for (auto& i : arr) {
        vi[i] = 0;
        p[i] = -1;
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

    dfs(1, 0);

    cin >> q;
    while (q--) {
        cin >> m;
        arr.resize(m);
        for (auto& i : arr) {
            cin >> i;
            vi[i] = 1;
        }

        for (auto& i : arr) {
            if (vi[par[i]]) merge(i, par[i]);
        }

        set<int> s;
        for (auto& i : arr) {
            s.insert(find(i));
        }

        ll ans = 0;
        for (auto& i : s) {
            ans += -p[i] * (-p[i] - 1) / 2;
        }

        cout << ans << '\n';

        init();
    }

    return 0;
}