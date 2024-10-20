#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;
const ll INF = 1e18;

int n, a[MAXN];
vector<int> adj[MAXN], t[MAXN];

void input() {
    cin >> n;
    string s; cin >> s;
    for (int i = 0; i < sz(s); i++) {
        a[i + 1] = (s[i] == 'A' ? 1 : 2);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int dep[MAXN], siz[MAXN];
int cnt1[MAXN], cnt2[MAXN];

void dfs(int v, int prv) {
    dep[v] = 1 + dep[prv];
    siz[v] = 1;
    
    if (a[v] == 1) cnt1[v]++;
    if (a[v] == 2) cnt2[v]++;

    for (auto& i : adj[v]) {
        if (i == prv) continue;
        t[v].push_back(i);
        dfs(i, v);
        siz[v] += siz[i];
        cnt1[v] += cnt1[i];
        cnt2[v] += cnt2[i];
    }
}

ll dp1above[MAXN], dp1below[MAXN];
ll dp2above[MAXN], dp2below[MAXN];

void getDPbelow() {
    vector<int> ord;
    for (int v = 1; v <= n; v++)
        ord.push_back(v);
    sort(all(ord), [&](const int p1, const int p2) {
        return dep[p1] > dep[p2];
    });

    for (auto& v : ord) {
        for (auto& i : t[v]) {
            dp1below[v] += dp1below[i] + cnt1[i];
            dp2below[v] += dp2below[i] + cnt2[i];
        }
    }
}

void getDPabove() {
    vector<int> ord;
    for (int v = 1; v <= n; v++)
        ord.push_back(v);
    sort(all(ord), [&](const int p1, const int p2) {
        return dep[p1] < dep[p2];
    });

    for (auto& v : ord) {
        dp1above[v] += cnt1[1] - cnt1[v];
        dp2above[v] += cnt2[1] - cnt2[v];
        for (auto& i : t[v]) {
            dp1above[i] += dp1above[v];
            dp2above[i] += dp2above[v];
            dp1above[i] += dp1below[v] - dp1below[i] - cnt1[i];
            dp2above[i] += dp2below[v] - dp2below[i] - cnt2[i];
        }
    }
}

ll ans = INF;

void solve() {
    for (int v = 1; v <= n; v++) {
        if (siz[v] == cnt1[1]) {
            ans = min(ans, dp2below[v] + dp1above[v]);
        }
        if (siz[v] == cnt2[1]) {
            ans = min(ans, dp1below[v] + dp2above[v]);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, 0);

    getDPbelow();

    getDPabove();

    solve();

    cout << (ans == INF ? -1 : ans);
}