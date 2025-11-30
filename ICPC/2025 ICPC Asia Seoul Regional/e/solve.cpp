#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 5050;

int n;
vector<int> adj[N];

ll sum[N];
ll ans = 0;

void dfs(int v, int prv) {
    vector<ll> arr;

    sum[v] = 1;
    for (const int u : adj[v]) {
        if (u == prv) continue;
        dfs(u, v);
        sum[v] += sum[u];
        arr.push_back(sum[u]);
    }

    sort(arr.rbegin(), arr.rend());

    if (v == 1) {
        for (int i = 0; i < sz(arr); i++) {
            ans += (i / 2) * arr[i];
        }
    } else {
        for (int i = 1; i < sz(arr); i++) {
            ans += ((i + 1) / 2) * arr[i];
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1);

    cout << ans + (n - 1);
}