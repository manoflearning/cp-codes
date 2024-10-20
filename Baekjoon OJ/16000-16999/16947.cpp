#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

struct Edge {
    int idx, v;
};

int n, vi[3030], isC[3030], banned;
vector<Edge> adj[3030];
pii e[3030];

void dfs(int v) {
    vi[v] = 1;
    for (auto i : adj[v]) {
        if (vi[i.v]) continue;
        if (i.idx == banned) continue;
        dfs(i.v);
    }
}

int bfs(int st) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(st);
    dist[st] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (isC[v]) return dist[v];

        for (auto i : adj[v]) {
            if (dist[i.v] == -1) {
                dist[i.v] = dist[v] + 1;
                q.push(i.v);
            }
        }
    }
    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({ i, v });
        adj[v].push_back({ i, u });
        e[i] = { u, v };
    }

    for (int i = 0; i < n; i++) {
        memset(vi, 0, sizeof(vi));
        banned = i;
        dfs(1);
        int bit = 1;
        for (int j = 1; j <= n; j++) {
            if (!vi[j]) bit = 0;
        }
        if (bit) isC[e[i].fr] = isC[e[i].sc] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (isC[i]) cout << 0 << ' ';
        else {
            cout << bfs(i) << ' ';
        }
    }

    return 0;
}