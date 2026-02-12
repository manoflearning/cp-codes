#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

struct Edge {
    int nxt, w;
};

int dfs(int now, const int x, vector<pair<int *, int>> &log, vector<int> &vis, vector<int> &fix, const vector<vector<Edge>> &g) {
    log.push_back({&vis[now], vis[now]});
    vis[now] = 1;

    if (fix[now] != -1) {
        if (fix[now] != x) return INF;
    } else {
        log.push_back({&fix[now], fix[now]});
        fix[now] = x;
    }

    int ret = x;
    for (const Edge &e : g[now]) {
        const int nx = ((e.w - x) % 3 + 3) % 3;
        if (vis[e.nxt]) {
            if (fix[e.nxt] != nx) return INF;
        } else {
            ret = min(INF, ret + dfs(e.nxt, nx, log, vis, fix, g));
        }
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int l, b;
    cin >> l >> b;

    string s; cin >> s;

    vector<vector<int>> a(l);
    for (int i = 0; i < b; i++) {
        int cnt; cin >> cnt;
        while (cnt--) {
            int j; cin >> j;
            j--;
            a[j].push_back(i);
        }
    }

    vector<vector<Edge>> g(b);
    vector<int> fix(b, -1);
    for (int i = 0; i < l; i++) {
        const int w = (s[i] == 'G' ? 2 : (s[i] == 'B' ? 1 : 0));
        if (sz(a[i]) == 2) {
            g[a[i][0]].push_back({a[i][1], w});
            g[a[i][1]].push_back({a[i][0], w});
        } else if (sz(a[i]) == 1) {
            if (fix[a[i][0]] == -1) {
                fix[a[i][0]] = w;
            } else {
                if (fix[a[i][0]] != w) {
                    cout << "impossible\n";
                    exit(0);
                }
            }
            
        } else {
            if (w > 0) {
                cout << "impossible\n";
                exit(0);
            }
        }
    }

    int ans = 0;

    vector<int> vis(b);
    for (int now = 0; now < b; now++) {
        if (vis[now]) continue;
        
        int opt = INF, opt_x = -1;

        vector<pair<int *, int>> log;
        for (int x = 0; x < 3; x++) {
            const int res = dfs(now, x, log, vis, fix, g);
            if (opt > res) {
                opt = res;
                opt_x = x;
            }
            while (!log.empty()) {
                *log.back().first = log.back().second;
                log.pop_back();
            }
        }
        if (opt == INF) {
            cout << "impossible\n";
            exit(0);
        }

        dfs(now, opt_x, log, vis, fix, g);
        ans += opt;
    }

    if (ans == INF) {
        cout << "impossible\n";
    } else {
        cout << ans << '\n';
    }
}
