#include <bits/stdc++.h>
using namespace std;

int n, top = 1001;
vector<int> adj[2020];
vector<int> par(2020, -1);

int dfs(int v, int prv, int en) {
    if (v == en) return 0;
    int ret = 1e9 + 7;
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        ret = min(ret, 1 + dfs(i, v, en));
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

    cin >> n;
    vector<pair<int, pair<int, int>>> a;
    for (int i = 1; i < n; i++) {
        int w; cin >> w;
        a.push_back({ w, { i, i + 1 } });
    }

    while (!a.empty()) {
        vector<pair<int, pair<int, int>>> tmp;
        for (auto& i : a) {
            auto& [u, v] = i.second;
            int& w = i.first;
            while (par[u] != -1) { u = par[u]; w--; }
            while (par[v] != -1) { v = par[v]; w--; }
            if (w == 2) {
                adj[u].push_back(top);
                adj[v].push_back(top);
                adj[top].push_back(u);
                adj[top].push_back(v);
                par[u] = par[v] = top++;
            }
            else tmp.push_back(i);
        }
        a = tmp;
    }

    int st, en;
    cin >> st >> en;
    cout << dfs(st, -1, en);
}