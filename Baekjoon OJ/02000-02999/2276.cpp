#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int dy[] = { 1, -1, 0, 0 };
const int dx[] = { 0, 0, 1, -1 };

struct Node {
    ll h; int y, x;
    bool operator<(const Node& rhs) const{
        return h > rhs.h;
    }
};

int n, m;
ll a[303][303];

priority_queue<Node> pq;
int vi[303][303];
ll ans;

void dfs(ll h, int y, int x) {
    ans += h - a[y][x];
    a[y][x] = h;
    vi[y][x] = 1;
    
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 1 || n < ny || nx < 1 || m < nx) continue;
        if (vi[ny][nx]) continue;

        if (a[ny][nx] > h) pq.push({ a[ny][nx], ny, nx });
        else dfs(h, ny, nx);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        pq.push({ a[i][1], i, 1 });
        pq.push({ a[i][m], i, m });
    }

    for (int i = 2; i < m; i++) {
        pq.push({ a[1][i], 1, i });
        pq.push({ a[n][i], n, i });
    }

    while (!pq.empty()) {
        ll h = pq.top().h;
        int y = pq.top().y, x = pq.top().x;
        pq.pop();

        dfs(h, y, x);
    }

    cout << ans;

    return 0;
}