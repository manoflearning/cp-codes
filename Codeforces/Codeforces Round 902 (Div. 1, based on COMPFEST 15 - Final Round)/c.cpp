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

int n, a[N];

vector<int> adj[N], radj[N];
int ind[N];

bool is_circled[N];
bool vis[N];

void dfs(int v) {
    vis[v] = 1;
    if (!is_circled[v]) {
        is_circled[adj[v][0]] = 1;
    }
    for (auto u : adj[v]) {
        if (!vis[u]) dfs(u);
    }
}

int cnt_r[N], cnt_p[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        adj[i].push_back(a[i]);
        radj[a[i]].push_back(i);
        ind[a[i]]++;
    }

    queue<int> qu;
    for (int v = 1; v <= n; v++) {
        if (!ind[v]) qu.push(v);
    }

    while (!qu.empty()) {
        int v = qu.front();
        qu.pop();

        // DEGUG
        // cout << v << '\n';

        vis[v] = 1;

        if (!is_circled[v]) {
            is_circled[adj[v][0]] = 1;
        }

        for (auto u : adj[v]) {
            ind[u]--;
            if (!ind[u]) qu.push(u);
        }
    }

    for (int v = 1; v <= n; v++) {
        if (!vis[v] && is_circled[v]) dfs(v);
    }
    for (int v = 1; v <= n; v++) {
        if (!vis[v]) dfs(v);
    }

    vector<int> r;
    for (int i = 1; i <= n; i++) {
        if (!is_circled[i]) {
            r.push_back(a[i]);
            cnt_r[a[i]]++;
        } else {
            cnt_p[i]++;
        }
    }

    for (int v = 1; v <= n; v++) {
        for (int u : adj[v]) {
            if (!is_circled[v] && !is_circled[u]) {
                // cout << v << ' ' << u << '\n';
                assert(0);
            }
        }
    }

    // DEBUG
    // cout << sz(r) << '\n';
    // for (auto &i : r) cout << i << ' ';
    // cout << '\n';
    // cout << '\n';
    // for (auto &x : mp_r) cout << x << ' ';
    // cout << '\n';
    // for (auto &x : mp_p) cout << x << ' ';
    // cout << '\n';
    // cout << '\n';

    bool is_valid = 1;
    for (int i = 1; i <= n; i++) {
        is_valid &= (cnt_r[i] >= cnt_p[i]);
        is_valid &= (cnt_r[i] == 0 || (cnt_r[i] > 0 && cnt_p[i] > 0));
    }

    if (is_valid) {
        cout << sz(r) << '\n';
        for (auto &i : r) cout << i << ' ';
    } else {
        cout << -1 << '\n';
    }
}
