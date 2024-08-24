#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

const int N = 101010;

int n, m;
ll d;
int a[N];
struct Edge {
    int u, v, l;
};
vector<Edge> e;

// refers to the following github link:
// https://github.com/manoflearning/cp-reference-codes/blob/master/reference-codes/1-data-structure/union_find.cpp
struct UF {
    vector<ll> uf;
    void init(int N) {
        uf.clear();
        uf.resize(N + 1, -1);
        for (int i = 1; i <= N; i++) {
            uf[i] = -a[i];
        }
    }
    int find(int v) {
        if (uf[v] < 0) return v;
        return uf[v] = find(uf[v]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] += uf[V];
        uf[V] = U;
    }
}uf;

void input() {
    cin >> n >> m >> d;
    for (int i = 1; i <= n; i++) cin >> a[i];
    e.resize(m);
    for (auto& i : e)
        cin >> i.u >> i.v >> i.l;
}

ll f(int c) {
    uf.init(n + 1);
    for (auto& i : e) {
        if (i.l <= c) uf.merge(i.u, i.v);
    }

    ll ret = 0;
    for (int i = 1; i <= n; i++) {
        ret = max(ret, -uf.uf[uf.find(i)]);
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

    input();

    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int u, v, l;
            cin >> u >> v >> l;
            e.push_back({ u, v, l });
        }
        else if (op == 2) {
            int k; cin >> k;
            cin >> a[k];
        }
        else if (op == 3) {
            cin >> d;
        }
        else if (op == 4) {
            int l = 0, r = 1'000'000 + 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (f(mid) >= d) r = mid;
                else l = mid + 1;
            }
            if (l == 0) cout << -1 << '\n';
            else if (l == 1'000'000 + 1) cout << -2 << '\n';
            else cout << l << '\n';
        }
    }
}
