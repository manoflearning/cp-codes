#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 2020;

int n, m, a, b;
struct Edge { ll w; int v; };
vector<Edge> adj[MAXN];
int k;
vector<int> v;

void input() {
    cin >> n >> m >> a >> b;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    cin >> k;
    v.resize(k);
    for (auto& i : v) cin >> i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
}
