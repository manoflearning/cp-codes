#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 505050;

struct UF {
    vector<int> uf;
    void init(int N) {
        uf.clear();
        uf.resize(N + 1, -1);
    }
    int find(int v) {
        if (uf[v] < 0) return v;
        return uf[v] = find(uf[v]);
    }
    int size(int v) { return -uf[find(v)]; }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] += uf[V];
        uf[V] = U;
    }
} uf;

int n, a[N];
int ind[N];
vector<int> radj[N];
int dp[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ind[a[i]]++;
        radj[a[i]].push_back(i);
    }

    // topological sort
    queue<int> q;
    for (int v = 1; v <= n; v++) {
        if (!ind[v]) q.push(v);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        ind[a[v]]--;
        if (!ind[a[v]]) q.push(a[v]);
    }

    // get cycle
    uf.init(N);
    for (int v = 1; v <= n; v++) {
        if (ind[v]) uf.merge(v, a[v]);
    }

    // get longest length
    for (int v = 1; v <= n; v++) {
        if (ind[v]) {
            dp[v] = uf.size(v);
            dfs(v);
        }
    }


}
