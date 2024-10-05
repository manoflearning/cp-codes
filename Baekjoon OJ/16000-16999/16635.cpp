#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 101;
const int MAXA = 101, MAXB = 101;
const int INF = 1e9 + 7;

int n, k;
int a[MAXN][MAXN];

bool col_vis[MAXN][MAXN];

int A[MAXA], B[MAXB], dist[MAXA];
bool used[MAXA];
vector<int> adj[MAXA];

void input() {
    cin >> n >> k;
    for (int y = 0; y < k; y++) {
        for (int x = 0; x < n; x++) {
            cin >> a[y][x];
        }
    }
}

bool is_valid() {
    for (int y = 0; y < k; y++) {
        set<int> st;
        for (int x = 0; x < n; x++) {
            st.insert(a[y][x]);
        }
        if (sz(st) != n) return 0;
    }
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < k; y++) {
            if (col_vis[x][a[y][x]]) return 0;
            col_vis[x][a[y][x]] = 1;
        }
    }
    return 1;
}

inline int Hash(int y, int x) { return y * 100 + x; };

void graph_modeling(int row) {
    for (int i = 0; i < MAXA; i++)
        adj[i].clear();

    for (int col = 0; col < n; col++) {
        for (int val = 1; val <= n; val++) {
            if (col_vis[col][val]) continue;

            int p = col;
            int q = val - 1;
            adj[p].push_back(q);
        }
    }
}

void get_answer(int row) {
    for (int col = 0; col < n; col++) {
        int p = col;
        if (A[p] == -1 || !used[p]) continue;

        a[row][col] = A[p] + 1;
        col_vis[col][a[row][col]] = 1;
    }
}

void bfs() {
	queue<int> q;
	for (int i = 0; i < MAXA; i++) {
		if (!used[i]) {
			dist[i] = 0;
			q.push(i);
		}
		else dist[i] = INF;
	}
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (int b : adj[a]) {
			if (B[b] != -1 && dist[B[b]] == INF) {
				dist[B[b]] = dist[a] + 1;
				q.push(B[b]);
			}
		}
	}
}
bool dfs(int a) {
	for (int b : adj[a]) {
		if (B[b] == -1 || (dist[B[b]] == dist[a] + 1 && dfs(B[b]))) {
			used[a] = true;
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}
int hopcroft() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
    memset(dist, 0, sizeof(dist));
    memset(used, 0, sizeof(used));
	int ret = 0;
	while (true) {
		bfs();
		int flow = 0;
		for (int i = 0; i < MAXA; i++)
			if (!used[i] && dfs(i)) flow++;
		if (flow == 0) break;
		ret += flow;
	}
	return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (!is_valid()) {
        cout << "no\n";
        exit(0);
    }

    for (int row = k; row < n; row++) {
        graph_modeling(row);

        int tot = hopcroft();
        assert(tot == n);

        get_answer(row);
    }
    
    cout << "yes\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}
