#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int n, m;
ll len;
struct wv { ll w; int v; };
vector<wv> adj[101010];

void input() {
    cin >> n >> m >> len;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

ll dp1[101010], dp2[101010];
void dfs1(int v, int prv) {
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        dfs1(i.v, v);
        dp1[v] = max(dp1[v], i.w + dp1[i.v]);
    }
}
void dfs2(int v, int prv) {
    vector<pll> arr;
    for (auto& i : adj[v]) {
        if (i.v == prv) 
            arr.push_back({ dp1[i.v], i.v });
    }
    
    if (sz(arr) == 1) {

    }

    sort(arr.rbegin(), arr.rend());
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
}