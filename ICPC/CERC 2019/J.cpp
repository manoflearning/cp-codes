#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int sq = 373;

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
        // uf[U] += uf[V];
        uf[V] = U;
    }
}uf;

int N, E, P;
vector<int> t[101010];
set<pair<int, int>> edges;

void input() {
    cin >> N >> E >> P;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        t[u].push_back(v);
        edges.insert({ u, v });
    }
}

ll case1(int x, const vector<int>& arr) { // O(x * x / 2)
    int ret = x;

    uf.init(x);
    for (int i = 0; i < x; i++) {
        for (int j = i + 1; j < x; j++) {
            int u = arr[i], v = arr[j];
            if (u > v) swap(u, v);

            if (!edges.count({ u, v })) continue;
            if (uf.find(i) == uf.find(j)) continue;

            uf.merge(i, j);
            ret--;
        }
    }

    return ret;
}

ll case2(int x, const vector<int>& arr) {
    int ret = x;

    uf.init(x);
    for (int i = x - 1; i >= 0; i--) {
        int u = arr[i];
        for (auto& v : t[u]) {
            int j = lower_bound(all(arr), v) - arr.begin();
            if (j == sz(arr) || (j < sz(arr) && arr[j] != v)) continue;
            if (uf.find(i) == uf.find(j)) continue;
            uf.merge(i, j);
            ret--;
        }
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

    for (int p = 0; p < P; p++) {
        int x; cin >> x;
        vector<int> arr(x);
        for (auto& i : arr) cin >> i;

        sort(all(arr));

        if (x <= sq) cout << case1(x, arr) << '\n';
        else cout << case2(x, arr) << '\n';
    }
}