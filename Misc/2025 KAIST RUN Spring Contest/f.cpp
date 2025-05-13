#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 2020;
const int M = N * (N - 1) / 2;

struct Point {
    ll x, y;
    bool operator==(const Point &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};
ll ccw(const Point &a, const Point &b, const Point &c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
bool is_cross(const Point &a, const Point &b, const Point &c, const Point &d) {
    ll ab = ccw(a, b, c) * ccw(a, b, d);
    ll cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        pll A = {a.x, a.y}, B = {b.x, b.y}, C = {c.x, c.y}, D = {d.x, d.y};
        if (A > B) swap(A, B);
        if (C > D) swap(C, D);
        return (A <= D && C <= B);
    } else return (ab <= 0 && cd <= 0);
}

int p3[12];

int n, m;
Point po[N];
vector<int> adj[N];
pll e[M];
int co[M];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    p3[0] = 1;
    for (int i = 1; i <= 12; i++) {
        p3[i] = 3 * p3[i - 1];
    }

    cin >> n;
    m = n * (n - 1) / 2;
    for (int i = 1; i <= n; i++) {
        cin >> po[i].x >> po[i].y;
    }

    int idx = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            e[idx++] = {i, j};
        }
    }
    assert(idx == m);

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (is_cross(po[e[i].fr], po[e[i].sc], po[e[j].fr], po[e[j].sc])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    // subtask 1
    if (n <= 5) {
        for (int bit = 0; bit < p3[m]; bit++) {
            int cnt1 = 0, cnt2 = 0;
            for (int i = 0; i < m; i++) {
                int w = bit % p3[i + 1] / p3[i];
                co[i] = w;
                cnt1 += (w == 1);
                cnt2 += (w == 2);
            }
            
            bool yes = 1;
            yes &= (cnt1 == n - 1);
            if (!yes) continue;
            yes &= (cnt2 == n - 1);
            if (!yes) continue;
            
            for (int w = 1; w <= 2; w++) {
                memset(vis, 0, sizeof(vis));
                vis_cnt = 0;
                dfs(1, w);
                yes &= (vis_cnt == n);
            }
            if (!yes) continue;

            for (int i = 0; i < m; i++) {
                if (!co[i]) continue;
                for (int j = i + 1; j < m; j++) {
                    if (!co[j]) continue;

                    yes &= !is_cross(po[e[i].fr], po[e[i].sc], po[e[j].fr], po[e[j].sc]);
                }
            }

            if (yes) {
                cout << 2 * n - 2 << '\n';
                for (int i = 0; i < m; i++) {
                    if (!co[i]) continue;
                    cout << e[i].fr << ' ' << e[i].sc << ' ' << (co[i] == 1 ? 'R' : 'B') << '\n';
                }
                exit(0);
            }
        }

        cout << -1;
    }
    // subtask 2
    else if (n <= 100) {

    }
    // subtask 3
    else {

    }
}
