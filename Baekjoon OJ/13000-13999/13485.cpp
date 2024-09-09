#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int INF = 1e9 + 7;

int n;
vector<string> a(10);
vector<vector<int>> dist;

void dijkstra() {
    dist.resize(10, vector<int>(n, INF));

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    dist[0][0] = 0;
    pq.push({ dist[0][0], 0, 0 });

    while (!pq.empty()) {
        auto [w, y, x] = pq.top();
        pq.pop();

        if (dist[y][x] < w) continue;

        for (int d = 0; d + y < 10 && d + x < n; d++) {
            int ny = y + d, nx = x + d;
            if (a[ny][nx] == 'X') break;
            if (dist[y][x] + 1 >= dist[ny][nx]) continue;
            dist[ny][nx] = dist[y][x] + 1;
            pq.push({ dist[ny][nx], ny, nx });
        }

        if (y == 0 && a[y][x + 1] == '.' && dist[y][x] < dist[y][x + 1]) {
            dist[y][x + 1] = dist[y][x];
            pq.push({ dist[y][x + 1], y, x + 1 });
        }

        if (y > 0 && a[y - 1][x + 1] == '.' && dist[y][x] < dist[y - 1][x + 1]) {
            dist[y - 1][x + 1] = dist[y][x];
            pq.push({ dist[y - 1][x + 1], y - 1, x + 1 });
        }
    }
}

vector<pii> ans;
void backtrace() {
    int opty = 0, optx = n - 1;
    for (int y = 1; y < 10; y++) {
        if (dist[opty][optx] > dist[y][n - 1]) {
            opty = y;
        }
    }

    cout << dist[opty][optx];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < 10; i++) cin >> a[10 - i - 1];

    dijkstra();
    
    backtrace();
}