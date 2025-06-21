#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;
const int N = 20;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int n, m;
ll adj[N][N];
int dp[N][N][1 << N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u][v]++;
        adj[v][u]++;
    }

    ll ans = 0;

    // base case
    for (int v = 0; v < n; v++) {
        dp[v][v][1 << v] = 1;
    }

    // inductive step
    for (int bit = 0; bit < (1 << n); bit++) {
        for (int st = 0; st < n; st++) {
            for (int en = st; en < n; en++) {
                if (dp[st][en][bit] == 0) continue;

                for (int i = st; i < n; i++) {
                    if (!adj[en][i]) continue;
                    if (i == st) {
                        ans = (ans + dp[st][en][bit] * adj[en][i]) % MOD;
                    } else if (!((1 << i) & bit)) {
                        dp[st][i][bit | (1 << i)] = (dp[st][i][bit | (1 << i)] + dp[st][en][bit] * adj[en][i]) % MOD;
                    }
                }
            }
        }
    }
    
    ans = (ans - m) % MOD;
    ans = (ans + MOD) % MOD;
    // cout << ans << '\n';
    cout << ans * power(2, MOD - 2) % MOD;
}
