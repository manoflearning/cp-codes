#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n;
vector<int> t[4040];
int siz[4040];

void dfs(int v, int prv) {
    siz[v] = 1;
    for (auto& i : t[v]) {
        if (i == prv) continue;
        dfs(i, v);
        siz[v] += siz[i];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}