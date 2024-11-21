#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998244353;
const int MAXN = 101;

void bottomup(vector<vector<ll>> &dp, string w) {
    // base case
    dp[0][0] = 1;
    dp[0][1] = 1;

    // inductive step
    for (int i = 0; i + 1 < MAXN; i++) {
        
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m, k;
    string w, rw;
    cin >> n >> m >> k >> w;
    rw = w; reverse(all(rw));

    vector<vector<ll>> dpl(MAXN, vector<ll>(8));
    vector<vector<ll>> dpr(MAXN, vector<ll>(8));

    bottomup(dpl, w);
    bottomup(dpr, rw);

    ll ans = 0;
    for (int s1 = 1; s1 + k - 1 <= n; s1++) {
        int e1 = s1 + k - 1;
        for (int s2 = 1; s2 + k - 1 <= m; s2++) {
            int e2 = s2 + k - 1;

            ll resl = 0, resr = 0;
            for (int bl1 = 0; bl1 < 8; bl1 += 2) {
                for (int bl2 = 1; bl2 < 8; bl2 += 2) {
                    resl += dpl[s1 - 1][bl1] * dpl[s2 - 1][bl2];
                    resl %= MOD;
                    resl += dpl[s1 - 1][bl2] * dpl[s2 - 1][bl1];
                    resl %= MOD;
                }
            }

            for (int br1 = 0; br1 < 8; br1 += 2) {
                for (int br2 = 1; br2 < 8; br2 += 2) {
                    resr += dpr[n - e1][br1] * dpr[m - e2][br2];
                    resr %= MOD;
                    resr += dpr[n - e1][br2] * dpr[m - e2][br1];
                    resr %= MOD;
                }
            }

            ans = (ans + resl * resr) % MOD;
        }
    }

    cout << ans;
}
