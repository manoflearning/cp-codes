#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr ll dx[] = {1, -1, 1, -1};
constexpr ll dy[] = {1, 1, -1, -1};

constexpr int N = 1010;

ll cnt[N];

struct union_find {
    vector<int> uf;
    void build() {
        uf.resize(N, -1);
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
} uf;

int n, p, q;
vector<int> a, b;

bool vis[N][N];

void no() {
    cout << "N";
    exit(0);
}

void update(int u, int v) {
    vis[u][v] = vis[v][u] = 1;
}

void circuit() {
    for (int v = 1; v <= n; v++) {
        int deg = 0;
        for (int u = 1; u <= n; u++) {
            if (!vis[u][v]) deg++;
        }
        if (deg % 2 == 1) {
            no();
        }
    }
}
void path(int st, int en) {
    if (st == en) {
        circuit();
        return;
    }

    for (int v = 1; v <= n; v++) {
        int deg = 0;
        for (int u = 1; u <= n; u++) {
            if (!vis[u][v]) deg++;
        }

        if (v == st || v == en) {
            if (deg % 2 == 0) no();
        } else {
            if (deg % 2 == 1) no();
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    cin >> p;
    a.resize(p);
    for (auto &i : a) cin >> i;
    cin >> q;
    b.resize(q);
    for (auto &i : b) cin >> i;

    for (int v = 1; v <= n; v++) vis[v][v] = 1;

    for (int i = 0; i + 1 < sz(a); i++) {
        if (vis[a[i]][a[i + 1]]) no();
        update(a[i], a[i + 1]);
    }
    for (int i = 0; i + 1 < sz(b); i++) {
        if (vis[b[i]][b[i + 1]]) no();
        update(b[i], b[i + 1]);
    }

    if (n == 2) {
        if (!a.empty() && !b.empty()) {
            if (vis[a.back()][b.front()]) no();
        }
        cout << "Y";
        exit(0);
    }

    uf.build();
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (vis[u][v]) continue;
            uf.merge(u, v);
            cnt[u]++;
            cnt[v]++;
        }
    }

    ll last=-1;
    for(int u=1; u<=n; u++) {
        if(cnt[u]==0) continue;

        if(last==-1) {
            last=u;
            continue;
        }

        if(uf.find(u)!=uf.find(last)) no();
    }

    if (n % 2 == 0) no();

    if (a.empty() && b.empty()) {
        circuit();
    } else if (a.empty() || b.empty()) {
        if (a.empty()) {
            int st = b.front(), en = b.back();
            if (sz(b) != (ll)n * (n - 1) / 2 + 1 && (cnt[st] == 0 || cnt[en] == 0)) no();
            path(st, en);
        } else {
            int st = a.back(), en = a.front();
            if (sz(a) != (ll)n * (n - 1) / 2 + 1 && (cnt[st] == 0 || cnt[en] == 0)) no();
            path(st, en);
        }
    } else {
        int st = a.back(), en = b.front();
        if (st == en && (ll)n * (n - 1) / 2 <= sz(a) + sz(b) - 1) no();
        if (cnt[st] == 0 || cnt[en] == 0) no();
        path(st, en);
    }

    cout << "Y";
}