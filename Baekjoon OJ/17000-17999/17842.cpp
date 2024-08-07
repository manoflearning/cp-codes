#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n;
vector<int> adj[202020];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (n == 2) {
        cout << 1;
        return 0;
    }

    int cnt = 0;
    for (int v = 0; v < n; v++) {
        if (sz(adj[v]) == 1) cnt++;
    }

    cout << (cnt + 1) / 2;
}