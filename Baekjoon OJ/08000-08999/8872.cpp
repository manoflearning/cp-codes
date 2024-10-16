#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const ll INF = 1e18;

int n, m;
ll len;
struct wv { ll w; int v; };
vector<wv> adj[101010];

void input() {
    cin >> n >> m >> len;
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        u++, v++;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

int vi[101010];
ll dp1[101010], dp2[101010];
void dfs1(int v, int prv) {
    vi[v] = 1;
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        dfs1(i.v, v);
        dp1[v] = max(dp1[v], i.w + dp1[i.v]);
    }
}
void dfs2(int v, int prv) {
    struct Node {
        ll w1, w2; int v;
        bool operator<(const Node& rhs) const { return w1 > rhs.w1; }
    };
    vector<Node> arr;
    for (auto& i : adj[v]) {
        if (i.v != prv) 
            arr.push_back({ dp1[i.v] + i.w, i.w, i.v });
    }

    if (sz(arr) == 0) return;
    else if (sz(arr) == 1) {
        dp2[arr[0].v] = dp2[v] + arr[0].w2;
    }
    else {
        sort(arr.begin(), arr.end());

        for (int i = 0; i < sz(arr); i++) {
            auto it = arr[i];
            dp2[it.v] = it.w2 + max(arr[i == 0 ? 1 : 0].w1, dp2[v]);
        }
    }

    for (auto& i : adj[v]) {
        if (i.v != prv) dfs2(i.v, v);
    }
}
ll dfs3(int v, int prv) {
    vector<ll> arr;
    for (auto& i : adj[v]) {
        if (i.v == prv) arr.push_back(dp2[i.v] + i.w);
        else arr.push_back(dp1[i.v] + i.w);
    }

    sort(arr.rbegin(), arr.rend());

    ll ret = 0;
    if (sz(arr) == 1) ret = arr[0];
    if (sz(arr) >= 2) ret = max(ret, arr[0] + arr[1]);

    for (auto& i : adj[v]) {
        if (i.v != prv) ret = max(ret, dfs3(i.v, v));
    }
    return ret;
}
ll dfs4(int v, int prv) {
    ll ret = dp2[v];
    for (auto& i : adj[v]) {
        if (i.v != prv) 
            ret = max(ret, dp1[i.v] + i.w);
    }
    
    if (ret == -1) ret = INF;
    for (auto& i : adj[v]) {
        if (i.v != prv) {
            ret = min(ret, dfs4(i.v, v));
        }
    }
    return ret == INF ? 0 : ret;
}

vector<ll> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    ll ans = 0;
    for (int v = 1; v <= n; v++) {
        if (!vi[v]) {
            dfs1(v, 0);
            dfs2(v, 0);
            ans = max(ans, dfs3(v, 0));
            a.push_back(dfs4(v, 0));
        }
    }

    //for (auto& i : a)
    //    cout << i << ' ';
    //cout << '\n';

    sort(a.rbegin(), a.rend());
    if (sz(a) >= 2) {
        ans = max(ans, len + a[0] + a[1]);
    }
    if (sz(a) >= 3) {
        ans = max(ans, 2 * len + a[1] + a[2]);
    }

    cout << ans;
}