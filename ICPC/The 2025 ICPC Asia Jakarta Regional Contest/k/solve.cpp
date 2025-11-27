#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) (x).begin(), (x).end()

constexpr int N = 303030;
constexpr int K = 303030;

int n, m, k, q;

unordered_map<int, unordered_set<int>> adj0u[N], adj1v[K], adj1co[N];

bool vis[N];
int ans;

void add_edge(int u, int v, int co) {
    if (vis[v]) return;

    if (!vis[u]) {
        adj0u[u][co].insert(v);
    } else {
        adj1v[v][co].insert(u);
        adj1co[co][u].insert(v);
    }
}

void move_0to1(int u) {
    assert(vis[u]);
    for (auto &i : adj0u[u]) {
        int co = i.first;
        for (auto &v : i.second) {
            if (!vis[v]) {
                adj1v[v][co].insert(u);
                adj1co[co][u].insert(v);
            }
        }
    }
    adj0u[u].clear();
}
void remove_1(int v) {
    assert(vis[v]);
    for (auto &i : adj1v[v]) {
        int co = i.first;
        for (auto &u : i.second) {
            assert(vis[u]);
            adj1co[co][u].erase(v);
            if (adj1co[co][u].empty()) adj1co[co].erase(u);
        }
    }
    adj1v[v].clear();
}

void remove_edge(int u, int v, int co) {
    adj0u[u][co].erase(v);
    if (adj0u[u][co].empty()) adj0u[u].erase(co);
    adj1v[v][co].erase(u);
    if (adj1v[v][co].empty()) adj1v[v].erase(co);
    adj1co[co][u].erase(v);
    if (adj1co[co][u].empty()) adj1co[co].erase(u);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k >> q;
    vis[1] = 1, ans++;
    for (int i = 0; i < m; i++) {
        int u, v, co;
        cin >> u >> v >> co;
        add_edge(u, v, co);
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int u, v, co;
            cin >> u >> v >> co;
            add_edge(u, v, co);
        } else if (op == 2) {
            int u, v, co;
            cin >> u >> v >> co;
            remove_edge(u, v, co);
        } else if (op == 3) {
            int co; cin >> co;

            vector<int> lazy_upd;
            for (auto &i : adj1co[co]) {
                int u = i.first;
                // assert(vis[u]);
                if (!vis[u]) {
                    continue;
                }
                for (auto &v : i.second) {
                    lazy_upd.push_back(v);
                    if (vis[v]) continue;
                    vis[v] = 1, ans++;
                }
            }

            sort(all(lazy_upd));
            lazy_upd.erase(unique(all(lazy_upd)), lazy_upd.end());

            for (auto &i : lazy_upd) {
                move_0to1(i);
                remove_1(i);
            }

            cout << ans << '\n';
        }
    }
}