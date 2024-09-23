#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 252525;
const ll INF = 1e18;

int n;
vector<ll> s(MAXN), t(MAXN);
vector<int> p(MAXN), q(MAXN);

int m;
vector<vector<int>> adj(MAXN << 1);
vector<int> cnt(MAXN << 1);

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> t[i];
    }
}

vector<ll> cc;
void vc() {
    for (int i = 1; i <= n; i++) {
        cc.push_back(s[i]);
        cc.push_back(t[i]);
    }
    cc.push_back(-1);

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (int i = 1; i <= n; i++) {
        p[i] = lower_bound(all(cc), s[i]) - cc.begin();
        q[i] = lower_bound(all(cc), t[i]) - cc.begin();
    }
    m = sz(cc) - 1;
}

void graph_modeling() {
    for (int i = 1; i <= n; i++) {
        adj[p[i]].push_back(q[i]);
        adj[q[i]].push_back(p[i]);
        cnt[p[i]]++;
    }
}

ll ans = 0;
vector<bool> vis(MAXN << 1);
vector<ll> vals;
int siz = 0;

void dfs(int v) {
    vis[v] = 1;
    vals.push_back(cc[v]);
    siz += cnt[v];
    for (auto& i : adj[v]) {
        if (!vis[i]) dfs(i);
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        ans += s[i] + t[i];
    }

    for (int v = 1; v <= m; v++) {
        if (vis[v]) continue;
        vals.clear();
        siz = 0;
        
        dfs(v);

        sort(all(vals));
        for (int i = 0; i < siz; i++) {
            ans -= vals[i];
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

    vc();

    graph_modeling();

    solve();

    cout << ans;
}
