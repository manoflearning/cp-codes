#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m;
struct Edge { int w, v; };
vector<Edge> adj[20];
int ans = INF;

int bf() {
    vector<int> upper(20 * (1 << n) + 20, INF);
    for (int st = 0; st < n; st++) {
        upper[n * (1 << st) + st] = 0;
    }

    bool update = 1;
    while (update) {
        update = 0;
        for (int now = 0; now < n * (1 << n) + n; now++) {
            if (upper[now] == INF) continue;
            int v = now % n, vbit = now / n;
            for (auto& i : adj[v]) {
                int next = n * (vbit | (1 << i.v)) + i.v;
                if (upper[next] > upper[now] + i.w) {
                    upper[next] = upper[now] + i.w;
                    update = 1;
                }
            }
        }
    }

    int ret = INF;
    for (int v = 0; v < n; v++) {
        ret = min(ret, upper[n * ((1 << n) - 1) + v]);
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

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({ w, v });
    }

    // for (int v = 0; v < n; v++) {
        // ans = min(ans, bf(v));
    // }
    ans = bf();
    if (ans == INF) cout << "No";
    else cout << ans;
}