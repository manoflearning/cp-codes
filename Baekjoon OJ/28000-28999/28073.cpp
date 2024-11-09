#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 2020202;

int n, m;
char st, en;
string w;
vector<int> adj[MAXN];

int dist[MAXN], prv[MAXN];

void input() {
    cin >> n >> m;
    cin >> st >> en;
    cin >> w;
    w = "*" + w;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

struct State {
    int di;
    char c;
    vector<int> vs;
};
queue<State> qu;

void bfs() {
    memset(dist, -1, sizeof(dist));

    State source_state;
    source_state.di = 0;
    source_state.c = st;
    for (int v = 1; v <= n; v++) {
        if (w[v] == st) {
            dist[v] = 0;
            prv[v] = -1;
            source_state.vs.push_back(v);
        }
    }
    qu.push(source_state);

    while (!qu.empty()) {
        auto state = qu.front();
        qu.pop();

        bool updated = 0;
        for (int c = 0; c < 26; c++) {
            State nxt;
            nxt.di = state.di + 1;
            nxt.c = (c + 'A');

            for (auto v : state.vs) {
                if (w[v] == en) {
                    string ans(dist[v] + 1, '*');
                    int p = sz(ans) - 1, idx = v;
                    while (p >= 0) {
                        ans[p--] = w[idx];
                        idx = prv[idx];
                    }
                    cout << ans;
                    exit(0);
                }

                for (auto &i : adj[v]) {
                    if (dist[i] != -1 || w[i] != nxt.c) continue;
                    dist[i] = 1 + dist[v];
                    prv[i] = v;
                    nxt.vs.push_back(i);
                    updated = 1;
                }
            }
            if (!nxt.vs.empty()) qu.push(nxt);
        }
    }

    cout << "Aaak!";
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    bfs();
}
