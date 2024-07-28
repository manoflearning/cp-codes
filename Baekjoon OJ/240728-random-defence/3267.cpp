#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;
const int N = 101010;

struct Edge {
    ll w; int v;
};

int n, st;
vector<Edge> t[N];
ll dp[N][2];
// dp[v][0] = min distance with two snow plovers to clean up the subtree(v)
// dp[v][1] = min distance with one snow plovers to clean up the subtree(v)

ll dp1[N];
// dp1[v] = min distance with one snow plovers to clean up the subtree(v)
// and come back to node v
ll dp2[N];
// dp2[v] = min distance with one snow plovers to clean up the subtree(v)
// and not necessarily come back to node v

void input() {
    cin >> n >> st;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        t[u].push_back({ w, v });
        t[v].push_back({ w, u });
    }
}

void dfs(int v, int prv) {
    vector<pair<ll, ll>> ord;
    for (auto& i : t[v]) {
        if (i.v == prv) continue;
        dfs(i.v, v);
        dp1[v] += 2 * i.w + dp1[i.v];
        ord.push_back({ i.w + dp2[i.v], 2 * i.w + dp1[i.v] });
    }

    sort(all(ord), [&](const pair<ll, ll>& p1, const pair<ll, ll>& p2) {
        return p1.second - p1.first > p2.second - p2.first;
    });

    for (int i = 0; i < sz(ord); i++) {
        if (i == 0) dp2[v] += ord[i].first;
        else dp2[v] += ord[i].second;
    }
}

ll f(int v, int prv, bool one_snow_plover) {
    ll& ret = dp[v][one_snow_plover];
    if (ret != -1) return ret;
    if (one_snow_plover) return ret = dp2[v];
    if (prv == -1 && sz(t[v]) == 1) {
        return ret = 2 * t[v][0].w + f(t[v][0].v, v, 0);
    }
    if (prv != -1 && sz(t[v]) == 2) {
        ret = 0;
        for (auto& i : t[v]) {
            if (i.v == prv) continue;
            ret += 2 * i.w + f(i.v, v, 0);
        }
        return ret;
    }

    ret = INF;

    // case 1
    {
        ll res = 0;
        vector<pair<ll, ll>> ord;
        for (auto& i : t[v]) {
            if (i.v == prv) continue;
            ord.push_back({ 2 * i.w + f(i.v, v, 0), 2 * i.w + dp1[i.v] });
        }

        sort(all(ord), [&](const pair<ll, ll>& p1, const pair<ll, ll>& p2) {
            return p1.second - p1.first > p2.second - p2.first;
        });

        for (int i = 0; i < sz(ord); i++) {
            if (i == 0) res += ord[i].first;
            else res += ord[i].second;
        }

        ret = min(ret, res);
    }

    // case 2
    {
        ll res = 0;
        vector<pair<ll, ll>> ord;
        for (auto& i : t[v]) {
            if (i.v == prv) continue;
            ord.push_back({ i.w + dp2[i.v], 2 * i.w + dp1[i.v] });
        }

        sort(all(ord), [&](const pair<ll, ll>& p1, const pair<ll, ll>& p2) {
            return p1.second - p1.first > p2.second - p2.first;
        });

        for (int i = 0; i < sz(ord); i++) {
            if (i == 0 || i == 1) res += ord[i].first;
            else res += ord[i].second;
        }

        ret = min(ret, res);
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

    dfs(st, -1);

    memset(dp, -1, sizeof(dp));

    cout << min(f(st, -1, 1), f(st, -1, 0));
}