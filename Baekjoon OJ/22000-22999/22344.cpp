#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct wv { ll w; int v; };
struct cbit { ll c; int bit; };

int n, m, vi[101010];
vector<wv> adj[101010];
cbit val[101010];
int po = 1;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dfs(int v, int prv) {
    vi[v] = 1;
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        
        if (vi[i.v]) {
            cbit du = { i.w - val[v].c, !val[v].bit };

            if (val[i.v].bit == du.bit) {
                if (val[i.v].c != du.c) po = 0;
            }
            else {
                
            }
        }
        else {
            val[i.v].bit = !val[v].bit;
            val[i.v].c = i.w - val[v].c;
            dfs(i.v, v);
        }
    }
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int v = 1; v <= n; v++) {
        if (!vi[v]) {
            dfs(v, 0);
        }
    }

    return 0;
}