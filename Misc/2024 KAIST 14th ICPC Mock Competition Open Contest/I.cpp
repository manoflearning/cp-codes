#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;
const int MOD = 998'244'353;

int n;
ll a1[MAXN][3];
ll a2[MAXN][3];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a1[i][0] >> a1[i][1] >> a1[i][2];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a2[i][0] >> a2[i][1] >> a2[i][2];
    }
}

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

// 0: non-attacker
// 1: A attacker
// 2: B atttaker
ll dp[MAXN][3]; // dp[i][j] = |not finish after ith turn with attacker j|

ll win1 = 0;
ll d = 1;

void bottomup() {
    // base case
    dp[0][0] = 1;

    // inductive step
    for (int i = 1; i <= n; i++) {
        d = (d * (a1[i][0] + a1[i][1] + a1[i][2]) % MOD * (a2[i][0] + a2[i][1] + a2[i][2]) % MOD) % MOD;

        // rr, ss, pp
        {
            for (int j = 0; j < 3; j++) {
                dp[i][0] = (dp[i][0] + a1[i][j] * a2[i][j] % MOD * dp[i - 1][0] % MOD) % MOD;

                ll x = a1[i][j] * a2[i][j] % MOD * dp[i - 1][1] % MOD;
                ll y = d;
                win1 = (win1 + x * power(y, MOD - 2) % MOD) % MOD;
            }
        }
        // rs, sp, pr
        {
            for (int j = 0; j < 3; j++) {
                dp[i][1] = (dp[i][1] + a1[i][j] * a2[i][(j + 1) % 3] % MOD * dp[i - 1][0] % MOD) % MOD;
                dp[i][1] = (dp[i][1] + a1[i][j] * a2[i][(j + 1) % 3] % MOD * dp[i - 1][1] % MOD) % MOD;
                dp[i][1] = (dp[i][1] + a1[i][j] * a2[i][(j + 1) % 3] % MOD * dp[i - 1][2] % MOD) % MOD;
            }
        }
        // sr, ps, rp
        {
            for (int j = 0; j < 3; j++) {
                dp[i][2] = (dp[i][2] + a1[i][(j + 1) % 3] * a2[i][j] % MOD * dp[i - 1][0] % MOD) % MOD;
                dp[i][2] = (dp[i][2] + a1[i][(j + 1) % 3] * a2[i][j] % MOD * dp[i - 1][1] % MOD) % MOD;
                dp[i][2] = (dp[i][2] + a1[i][(j + 1) % 3] * a2[i][j] % MOD * dp[i - 1][2] % MOD) % MOD;
            }
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

    bottomup();

    cout << win1;
}
