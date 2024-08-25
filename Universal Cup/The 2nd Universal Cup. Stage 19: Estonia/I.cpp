#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int N = 202020;

int n, m;
struct Edge {
    ll w; int u, v;
    bool operator<(const Edge& rhs) const {
        return w < rhs.w;
    }
};
vector<Edge> e;
int rst = -1, ren = -1, rw = -1;

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
        if (U != V) return;
        uf[U] += uf[V];
        uf[V] = U;
    }
}uf;

void init() {
    for (int i = 1; i <= n; i++) {
        rst = ren = rw = -1;
    }
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u > v) rst = u, ren = v, rw = w;
        else e.push_back({ w, u, v });
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        input();

        sort(e.begin(), e.end());

        ll ans = 0;

        uf.init(n);
        for (auto& [w, u, v] : e) {
            if (uf.find(u) == uf.find(v)) continue;
            uf.merge(u, v);
            ans += w;
        }

        

        init();
    }
}