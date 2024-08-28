#include <bits/stdc++.h>
using namespace std;

struct UF {
    vector<int> uf;
    void init(int n) {
        uf.clear();
        uf.resize(n + 1, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] += uf[V];
        uf[V] = U;
    }
}uf;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    uf.init(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        uf.merge(u, v);
    }

    int ans = 0;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    for (int i = 0; i + 1 < n; i++) {
        if (uf.find(a[i]) != uf.find(a[i + 1])) ans++;
    }
    
    cout << ans;
}