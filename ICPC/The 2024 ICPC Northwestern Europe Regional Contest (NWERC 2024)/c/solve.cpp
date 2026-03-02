#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

struct Point {
    int x, y;
    bool operator==(Point p) const {
        return tie(x, y) == tie(p.x, p.y);
    }
    bool operator!=(Point p) const {
        return tie(x, y) != tie(p.x, p.y);
    }
    bool operator<(Point p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
};

void floydWarshall(vector<vector<ll>> &m) {
    const int n = sz(m);
    rep(i, 0, n) m[i][i] = min(m[i][i], 0ll);
    rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
        if (m[i][k] != INF && m[k][j] != INF) {
            auto newDist = max<ll>(m[i][k] + m[k][j], -INF);
            m[i][j] = min<ll>(m[i][j], newDist);
        }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    vector<Point> a(5);
    for (auto &i : a) { cin >> i.x >> i.y; }

    set<Point> vis;
    for (auto &i : a) vis.insert(i);

    vector<Point> p;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            const Point k{a[i].x, a[j].y};
            if (!vis.count(k)) p.push_back(k);
        }
    }
    sort(all(p));
    p.erase(unique(all(p)), p.end());

    ll ans = INF;
    for (int bit = 0; bit < (1 << sz(p)); bit++) {
        if (__builtin_popcount(bit) > 10) continue;

        vector<Point> q;
        for (auto &i : a) q.push_back(i);
        for (int b = 0; b < sz(p); b++) {
            if (bit & (1 << b)) {
                q.push_back(p[b]);
            }
        }

        unordered_map<int, vector<pii>> mp_x, mp_y;
        for (int i = 0; i < sz(q); i++) {
            mp_x[q[i].x].push_back({q[i].y, i});
            mp_y[q[i].y].push_back({q[i].x, i});
        }

        vector<vector<ll>> m(sz(q), vector<ll>(sz(q), INF));

        ll res = 0;
        for (auto &[_, ys] : mp_x) {
            sort(all(ys));
            for (int i = 0; i + 1 < sz(ys); i++) {
                m[ys[i].second][ys[i + 1].second] = ys[i + 1].first - ys[i].first;
                m[ys[i + 1].second][ys[i].second] = ys[i + 1].first - ys[i].first;
                res += ys[i + 1].first - ys[i].first;
            }
        }
        for (auto &[_, xs] : mp_y) {
            sort(all(xs));
            for (int i = 0; i + 1 < sz(xs); i++) {
                m[xs[i].second][xs[i + 1].second] = xs[i + 1].first - xs[i].first;
                m[xs[i + 1].second][xs[i].second] = xs[i + 1].first - xs[i].first;
                res += xs[i + 1].first - xs[i].first;
            }
        }

        if (ans < res) continue;

        floydWarshall(m);

        bool yes = 1;
        for (int i = 0; i < 5; i++) {
            for (int j = i + 1; j < 5; j++) {
                if (abs(q[i].x - q[j].x) + abs(q[i].y - q[j].y) < m[i][j]) {
                    yes = 0, i = j = 5;
                    break;
                }
            }
        }
        if (yes) {
            ans = min(ans, res);
        }
    }
    cout << ans << '\n';
}
