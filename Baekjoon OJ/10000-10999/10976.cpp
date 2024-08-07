#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXV = 202;

int N, M, st = 0, en = MAXV + 1;
vector<int> adj[MAXV];
int c[MAXV][MAXV], f[MAXV][MAXV];
int level[MAXV], work[MAXV];

void init() {
    FOR(MAXV) {
        adj[i].clear();
        FOR(j, MAXV) {
            c[i][j] = f[i][j] = 0;
        }
        level[i] = work[i] = 0;
    }
}

void input() {
	cin >> N >> M;
    st = 1, en = N;
    FOR(M) {
        int u, v;
        cin >> u >> v;

        if (u == 1 || v == N) c[u][v] = 1;
        else c[u][v] = INF;

        adj[u].push_back(v);
        adj[v].push_back(u);
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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	FOR(tt, 1, tc + 1) {
        init();

		input();

        int total = dinic();
        cout << total << '\n';
	}

	return 0;
}