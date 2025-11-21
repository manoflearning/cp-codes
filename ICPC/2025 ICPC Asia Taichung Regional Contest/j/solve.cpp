#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 505050;

int ans[N];

struct UF {
    vector<int> uf, siz, prv;
    void build(int n) {
        uf.resize(n + 1, -1);
        siz.resize(n + 1, 1);
        prv.resize(n + 1, 0);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void sub(int x, int h) {
        x = find(x);        

        ans[x - siz[x] + 1] += (h - prv[x]);
        ans[x + 1] -= (h - prv[x]);

        prv[x] = h;

        siz[x]--;
    }
    void merge(int u, int v, int h) {
        u = find(u), v = find(v);
        if (u > v) swap(u, v);

        ans[u - siz[u] + 1] += (h - prv[u]);
        ans[u + 1] -= (h - prv[u]);

        ans[v - siz[v] + 1] += (h - prv[v]);
        ans[v + 1] -= (h - prv[v]);
        
        uf[u] = v;
        siz[v] += siz[u];
        prv[v] = h;
    }
} uf;

int n;
ll a[N], h[N];

vector<int> ra[N], rh[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ra[a[i]].push_back(i);
    }
    for (int i = 1; i <= n - 1; i++) {
        cin >> h[i];
        rh[h[i]].push_back(i);
    }

    uf.build(n);
    
    for (int h = 0; h <= n; h++) {
        for (auto &i : rh[h]) uf.merge(i, i + 1, h);
        for (auto &i : ra[h]) uf.sub(i, h);
    }

    uf.sub(1, n);

    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
        cout << ans[i] << ' ';
    }
}
