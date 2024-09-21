#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 111, MAXM = 111;
const ll INF = 1e9;

int n, m;
vector<ll> w(MAXN), l(MAXN), t(MAXM);

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> l[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> t[i];
}

int c[505][505], f[505][505];
vector<int> adj[505];
int level[505], work[505];
int st = -1, en = -1;

void add_edge(int u, int v) {
    c[u][v] = 1;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void graph_modeling() {
    for (int i = 1; i <= n; i++) {
        if (w[i] == 0) {
            add_edge(0, i);
        }
    }

    for (int i = 1; i <= n; i++) {
        add_edge(i, n + i);

        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            if (l[i] >= w[j] && w[j] > 0) {
                add_edge(n + i, j);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (l[i] >= t[j]) {
                add_edge(n + i, 2 * n + j);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        add_edge(2 * n + i, 2 * n + m + 1);
    }
}

void bfs() {
	memset(level, -1, sizeof(level));
	level[st] = 0;
	queue<int> q;
	q.push(st);
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (int next : adj[now]) {
			if (level[next] == -1 && c[now][next] - f[now][next] > 0) {
				level[next] = level[now] + 1;
				q.push(next);
			}
		}
	}
}
int dfs(int now, int flow) {
	if (now == en) return flow;
	for (int& i = work[now]; i < adj[now].size(); i++) {
		int next = adj[now][i];
		if (level[next] == level[now] + 1 && c[now][next] - f[now][next] > 0) {
			int df = dfs(next, min(c[now][next] - f[now][next], flow));
			if (df > 0) {
				f[now][next] += df;
				f[next][now] -= df;
				return df;
			}
		}
	}
	return 0;
}
int dinic() {
	int ret = 0;
	while (true) {
		bfs();
		if (level[en] == -1) break;
		memset(work, 0, sizeof(work));
		while (true) {
			int flow = dfs(st, INF);
			if (flow == 0) break;
			ret += flow;
		}
	}
	return ret;
}

vector<int> arr;
vector<vector<int>> ans(MAXM);
vector<bool> vis(505);

void get_answer(int v) {
    vis[v] = 1;
    if (2 * n + 1 <= v && v <= 2 * n + m) {
        ans[v - 2 * n] = arr;
        return;
    }

    for (auto& i : adj[v]) {
        if (vis[i]) continue;
        if (c[v][i] == 1 && f[v][i] == 1) {
            if (1 <= i && i <= n) {
                arr.push_back(i);
            }
            get_answer(i);
            if (1 <= i && i <= n) {
                arr.pop_back();
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    graph_modeling();
    
    st = 0, en = 2 * n + m + 1;
    ll total = dinic();

    if (total == m) {
        get_answer(0);

        for (int i = 1; i <= m; i++) {
            for (auto& j : ans[i]) cout << j << ' ';
            cout << '\n';
        }
    } else {
        cout << "impossible";
    }
}
