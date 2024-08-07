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
const ll INF = 1e18 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct wv {
    ll w;
    int v;
};

struct wvcnt {
    ll w;
    int v, cnt;
    bool operator<(const wvcnt& rhs) const {
        return w > rhs.w;
    }
};

int n, m, k;
vt<wv> adj[10101];
ll dist[10101][22];

void init() {
    FOR(10101) {
        FOR(j, 22) {
            dist[i][j] = INF;
        }
    }
}

void input() {
    cin >> n >> m >> k;
    FOR(m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dijkstra() {
    priority_queue<wvcnt> pq;
    
    pq.push({ 0, 1, 0 });
    dist[1][0] = 0;

    while (sz(pq)) {
        int v = pq.top().v, cnt = pq.top().cnt;
        ll w = pq.top().w;
        pq.pop();

        if (w > dist[v][cnt]) continue;

        EACH(i, adj[v]) {
            if (dist[i.v][cnt] > w + i.w) {
                pq.push({ w + i.w, i.v, cnt });
                dist[i.v][cnt] = w + i.w;
            }
            if (cnt < k && dist[i.v][cnt + 1] > w) {
                pq.push({ w, i.v, cnt + 1 });
                dist[i.v][cnt + 1] = w;
            }
        }
    }
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
    
    init();

	input();

    dijkstra();

    ll ans = INF;
    FOR(i, k + 1) {
        ans = min(ans, dist[n][i]);
    }

    cout << ans;

	return 0;
}