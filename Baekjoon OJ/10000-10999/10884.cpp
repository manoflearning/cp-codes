#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct wv { ll w; int v; };
struct dcnt { ll d; int cnt; };

int n, m;
vector<wv> adj[2020], chd[2020];
ll d;
dcnt dp[2020];

void init() {
    for (int i = 0; i < 2020; i++) {
        adj[i].clear(); chd[i].clear();
    }
}

void input() {
    cin >> n >> m;
    m = n - 1 - m;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dfs(int v, int prv) {
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        dfs(i.v, v);
        chd[v].push_back(i);
    }
}

dcnt f(int v) {
    auto& ret = dp[v];
    if (ret.d != -1) return ret;
    if (chd[v].empty()) return ret = { 0, 0 };

    ret = { 0, 0 };

    vector<ll> arr;
    for (auto& i : chd[v]) {
        auto res = f(i.v);

        if (res.d + i.w > d) ret.cnt++;
        else arr.push_back(res.d + i.w);

        ret.cnt += res.cnt;
    }

    sort(arr.rbegin(), arr.rend());
    
    int st = 0;
    for (st = 0; st < sz(arr) - 1; st++) {
        if (arr[st] + arr[st + 1] <= d) break;
        ret.cnt++;
    }

    if (st < sz(arr)) ret.d = arr[st];

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tt; cin >> tt;
    while (tt--) {
        init();

        input();

        dfs(1, -1);

        ll l = 1, r = 2000 * 1e6;
        while (l < r) {
            for (int i = 0; i < 2020; i++) dp[i] = { -1, -1 };

            d = (l + r) >> 1;
            
            if (f(1).cnt <= m) r = d;
            else l = d + 1;
        }

        cout << l << '\n';
    }

    return 0;
}