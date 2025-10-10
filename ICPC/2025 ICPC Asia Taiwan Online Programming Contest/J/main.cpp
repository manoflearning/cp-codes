#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 202020;

int n, k;
struct Edge { ll w; int v; };
vector<Edge> adj[N];

void input() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
}

int cnt_rest_area = 0;
ll dfs(int v, int prv, const ll ub) {
    ll mx_len_fr = 0, mx_len_sc = 0;

    for (auto &i : adj[v]) {
        if (i.v == prv) continue;

        ll len = i.w + dfs(i.v, v, ub);
        if (len > ub) {
            cnt_rest_area++;
            len = i.w;
        }
        
        if (len >= mx_len_fr) {
            mx_len_sc = mx_len_fr;
            mx_len_fr = len;
        } else if (len >= mx_len_sc) {
            mx_len_sc = len;
        }
    }

    if (mx_len_fr + mx_len_sc > ub) {
        cnt_rest_area++;
        return 0;
    } else {
        return mx_len_fr;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();

    ll l = 0, r = 1e9 * N;

    for (int v = 1; v <= n; v++) {
        for (auto &i : adj[v]) l = max(l, i.w);
    }

    while (l < r) {
        ll mid = (l + r) >> 1;

        cnt_rest_area = 0;
        dfs(1, 0, mid);

        if (cnt_rest_area > k) l = mid + 1;
        else r = mid;
    }

    cout << l;
}
