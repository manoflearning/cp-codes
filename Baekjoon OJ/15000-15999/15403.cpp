#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;

int n;
int a[101010];
int idx[101010];
vector<int> adj[101010];
int ind[101010];
int ans[101010];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int vis[101010];
vector<int> topo;
void dfs(int v) {
    vis[v] = 1;
    for (auto& i : adj[v]) {
        if (!vis[i]) dfs(i);
    }
    topo.push_back(v);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(idx, -1, sizeof(idx));

    input();

    for (int v = n; v >= 1; v--) {
        if (idx[a[v] - 1] != -1) {
            adj[idx[a[v] - 1]].push_back(v);
            ind[v]++;
        }
        if (idx[a[v]] != -1) {
            adj[v].push_back(idx[a[v]]);
            ind[idx[a[v]]]++;
        }
        idx[a[v]] = v;
    }

    for (int v = 1; v <= n; v++) {
        sort(all(adj[v]));
        // sort(adj[v].rbegin(), adj[v].rend());
    }

    // queue<int> q;
    for (int v = 1; v <= n; v++) {
        if (!ind[v]) dfs(v);
    }

    reverse(all(topo));
    for (int i = 0; i < n; i++) {
        ans[topo[i]] = n - i;
    }

    // while (!q.empty()) {
    //     int v = q.front();
    //     q.pop();

    //     ans[v] = num--;

    //     for (auto& i : adj[v]) {
    //         ind[i]--;
    //         if (!ind[i]) {
    //             q.push(i);
    //         }
    //     }
    // }

    for (int v = 1; v <= n; v++) {
        cout << ans[v] << ' ';
    }
}