#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
vector<vector<int>> t;
vector<int> dep, cnt, cnt_w_chd;

void init() {
    t.clear();
}

void input() {
    cin >> n;
    t.assign(n + 1, vector<int>());
    dep.assign(n + 1, 0);
    cnt.assign(n + 1, 0);
    cnt_w_chd.assign(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    dep[v] = dep[prv] + 1;
    cnt[dep[v]]++;
    if (v == 1 || sz(t[v]) > 1) cnt_w_chd[dep[v]]++;
    for (auto &i : t[v]) {
        if (i != prv) dfs(i, v);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        dfs(1, 0);

        int ans = cnt[2] + 1;
        for (int i = 2; i <= n; i++) {
            ans = max(ans, cnt[i] + (cnt_w_chd[i - 1] == 1));
        }
        cout << ans << '\n';
    }
}
