#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;

int n;
vector<ll> a(MAXN), dp(MAXN);
vector<bool> vis(MAXN);
vector<vector<int>> adj(MAXN), chd(MAXN);
vector<int> par(MAXN), siz(MAXN);

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void dfs(int v, int prv) {
    par[v] = prv;
    siz[v] = 1;
    for (auto& i : adj[v]) {
        if (i != prv) {
            chd[v].push_back(i);
            dfs(i, v);
            siz[v] += siz[i];
        }
    }
}

ll f(int v) {
    ll& ret = dp[v];
    if (vis[v]) return ret;
    vis[v] = 1;

    ret = a[v];

    vector<ll> arr_turn_changed;
    ll sum_turn_unchanged_neg = 0;
    for (auto& i : chd[v]) {
        ll res = f(i);
        if (siz[i] & 1) {
            arr_turn_changed.push_back(res);
        }
        else {
            if (res >= 0) ret -= res;
            else sum_turn_unchanged_neg += res;
        }
    }

    sort(all(arr_turn_changed));
    ll turn = -1;
    while (!arr_turn_changed.empty()) {
        ret += turn * arr_turn_changed.back();
        turn *= -1;
        arr_turn_changed.pop_back();
    }

    ret += turn * sum_turn_unchanged_neg;

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

    dfs(1, 0);

    ll ans = f(1);
    if (ans == 0) cout << "Draw";
    else if (ans > 0) cout << "Sehun";
    else if (ans < 0) cout << "Cheolmin";
}