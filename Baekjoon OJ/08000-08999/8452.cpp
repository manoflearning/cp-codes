#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

struct Query {
    char op;
    int v;
};

int n, m, q, vi[101010];
pii edge[101010];
vector<int> adj[1010], ans;
vector<Query> query;
int dist[1010];

void bfs(int st) {
    queue<int> q;
    q.push(st);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto& i : adj[v]) {
            if (dist[i] <= dist[v] + 1) continue;
            dist[i] = dist[v] + 1;
            q.push(i);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < 1010; i++) dist[i] = INF;

    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].fr >> edge[i].sc;
    }

    query.resize(q);
    for (auto& i : query) {
        cin >> i.op >> i.v;
        if (i.op == 'U') vi[i.v] = 1;
    }

    for (int i = 1; i <= m; i++) {
        if (vi[i]) continue;
        adj[edge[i].fr].push_back(edge[i].sc);
    }

    dist[1] = 0;
    bfs(1);
    
    for (int i = q - 1; i >= 0; i--) {
        auto it = query[i];
        if (it.op == 'U') {
            int u = edge[it.v].fr, v = edge[it.v].sc;
            adj[u].push_back(v);
            dist[v] = min(dist[v], dist[u] + 1);
            bfs(v);
        }
        else ans.push_back(dist[it.v]);
    }

    for (int i = sz(ans) - 1; i >= 0; i--) {
        cout << (ans[i] == INF ? -1 : ans[i]) << '\n';
    }

    return 0;
}