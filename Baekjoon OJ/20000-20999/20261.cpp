#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;

int n, m;
vector<int> adj[202020];
ll dp1[202020][2], dp2[101010][2][2];
vector<int> arr;

void init() {
    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < n + m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

ll f1(int v, int bit) {
    ll &ret = dp1[v][bit];
    if (ret != -1) return ret;

    ret = bit;

    for (auto &i : adj[v]) {
        if (i <= v || i < n) continue;

        ll res = INF;
        if (bit) {
            res = min(res, f1(i, 0));
            res = min(res, f1(i, 1));
        } else {
            res = min(res, f1(i, 1));
        }
        ret += res;
    }
    return ret;
}

ll f2(int i, int b1, int b2) {
    ll &ret = dp2[i][b1][b2];
    if (ret != -1) return ret;
    if (i == n) {
        if (b1 || b2) return ret = 0;
        else return ret = INF;
    }

    ret = INF;
    if (i == 0) {
        ret = min(ret, f2(i + 1, b1, b1) + f1(arr[i], b1));
    } else {
        if (b2) {
            ret = min(ret, f2(i + 1, b1, 0) + f1(arr[i], 0));
            ret = min(ret, f2(i + 1, b1, 1) + f1(arr[i], 1));
        } else {
            ret = min(ret, f2(i + 1, b1, 1) + f1(arr[i], 1));
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    int v = 0;
    vector<bool> vis(n);
    vis[v] = 1;
    while (1) {
        vis[v] = 1;
        arr.push_back(v);
        int nxt = -1;
        for (auto &i : adj[v]) {
            if (vis[i]) continue;
            if (n <= i) continue;
            nxt = i;
        }
        if (nxt == -1) break;
        v = nxt;
    }
    assert(sz(arr) == n);

    // for (auto &i : arr) {
    //     cout << i << ' ' << f1(i, 0) << ' ' << f1(i, 1) << '\n';
    // }

    ll ans = INF;
    ans = min(ans, f2(0, 0, 0));
    ans = min(ans, f2(0, 1, 1));
    cout << ans;
}
