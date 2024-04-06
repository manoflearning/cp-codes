// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int H, W;
string A[202];
int sty = -1, stx = -1, eny = -1, enx = -1;

int N, E[202][202];
int vis[202][202];

void init() {
    memset(vis, -1, sizeof(vis));
}

void input() {
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        cin >> A[i];
        for (int j = 0; j < W; j++) {
            if (A[i][j] == 'S') {
                sty = i, stx = j;
            }
            if (A[i][j] == 'T') {
                eny = i, enx = j;
            }
        }
    }

    cin >> N;
    for (int i = 0; i < N; i++) {
        int y, x, w;
        cin >> y >> x >> w;
        y--, x--;
        E[y][x] = w;
    }
}

struct Node {
    int y, x, w;
    bool operator<(const Node& rhs) const {
        return w < rhs.w;
    }
};
void solve() {
    priority_queue<Node> pq;
    vis[sty][stx] = E[sty][stx];
    pq.push({ sty, stx, E[sty][stx] });

    while (!pq.empty()) {
        auto [y, x, w] = pq.top();
        pq.pop();

        if (w < vis[y][x]) continue;
        if (w == 0) continue;

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (ny < 0 || H <= ny || nx < 0 || W <= nx) continue;
            if (A[ny][nx] == '#') continue;
            if (w - 1 <= vis[ny][nx]) continue;
            
            int nw = max(w - 1, E[ny][nx]);
            
            vis[ny][nx] = nw;
            pq.push({ ny, nx, nw });
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

    init();

    input();

    solve();

    cout << (vis[eny][enx] == -1 ? "No" : "Yes");
}