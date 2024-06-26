#include <bits/stdc++.h>
using namespace std;

int n, m;
int s[303030], e[303030];
int in[303030], rin[303030];
vector<int> g[303030], rg[303030];
int vi[303030];

vector<pair<int, int>> idx[303030];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i] >> e[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
        in[v]++, rin[u]++;
    }

    // topological sort
    queue<int> q;
    for (int v = 1; v <= n; v++) {
        if (!in[v]) q.push(v);
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        vi[v] = 1;
        for (auto& i : g[v]) {
            in[i]--;
            if (!in[i]) q.push(i);
            s[i] = max(s[i], s[v] + 1);
        }
    }

    for (int v = 1; v <= n; v++) {
        if (!vi[v]) {
            cout << -1; return 0;
        }
    }

    for (int v = 1; v <= n; v++) {
        if (!rin[v]) q.push(v);
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto& i : rg[v]) {
            rin[i]--;
            if (!rin[i]) q.push(i);
            e[i] = min(e[i], e[v] - 1);
        }
    }

    // greedy
    for (int v = 1; v <= n; v++) {
        idx[s[v]].push_back({ e[v], v });
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> ans;
    for (int v = 1; v <= n; v++) {
        for (auto& i : idx[v]) pq.push(i);
        if (pq.empty() || pq.top().first < v) {
            cout << -1; return 0;
        }
        ans.push_back(pq.top().second);
        pq.pop();
    }

    for (auto& i : ans)
        cout << i << '\n';
}