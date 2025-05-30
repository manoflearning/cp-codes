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

int n, a[MAXN];
int prv[MAXN], nxt[MAXN];
vector<bool> vis;

void init() {
    vis.clear();
}

void input() {
    cin >> n;
    vis.resize(n + 2);
    for (int i = 1; i <= n; i++) cin >> a[i];
}

bool good(int v) {
    if (v < 1 || n < v) return false;
    return a[prv[v]] == a[v] - 1 || a[nxt[v]] == a[v] - 1;
}

void solve() {
    priority_queue<pii> pq;
    a[0] = a[n + 1] = -2;
    for (int i = 1; i <= n; i++) {
        prv[i] = i - 1;
        nxt[i] = i + 1;
        if (good(i)) {
            vis[i] = true;
            pq.push({ a[i], i });
        }
    }

    while (!pq.empty()) {
        auto [_, v] = pq.top();
        pq.pop();

        nxt[prv[v]] = nxt[v];
        prv[nxt[v]] = prv[v];
        
        if (!vis[prv[v]] && good(prv[v])) {
            vis[prv[v]] = true;
            pq.push({ a[prv[v]], prv[v] });
        }
        if (!vis[nxt[v]] && good(nxt[v])) {
            vis[nxt[v]] = true;
            pq.push({ a[nxt[v]], nxt[v] });
        }
    }
}

void output() {
    int cntVis = 0;
    int cnt0 = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) cntVis++;
        if (a[i] == 0) cnt0++;
    }
    cout << (cntVis == n - 1 && cnt0 > 0 ? "YES" : "NO") << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        solve();

        output();
    }
}