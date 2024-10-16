#define _USE_MATH_DEFINES
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

const int MAXV = 55 * 55 * 2;

struct edge {
	int v;
	ll c, f;
	edge* dual; // pointer to reverse edge
	edge() : edge(-1, 0) {}
	edge(int v1, ll c1) : v(v1), c(c1), f(0), dual(nullptr) {}
	ll residual() {
		return c - f;
	}
	void addFlow(int f1) {
		f += f1;
		dual->f -= f1;
	}
};

int r, c, a[55][55], num[55][55], st, en;
vector<edge*> adj[MAXV + 5];
int prv[MAXV + 5];
edge* path[MAXV + 5];

void input() {
    cin >> r >> c;
    FOR(r) {
        string s; cin >> s;
        FOR(j, c) {
            if (s[j] == '.') a[i][j] = 0;
            if (s[j] == 'X') a[i][j] = 1;
        }
    }
}

void buildGraph() {
    int cnt = 0;
    FOR(r) {
        FOR(j, c) {
            if (a[i][j]) continue;
            if ((i + j) % 2 == 0) num[i][j] = cnt, cnt += 2;
            else num[i][j] = cnt++;
        }
    }
    st = cnt, en = cnt + 1;
    FOR(r) {
        FOR(j, c) {
            if (a[i][j]) continue;

            if (i % 2 == 0 && j % 2 == 1) {
                int v = num[i][j];
                edge* e1 = new edge(v, 1), * e2 = new edge(st, 0);
                e1->dual = e2, e2->dual = e1;
                adj[st].push_back(e1);
                adj[v].push_back(e2);
                FOR(k, 4) {
                    int y = i + dy[k], x = j + dx[k];
                    if (y < 0 || r <= y || x < 0 || c <= x) continue;
                    if (a[y][x]) continue;
                    int u = num[y][x];
                    edge* e3 = new edge(u, 1), * e4 = new edge(v, 0);
                    e3->dual = e4, e4->dual = e3;
                    adj[v].push_back(e3);
                    adj[u].push_back(e4);
                }
            }
            if (i % 2 == 1 && j % 2 == 0) {
                int v = num[i][j];
                edge* e1 = new edge(en, 1), * e2 = new edge(v, 0);
                e1->dual = e2, e2->dual = e1;
                adj[v].push_back(e1);
                adj[en].push_back(e2);
            }
            if ((i + j) % 2 == 0) {
                int v = num[i][j], u = num[i][j] + 1;
                edge* e1 = new edge(u, 1), * e2 = new edge(v, 0);
                e1->dual = e2, e2->dual = e1;
                adj[v].push_back(e1);
                adj[u].push_back(e2);
                FOR(k, 4) {
                    int y = i + dy[k], x = j + dx[k];
                    if (y < 0 || r <= y || x < 0 || c <= x) continue;
                    if (a[y][x]) continue;
                    if (y % 2 == 0) continue;
                    int z = num[y][x];
                    edge* e3 = new edge(z, 1), * e4 = new edge(u, 0);
                    e3->dual = e4, e4->dual = e3;
                    adj[u].push_back(e3);
                    adj[z].push_back(e4);
                }
            }
        }
    }
}

void bfs(int st, int en) {
	memset(prv, -1, sizeof(prv));

	queue<int> q;
	q.push(st);
	prv[st] = 0;

	while (!q.empty() && prv[en] == -1) {
		int now = q.front();
		q.pop();
		for (auto* e : adj[now]) {
			int next = e->v;
			if (prv[next] == -1 && e->residual() > 0) {
				q.push(next);
				prv[next] = now;
				path[next] = e;
			}
		}
	}
}

ll flow(int st, int en) {
	ll block = INF;
	for (int i = en; i != st; i = prv[i]) {
		block = min(block, path[i]->residual());
	}
	for (int i = en; i != st; i = prv[i]) {
		path[i]->addFlow(block);
	}
	return block;
}

ll maxFlow(int st, int en) {
	ll ret = 0;
	while (1) {
		bfs(st, en);
		if (prv[en] == -1) break;
		ret += flow(st, en);
	}
	return ret;
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

	input();

    buildGraph();

    cout << maxFlow(st, en);

	return 0;
}