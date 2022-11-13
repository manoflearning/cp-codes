#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int MAX = 1000 * 1001 + 1000 + 100;

inline int Hash(int y, int x) {
    return y * 1001 + x;
}

int n, sy, sx, ey, ex;
vt<string> a;

struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
		return w > rhs.w;
	}
};
vt<wv> adj[MAX];

void input() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i].resize(n + 1);
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 'P') {
                sy = i, sx = j;
            }
            if (a[i][j] == 'K') {
                ey = i, ex = j;
            }
        }
    }
}

const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

void qe(int y, int x) {
    for (int i = 0; i < 8; i++) {
        int ny = y, nx = x;
        while (1) {
            ny = ny + dy[i], nx = nx + dx[i];
            if (ny < 1 || n < ny || nx < 1 || n < nx) break;
            if (a[ny][nx] == '0') continue;
            
            int w = max(abs(ny - y), abs(nx - x));
            adj[Hash(y, x)].push_back({ w, Hash(ny, nx) });
            break;
        }
    }
}

void re(int y, int x) {
    for (int i = 0; i < 4; i++) {
        int ny = y, nx = x;
        while (1) {
            ny = ny + dy[i], nx = nx + dx[i];
            if (ny < 1 || n < ny || nx < 1 || n < nx) break;
            if (a[ny][nx] == '0') continue;
            
            int w = max(abs(ny - y), abs(nx - x));
            adj[Hash(y, x)].push_back({ w, Hash(ny, nx) });
            break;
        }
    }
}

void be(int y, int x) {
    for (int i = 4; i < 8; i++) {
        int ny = y, nx = x;
        while (1) {
            ny = ny + dy[i], nx = nx + dx[i];
            if (ny < 1 || n < ny || nx < 1 || n < nx) break;
            if (a[ny][nx] == '0') continue;
            
            int w = max(abs(ny - y), abs(nx - x));
            adj[Hash(y, x)].push_back({ w, Hash(ny, nx) });
            break;
        }
    }
}

void ne(int y, int x) {
    const int dyn[] = { 2, 2, 1, 1, -2, -2, -1, -1 };
    const int dxn[] = { 1, -1, 2, -2, 1, -1, 2, -2 };

    for (int i = 0; i < 8; i++) {
        int ny = y + dyn[i], nx = x + dxn[i];
        if (ny < 1 || n < ny || nx < 1 || n < nx) continue;
        if (a[ny][nx] == '0') continue;
        adj[Hash(y, x)].push_back({ 2, Hash(ny, nx) });
    }
}

void pe(int y, int x) {
    for (int i = 0; i < 8; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 1 || n < ny || nx < 1 || n < nx) continue;
        if (a[ny][nx] == '0') continue;
        adj[Hash(y, x)].push_back({ 1, Hash(ny, nx) });
    }
}

void buildGraph() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == '0') continue;

            if (a[i][j] == 'Q') qe(i, j);
            else if (a[i][j] == 'R') re(i, j);
            else if (a[i][j] == 'B') be(i, j);
            else if (a[i][j] == 'N') ne(i, j);
            //else if (a[i][j] == 'K') ke(i, j);
            else if (a[i][j] == 'P') pe(i, j);
        }
    }
}

vector<ll> dist(MAX, INF);

ll dijkstra(int st) {
	priority_queue<wv> pq;
	pq.push({ 0, st });
	dist[st] = 0;
	while (!pq.empty()) {
		int v = pq.top().v;
		ll w = pq.top().w;
		pq.pop();
		if (w > dist[v]) continue;
        if (v == Hash(ey, ex)) return w;
		for (auto& i : adj[v]) {
			if (dist[i.v] > w + i.w) {
				dist[i.v] = w + i.w;
				pq.push({ w + i.w, i.v });
			}
		}
	}
    return -1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    buildGraph();
    
    assert(a[sy][sx] == 'P');
    assert(a[ey][ex] == 'K');

    cout << dijkstra(Hash(sy, sx));

    /*for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == '0') cout << 0 << ' ';
            else cout << dist[Hash(i, j)] << ' ';
        }
        cout << '\n';
    }*/

	return 0;
}