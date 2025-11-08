#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int MOD = 1e9 + 7;

constexpr int dy[] = {0, 1, -1, 0};
constexpr int dx[] = {1, 0, 0, -1};

int h, w;
vector<string> s;
vector<vector<vector<ll>>> dist;

void init() {
    dist.clear();
}

void input() {
    cin >> h >> w;
    s.resize(h);
    for (auto &i : s) cin >> i;

    dist.resize(h, vector<vector<ll>>(w, vector<ll>(4, INF)));
}

void dijkstra() {
    struct node {
        ll w;
        int y, x, dir;
        bool operator<(const node &rhs) const {
            return w > rhs.w;
        }
    };

    priority_queue<node> pq;
    dist[0][0][0] = 0;
    pq.push({dist[0][0][0], 0, 0, 0});

    while (!pq.empty()) {
        auto [di, y, x, dir] = pq.top();
        pq.pop();

        if (dist[y][x][dir] < di) continue;

        // cout << y << ' ' << x << ' ' << dir << ' ' << di << '\n';

        for (int ndir = 0; ndir < 4; ndir++) {
            if (min(dir, ndir) == 0 && max(dir, ndir) == 3) continue;
            if (min(dir, ndir) == 1 && max(dir, ndir) == 2) continue;

            int ny = y + dy[ndir], nx = x + dx[ndir];
            if (ny < 0 || h <= ny || nx < 0 || w <= nx) continue;

            bool chng = 0;
            if (s[y][x] == 'A') {
                chng = (dir != ndir);
            } else if (s[y][x] == 'B') {
                chng = ((dir ^ 1) != ndir);
            } else if (s[y][x] == 'C') {
                chng = ((dir < 2 ? dir + 2 : dir - 2) != ndir);
            }

            if (dist[ny][nx][ndir] <= di + chng) continue;

            dist[ny][nx][ndir] = di + chng;
            pq.push({dist[ny][nx][ndir], ny, nx, ndir});
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        dijkstra();

        ll ans = INF;
        for (int dir = 0; dir < 4; dir++) {
            bool chng = 0;
            if (s[h - 1][w - 1] == 'A') {
                chng = (dir != 0);
            } else if (s[h - 1][w - 1] == 'B') {
                chng = ((dir ^ 1) != 0);
            } else if (s[h - 1][w - 1] == 'C') {
                chng = ((dir < 2 ? dir + 2 : dir - 2) != 0);
            }

            ans = min(ans, dist[h - 1][w - 1][dir] + chng);
        }
        cout << ans << '\n';
    }
}