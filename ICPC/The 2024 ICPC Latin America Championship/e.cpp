#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int n;
int st[2020], en[2020];
vector<int> adj[2020];

bool vis[2020];
int co[2020];

bool dfs(int v) {
    vis[v] = 1;

    int bit = 0;

    for (auto& i : adj[v]) {
        if (vis[i]) bit |= co[i];
    }

    if (bit == 3) return 0;
    co[v] = (bit == 1 ? 2 : 1);

    bool ret = 1;
    for (auto& i : adj[v]) {
        if (!vis[i]) ret &= dfs(i);
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

    cin >> n;
    for (int i = 1; i <= 2 * n; i++) {
        string s, t;
        cin >> s;
        for (int j = 1; j < sz(s); j++)
            t.push_back(s[j]);
        if (s[0] == '+') st[stoi(t)] = i;
        else en[stoi(t)] = i;
    }

    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            pii p1 = { st[u], en[u] };
            pii p2 = { st[v], en[v] };
            if (p1 > p2) swap(p1, p2);

            if (p2.fr < p1.sc && p1.sc < p2.sc) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
    }

    bool pos = 1;
    for (int v = 1; v <= n; v++) {
        if (!vis[v]) pos &= dfs(v);
    }

    if (!pos) { cout << '*'; return 0; }

    for (int i = 1; i <= n; i++) {
        cout << (co[i] == 1 ? 'G' : 'S');
    }
}