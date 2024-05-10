#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

vector<int> uf(101010, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[V] = U;
}

int n, m;
int a[101010];
vector<int> adj[101010];
vector<pii> e;

int cnt_0[101010], cnt_1[101010];

vector<int> c;
int ans = -1;

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back({ u, v });
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void cc() {
    c.push_back(-1);
    for (int i = 1; i <= n; i++)
        c.push_back(a[i]);
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
}

void solve() {
    vector<int> ord;
    map<int, int> v_to_ord, wei_to_ord;
    for (int i = 1; i <= n; i++) {
        ord.push_back(i);
    }
    
    sort(ord.begin(), ord.end(), [&](int p1, int p2) {
        return a[p1] < a[p2];
    });

    for (int i = 0; i < n; i++) {
        v_to_ord[a[ord[i]]] = i;
        wei_to_ord[a[ord[i]]] = i;
    }

    // cnt_0
    int res = 0;
    for (int i = 0; i < n; i++) {
        res++;

        int v = ord[i];
        for (auto& i : adj[v]) {
            if (a[i] > a[v]) continue;
            if (find(i) == find(v)) continue;
            merge(i, v);
            res--;
        }

        cnt_0[i] = res;
    }

    // cnt_1
    uf.clear();
    uf.resize(101010, -1);

    res = 0;
    for (int i = n - 1; i >= 0; i--) {
        res++;

        int v = ord[i];
        for (auto& i : adj[v]) {
            if (a[i] < a[v]) continue;
            if (find(i) == find(v)) continue;
            merge(i, v);
            res--;
        }

        cnt_1[i] = res;
    }

    // get answer
    for (int i = 0; i < n; i++) {
        if (i + 1 < n && a[ord[i]] == a[ord[i + 1]]) continue;

        int x = cnt_0[i];
        int y = cnt_1[i + 1];

        if (x == 0 || y == 0) continue;
        
        int node = min(i + 1, n - (i + 1));
        if (x + y <= node + 1) {
            ans = a[ord[i]];
            break;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cc();

    if (sz(c) == 2) {
        cout << -1;
        return 0;
    }

    solve();

    cout << (ans == -1 ? ans : c[ans]);
}