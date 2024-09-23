#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1010;
const int MOD = 1e9 + 7;

int n;
vector<int> p(MAXN);
vector<vector<int>> chd(MAXN);

vector<vector<ll>> dp(MAXN, vector<ll>(MAXN));
vector<int> siz(MAXN);

void input() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        chd[p[i]].push_back(i);
    }
}

void dfs(int v) {
    dp[v][1] = 1;
    siz[v] = 1;

    for (auto& u : chd[v]) {
        dfs(u);
        for (int j = siz[v]; j >= 1; j--) {
            for (int i = 1; i <= siz[u]; i++) {
                dp[v][i + j] = (dp[v][i + j] + dp[u][i] * dp[v][j]) % MOD;
            }
        }
        siz[v] += siz[u];
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

    dfs(0);

    vector<ll> ans(MAXN);
    for (int v = 0; v < n; v++) {
        for (int i = 1; i <= siz[v]; i++) {
            ans[i] = (ans[i] + dp[v][i]) % MOD;
        }
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
}
