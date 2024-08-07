#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int N;
vector<int> tree;
vector<vector<int>> adj, adj_rev;
int p[101010][22];
int dep[101010];

vector<int> get_result() {
    vector<int> result;

    queue<int> q;
    q.push(1);
    dep[1] = 1;

    while (!q.empty()) {
        auto x = q.front();
        q.pop();

        result.push_back(x);

        for (auto nxt : adj[x]) {
            q.push(nxt);
            dep[nxt] = dep[x] + 1;
        }
    }

    return result;
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);

    int ret = 0;
    int diff = dep[v] - dep[u];
    for (int i = 0; i <= 20; i++) {
        if (diff & (1 << i)) {
            v = p[v][i];
            ret += (1 << i);
        }
    }

    if (u == v) return ret;

    for (int i = 20; i >= 0; i--) {
        if (p[u][i] ^ p[v][i]) {
            u = p[u][i];
            v = p[v][i];
            ret += 2 * (1 << i);
        }
    }
    return ret + 2;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    adj.resize(N + 1);
    adj_rev.resize(N + 1);
    tree.assign(N + 1, -1);

    for (int i=2; i<=N; i++) {
        cin >> tree[i];
        adj[tree[i]].push_back(i);
        adj_rev[i].push_back(tree[i]);
        p[i][0] = tree[i];
    }

    for (int i=1; i<=N; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    // solve
    auto bfs_result = get_result();

    // for (auto u : bfs_result) {
    //     cout << u << ' ';
    // }

    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= N; j++) {
            p[j][i] = p[p[j][i - 1]][i - 1];
        }
    }

    ll ans = 0;
    for (int i=0; i<N-1; i++) {
        ans += lca(bfs_result[i], bfs_result[i + 1]);
    }

    cout << ans << '\n';

    return 0;
}