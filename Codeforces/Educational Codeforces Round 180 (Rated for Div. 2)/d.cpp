#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;

int n, ind[N];
vector<pii> e;
vector<int> adj[N];
vector<pii> ans;

void init() {
    for (int i = 1; i <= n; i++) {
        ind[i] = 0;
        adj[i].clear();
    }
    e.clear();
    ans.clear();
}

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        ind[u]++, ind[v]++;
        e.push_back({u, v});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv, bool dir) {
    // dir = 0 => (v, prv)
    // dir = 1 => (prv, v)

    if (dir) {
        ans.push_back({prv, v});
    } else {
        ans.push_back({v, prv});
    }
    
    for (auto &i : adj[v]) {
        if (i != prv) dfs(i, v, !dir);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        for (int v = 1; v <= n; v++) {
            if (ind[v] == 2) {
                dfs(adj[v][0], v, 0);
                dfs(adj[v][1], v, 1);
                break;
            }
        }

        if (!ans.empty()) {
            cout << "YES\n";
            for (auto &[u, v] : ans) {
                cout << u << ' ' << v << '\n';
            }
        } else {
            cout << "NO\n";
        }
    }
}
