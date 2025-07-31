#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 105;
const int MOD = 998244353;

ll fac[N], inv[N], facInv[N];
ll binom(int n, int r) {
    return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int n, s[N];
int dp[N][N][N][N];

int f(int l, int r, int lcnt, int rcnt) {
    int &ret = dp[l][r][lcnt][rcnt];
    if (ret != -1) return ret;
    if (l > r) {
        return ret = (lcnt <= 1) && (rcnt <= 1);
    }

    ret = 0;

    for (int i = l; i <= r; i++) {
        int is_l = (i - l <= r - i ? 1 : 0);
        int is_r = !is_l;
       
        if (l == 1 && r == n) {
            is_l = 0, is_r = 0;
        } else if (l == 1) {
            is_l = 0, is_r = 1;
        } else if (r == n) {
            is_l = 1, is_r = 0;
        }

        int nlcnt = lcnt - is_l;
        if (lcnt == 0) nlcnt = 0;
        if (lcnt == 1 && nlcnt == 0) continue;

        int nrcnt = rcnt - is_r;
        if (rcnt == 0) nrcnt = 0;
        if (rcnt == 1 && nrcnt == 0) continue;

        ll res = 1;
        if (l < i && i < r) {
            if (s[i] == 0) {
                res = res * f(l, i - 1, nlcnt, s[i]) % MOD;
                res = res * f(i + 1, r, s[i], nrcnt) % MOD;
                res = res * binom(r - l, i - l) % MOD;
            } else {
                res = 0;
                for (int k = 0; k <= s[i] - 1; k++) {
                    ll res2 = 1;
                    res2 = res2 * f(l, i - 1, nlcnt, k + 1) % MOD;
                    res2 = res2 * f(i + 1, r, s[i] - k, nrcnt) % MOD;
                    res2 = res2 * binom(r - l, i - l) % MOD;
                    res = (res + res2) % MOD;
                }
            }
        } else if (l == i) {
            res = (nlcnt <= 1) * f(i + 1, r, s[i], nrcnt) % MOD;
        } else if (i == r) {
            res = (nrcnt <= 1) * f(l, i - 1, nlcnt, s[i]) % MOD;
        } else {
            assert(0);
        }

        ret = (ret + res) % MOD;
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

    // Preprocessing in O(N)
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    for (int i = 2; i < N; i++) {
        fac[i] = i * fac[i - 1] % MOD;
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
    }

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> s[i]; s[i]++;
        }

        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= n + 1; j++) {
                for (int p = 0; p <= n; p++) {
                    for (int q = 0; q <= n; q++) {
                        dp[i][j][p][q] = -1;
                    }
                }
            }
        }

        cout << f(1, n, 0, 0) << '\n';
    }
}
