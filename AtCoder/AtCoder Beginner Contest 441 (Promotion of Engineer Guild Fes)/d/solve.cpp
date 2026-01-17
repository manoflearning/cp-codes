#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, m, l;
ll s, t;

vector<vector<pair<ll, int>>> adj;
vector<int> ans;

void bt(int cnt, int now, ll w) {
    if (cnt == l) {
        if (s <= w && w <= t) ans.push_back(now);
        return;
    }

    for (pair<ll, int> i : adj[now]) {
        const auto [c, nxt] = i;
        bt(cnt + 1, nxt, w + c);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    
    cin >> n >> m >> l >> s >> t;
    adj.assign(n + 1, vector<pair<ll, int>>{});
    for (int i = 0; i < m; i++) {
        int u, v; ll c;
        cin >> u >> v >> c;
        adj[u].push_back({c, v});
    }

    bt(0, 1, 0);

    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());

    for (auto &i : ans) cout << i << ' ';
    cout << '\n';
}