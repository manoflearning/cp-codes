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

const int MAXN = 101010;

int n;
vector<int> t[MAXN];
ll w[MAXN];
ll dp1[MAXN], dp2[MAXN];
ll sum[MAXN];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
}

void dfs1(int v, int prv) {
    for (auto& i : t[v]) {
        if (i == prv) continue;
        dfs1(i, v);
        sum[v] += sum[i];
        dp1[v] += dp1[i];
    }
    sum[v] += w[v];
    dp1[v] += (sum[v] - w[v]);
}

void dfs2(int v, int prv) {
    ll dpsum = dp2[v] + w[v] + (sum[1] - sum[v]);

    for (auto& i : t[v]) {
        if (i == prv) continue;
        dpsum += dp1[i] + 2 * sum[i];
    }

    for (auto& i : t[v]) {
        if (i == prv) continue;
        dp2[i] = dpsum - (dp1[i] + 2 * sum[i]);
        dfs2(i, v);
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

    dfs1(1, -1);

    dfs2(1, -1);

    ll ans = LLONG_MAX;
    for (int v = 1; v <= n; v++)
        ans = min(ans, dp1[v] + dp2[v]);

    cout << ans;
}