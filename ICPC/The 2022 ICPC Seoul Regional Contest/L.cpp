// solution 1
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[101010];
int in[101010], out[101010], dep[101010], par[101010];
vector<pair<int, int>> cycle[101010];

void dfs(int v, int prv) {
    in[v] = 1;

    par[v] = prv;
    dep[v] = dep[prv] + 1;
    for (auto& i : adj[v]) {
        if (prv == i) continue;
        if (!in[i]) dfs(i, v);
        else if (!out[i]) {
            cycle[dep[v] - dep[i] + 1].push_back({ i, v });
        }
    }

    out[v] = 1;
}

void print(int v, int u) {
    for (int i = v; i != par[u]; i = par[i])
        cout << i << ' ';
    cout << '\n';
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    m = 2 * n - 3;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // build dfs spanning tree
    for (int v = 1; v <= n; v++) {
        if (!in[v]) {
            dep[v] = 1; dfs(v, 0);
        }
    }

    // print answer
    for (int len = 3; len <= n; len++) {
        if (cycle[len].size() < 2) continue;

        cout << len << '\n';
        print(cycle[len][0].second, cycle[len][0].first);
        print(cycle[len][1].second, cycle[len][1].first);

        return 0;
    }
    
    cout << 3 << '\n';
    print(cycle[3][0].second, cycle[3][0].first);
    
    vector<int> ans;
    ans.push_back(cycle[n - 1][0].second);
    ans.push_back(cycle[n - 1][0].first);
    auto [u, v] = cycle[n][0];
    if (u != ans[0] && u != ans[1])
        ans.push_back(u);
    else ans.push_back(v);
    
    for (auto& i : ans)
        cout << i << ' ';
}

// solution 2: random
/*#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[101010];
int in[101010], out[101010], dep[101010], par[101010];
vector<pair<int, int>> cycle[101010];

void init() {
    for (int i = 1; i <= n; i++) {
        in[i] = out[i] = dep[i] = par[i] = 0;
        cycle[i].clear();
    }
}

void dfs(int v, int prv) {
    in[v] = 1;

    par[v] = prv;
    dep[v] = dep[prv] + 1;
    for (auto& i : adj[v]) {
        if (prv == i) continue;
        if (!in[i]) dfs(i, v);
        else if (!out[i]) {
            cycle[dep[v] - dep[i] + 1].push_back({ i, v });
        }
    }

    out[v] = 1;
}

void print(int v, int u) {
    for (int i = v; i != par[u]; i = par[i])
        cout << i << ' ';
    cout << '\n';
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    m = 2 * n - 3;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    while (1) {
        // initialize
        init();

        // random
        for (int v = 1; v <= n; v++) {
            random_shuffle(adj[v].begin(), adj[v].end());
        }
        vector<int> order;
        for (int v = 1; v <= n; v++)
            order.push_back(v);
        random_shuffle(order.begin(), order.end());

        // build dfs spanning tree
        for (auto& v : order) {
            if (!in[v]) {
                dep[v] = 1; dfs(v, 0);
            }
        }

        // print answer
        for (int len = 3; len <= n; len++) {
            if (cycle[len].size() < 2) continue;

            cout << len << '\n';
            print(cycle[len][0].second, cycle[len][0].first);
            print(cycle[len][1].second, cycle[len][1].first);

            return 0;
        }
    }
}*/