// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 202020;

vector<int> uf(MAXN, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] = V;
}

int n, m, a[MAXN];
vector<int> adj[MAXN];
int score[MAXN], vi[MAXN];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        if (a[u] > a[v]) swap(u, v);
        if (a[u] < a[v]) adj[u].push_back(v);

        if (a[u] == a[v]) {
            merge(u, v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
}

void solve() {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    score[find(1)] = 1;
    pq.push({ a[1], 1 });

    while (!pq.empty()) {
        int v = pq.top().sc;
        pq.pop();

        for (auto& i : adj[v]) {
            score[find(i)] = max(score[find(i)], (a[i] > a[v]) + score[find(v)]);
            if (vi[i]) continue;
            vi[i] = true;
            pq.push({ a[i], i });
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

    solve();

    cout << score[find(n)];
}