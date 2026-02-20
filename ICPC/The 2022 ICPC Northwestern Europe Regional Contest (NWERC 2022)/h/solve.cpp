#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

void dfs1(int now, int prv, const vector<vi> &g, vector<vi> &t) {
    for (const int nxt : g[now]) {
        if (nxt == prv) continue;
        t[now].push_back(nxt);
        dfs1(nxt, now, g, t);
    }
}

void dfs2(int now, const vector<vi> &t, vector<int> &dep) {
    for (const int nxt : t[now]) {
        dep[nxt] = dep[now] + 1;
        dfs2(nxt, t, dep);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<vi> g(n), t(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(0, -1, g, t);

    vi dep(n);
    dfs2(0, t, dep);

    vi ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) {
        return dep[i] > dep[j];
    });

    int ans = 0;

    vector<priority_queue<int>> sub(n);
    for (const int now : ord) {
        int chd1{}, chd2{};
        if (sz(t[now]) == 0) {
            sub[now].push(dep[now]);
        } else if (sz(t[now]) == 1) {
            const int chd = t[now][0];
            while (!sub[chd].empty() && dep[now] + 1 < sub[chd].top()) {
                sub[chd].pop();
            }
            sub[chd].push(dep[now]);
            sub[now].swap(sub[chd]);
        } else if (sz(t[now]) == 2) {
            int chd_l = t[now][0], chd_r = t[now][1];
            if (sub[chd_l].top() > sub[chd_r].top()) swap(chd_l, chd_r);

            while (sub[chd_l].top() + 1 < sub[chd_r].top()) sub[chd_r].pop();

            if (sz(sub[chd_l]) > sz(sub[chd_r])) swap(chd_l, chd_r);

            while (!sub[chd_l].empty()) {
                sub[chd_r].push(sub[chd_l].top());
                sub[chd_l].pop();
            }
            sub[chd_r].push(dep[now]);
            sub[now].swap(sub[chd_r]);
        } else { assert(0); }
    }

    cout << n - sz(sub[0]) << '\n';
}
