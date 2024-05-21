#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int sq = 232;

struct UF {
    vector<int> uf;
    void init(int N) {
        uf.clear();
        uf.resize(N + 1, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[V] = U;
    }
}uf;

int N, E, P;
vector<int> t[101010];
unordered_set<ll> edges;

void input() {
    cin >> N >> E >> P;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        t[u].push_back(v);
        edges.insert(u * 101010ll + v);
    }
}

ll case1(int x, const vector<int>& arr) {
    // total: O(sq^3)
    int ret = x;

    uf.init(x);
    for (int i = 0; i < x; i++) {
        for (int j = i + 1; j < x; j++) {
            int u = arr[i], v = arr[j];
            if (u > v) swap(u, v);

            if (!edges.count(u * 101010ll + v)) continue;
            if (uf.find(i) == uf.find(j)) continue;

            uf.merge(i, j);
            ret--;
        }
    }

    return ret;
}

vector<int> vis(101010, -1);

ll case2(int x, const vector<int>& arr) {
    // total: O(E) * O(P / sq) + O(10^5)
    int ret = x;

    for (int i = 0; i < sz(arr); i++) vis[arr[i]] = i;

    uf.init(x);
    for (auto& val : edges) {
        int u = val / 101010, v = val % 101010;
        if (vis[u] == -1 || vis[v] == -1) continue;
        if (uf.find(vis[u]) == uf.find(vis[v])) continue;
        uf.merge(vis[u], vis[v]);
        ret--;
    }
    
    for (int i = 0; i < sz(arr); i++) vis[arr[i]] = -1;

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

    for (int p = 0; p < P; p++) {
        int x; cin >> x;
        vector<int> arr(x);
        for (auto& i : arr) cin >> i;

        sort(all(arr));

        if (x <= sq) cout << case1(x, arr) << '\n';
        else cout << case2(x, arr) << '\n';
    }
}