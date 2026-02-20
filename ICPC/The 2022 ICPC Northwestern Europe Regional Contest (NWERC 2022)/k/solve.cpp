#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int dfs(int now, int prv, const vector<vi> &g, vector<int> &co) {
    int ret = 0;
    co[now] = 1;
    for (const int nxt : g[now]) {
        if (co[nxt]) {
            if (co[nxt] == 1 && nxt != prv) ret |= 1;
            else continue;
        } else ret |= dfs(nxt, now, g, co);
    }
    co[now] = 2;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<pii> a(n);
    for (auto &i : a) {
        cin >> i.first >> i.second;
        i.first--, i.second--;
        if (i.first > i.second) swap(i.first, i.second);
    }

    sort(all(a));
    a.erase(unique(all(a)), a.end());

    vector<int> cnt(k);
    for (auto &i : a) {
        cnt[i.first]++, cnt[i.second]++;
    }

    vector<vi> g(k);
    for (auto &[u, v] : a) {
        if (cnt[u] == 1 || cnt[v] == 1) continue;
        if (u == v) continue;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool yes = 1;
    for (int i = 0; i < k; i++) {
        yes &= (sz(g[i]) <= 2);
    }

    vector<int> co(k);
    int cnt_cycles{}, cnt_comps{};
    for (int now = 0; now < k; now++) {
        if (co[now]) continue;
        if (cnt[now] <= 1) continue;

        cnt_cycles += dfs(now, -1, g, co);
        cnt_comps++;
    }
    
    for (const auto [u, v] : a) {
        if (cnt[u] == 1 && cnt[v] == 1) cnt_comps++;
    }

    yes &= (cnt_cycles <= 1);
    yes &= (cnt_comps == 1 || cnt_cycles == 0);

    cout << (yes ? "possible" : "impossible") << '\n';
}
